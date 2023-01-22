//
// Created by Osher Steel on 1/20/23.
//

#include "Game.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


Game::Game(int  tileSize) {
    for(int i=0; i<8; i++){
        for(int j=0; j<8;j++){
            this->board[i][j]=board[i][j];
        }
    }

    turn=-1;
    pieceSelected=false;
    this->tileSize=tileSize;

    allAvailableMoves(false);
}

void Game::turnProgress(Vector2i mp) {
    mousePosition=mp;

    mousePosition.x/=tileSize;
    mousePosition.y/=tileSize;

    if(!pieceSelected){

        selectedPosition=mousePosition;

        if(!piecesThatCanEat.empty()){
            for(auto & i : piecesThatCanEat){
                if(mousePosition.x==i.x && mousePosition.y==i.y)
                    pieceSelected=true;
            }
        }
        else if(canPieceMoveCheck(selectedPosition.x,selectedPosition.y))
            pieceSelected=true;
    }
    else{
        if(mousePosition!=selectedPosition){
            if(isMoveLegal()){
                bool justTurnedIntoKing=false;

                board[mousePosition.x][mousePosition.y]=board[selectedPosition.x][selectedPosition.y];
                board[selectedPosition.x][selectedPosition.y]=0;

                if(turn==-1){
                    if(mousePosition.y==7)
                    {
                        board[mousePosition.x][mousePosition.y]=-2;
                        justTurnedIntoKing=true;

                    }
                }
                else{
                    if(mousePosition.y==0){
                        justTurnedIntoKing=true;
                        board[mousePosition.x][mousePosition.y]=2;
                    }
                }
                clearVectors();

                if(wasMoveAJump()){
                    pawnEaten();
                    allAvailableMoves(true);
                    if(piecesThatCanMove.empty() || justTurnedIntoKing){
                        clearVectors();
                        turn=-turn;
                        allAvailableMoves(false);

                    }
                }
                else{
                    clearVectors();
                    turn=-turn;
                    allAvailableMoves(false);
                }


                pieceSelected=false;
            }
        }
        else
            pieceSelected=false;
    }

}

void Game::allAvailableMoves( bool musEat) {
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j]==turn||board[i][j]==turn+turn ){
                if(i==1 && j==7){

                }
                if(canPieceMove(board[i][j],i,j, musEat)){
                    piecesThatCanMove.emplace_back(i,j);
                }
            }
        }
    }

}

bool Game::canPlayerMove() {
    if(piecesThatCanMove.empty())
        return false;
    else
        return true;
}

bool Game::canPieceMove(int piece, int x, int y, bool mustEat) {
    int buffer= -(turn);
    bool canMove=false;
    bool canEat=false;
    bool isKing;

    if(piece==2 || piece==-2)
        isKing=true;
    else
        isKing=false;


    if(x==4 && y==5){

    }
    vector<Vector2i>availableMoves;
    availableMoves.emplace_back(x,y);

    if(isInbounds(x+1,y+buffer) && board[x+1][y+buffer]==0 && !mustEat){
        availableMoves.emplace_back(x+1,y+buffer);
        canMove=true;
    }
    if(isInbounds(x+1,y+buffer) &&( board[x+1][y+buffer]==buffer || board[x+1][y+buffer]==buffer+buffer  ))  //if pawn
        // across is ennemy
    {
        if(isInbounds(x+2,y+buffer+buffer) && board[x+2][y+buffer+buffer]==0){
            if(!mustEat ||(mousePosition.x==x && mousePosition.y==y) ) {
                availableMoves.emplace_back(x + 2, y + buffer + buffer);
                canMove = true;
                canEat = true;
            }
        }
    }

    if(isInbounds(x-1,y+buffer) && board[x-1][y+buffer]==0 && !mustEat){
        availableMoves.emplace_back(x-1,y+buffer);
        canMove=true;
    }
    if(isInbounds(x-1,y+buffer) && (board[x-1][y+buffer]==buffer || board[x-1][y+buffer]==buffer+buffer  ))
    {
        if(isInbounds(x-2,y+buffer+buffer) && board[x-2][y+buffer+buffer]==0){
            if(!mustEat ||(mousePosition.x==x && mousePosition.y==y) ){
                availableMoves.emplace_back(x-2,y+buffer+buffer);
                canMove=true;
                canEat=true;
            }
        }
    }

    if(isInbounds(x-1,y-buffer) && board[x-1][y-buffer]==0 && !mustEat && isKing){
        availableMoves.emplace_back(x-1,y-buffer);
        canMove=true;
    }
    if(isInbounds(x-1,y-buffer) && (board[x-1][y-buffer]==buffer || board[x-1][y-buffer]==buffer+buffer)&& isKing)
    {
        if(isInbounds(x-2,y-buffer-buffer) && board[x-2][y-buffer-buffer]==0){
            if(!mustEat ||(mousePosition.x==x && mousePosition.y==y) ) {
                availableMoves.emplace_back(x - 2, y - buffer - buffer);
                canMove = true;
                canEat = true;
            }
        }
    }

    if(isInbounds(x+1,y-buffer) && board[x+1][y-buffer]==0 && !mustEat && isKing){
        availableMoves.emplace_back(x+1,y-buffer);
        canMove=true;
    }
    if(isInbounds(x+1,y-buffer) &&( board[x+1][y-buffer]==buffer  || board[x+1][y-buffer]==buffer+buffer) && isKing)
    {
        if(isInbounds(x+2,y-buffer-buffer) && board[x+2][y-buffer-buffer]==0){
            if(!mustEat ||(mousePosition.x==x && mousePosition.y==y) ){
                availableMoves.emplace_back(x+2,y-buffer-buffer);
                canMove=true;
                canEat=true;
            }
        }
    }

    if(canEat){
        piecesThatCanEat.emplace_back(x,y);
    }
    piecesMoves.push_back(availableMoves);
    return canMove;
}

bool Game::canPieceMoveCheck(int x, int y) {
    for(auto & i : piecesThatCanMove){
        if(i.x==x && i.y==y)
            return true;
    }

    return false;
}

bool Game::isMoveLegal() {
    for(auto & piecesMove : piecesMoves){
        if(piecesMove[0].x==selectedPosition.x && piecesMove[0].y==selectedPosition.y ){
            for(auto & j : piecesMove){
                if(j==mousePosition)
                    return true;
            }
        }
    }
    return false;
}

bool Game::wasMoveAJump() const  {
    if(abs(selectedPosition.y-mousePosition.y)==2)
        return true;
    else
        return false;
}

void Game::pawnEaten() {
    if(selectedPosition.y>mousePosition.y){
        if(selectedPosition.x>mousePosition.x){
            board[selectedPosition.x-1][selectedPosition.y-1]=0;
        }
        else{
            board[selectedPosition.x+1][selectedPosition.y-1]=0;
        }
    }
    else{
        if(selectedPosition.x>mousePosition.x){
            board[selectedPosition.x-1][selectedPosition.y+1]=0;
        }
        else{
            board[selectedPosition.x+1][selectedPosition.y+1]=0;
        }
    }
}

void Game::clearVectors() {
    piecesMoves.clear();
    piecesThatCanMove.clear();
    piecesThatCanEat.clear();
}

bool Game::isInbounds(int x, int y) {
    if(x>7 || y>7 || x<0 || y<0)
        return false;
    else return true;

}


