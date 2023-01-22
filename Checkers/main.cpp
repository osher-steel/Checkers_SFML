#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;


namespace constants {
    constexpr float tileSize=100;
}
CircleShape redPiece;
CircleShape blackPiece;
RectangleShape tile;
RectangleShape selectedTile;
Texture kingTexture;
Sprite kingImage;

void createGraphics();

int main() {

    RenderWindow window(VideoMode(constants::tileSize*8,constants::tileSize*8),"Checkers");
    createGraphics();
    Game game= Game(constants::tileSize);

    while(window.isOpen()){

                                //MOUSE EVENTS//
        Event event;
        Vector2i mousePosition= Mouse::getPosition(window);

        while(window.pollEvent(event)){
            if(event.type==Event::Closed)
                return 0;

            if(event.type== Event::MouseButtonPressed && event.key.code==Mouse::Left){
                    game.turnProgress(mousePosition);
            }

        }


        window.clear();


                                    //DRAW BOARD//
        for(int i=0; i<8;i++){
            for(int j=0; j<8; j++){
                if(i%2==0){
                    if(j%2==0)
                        tile.setFillColor(Color(0,50,50));
                    else
                        tile.setFillColor(Color(255,255,255));

                }
                else{
                    if(j%2==1)
                        tile.setFillColor(Color(0,50,50));
                    else
                        tile.setFillColor(Color(255,255,255));
                }
                tile.setPosition(j*constants::tileSize,i*constants::tileSize);
                window.draw(tile);
            }
        }

                                    //DRAW SELECTED TILE//
        if(game.pieceSelected){
            selectedTile.setPosition(game.selectedPosition.x*constants::tileSize,game.selectedPosition
                                                                                         .y*constants::tileSize);
            window.draw(selectedTile);
        }

                                    //DRAW PIECES//

        for(int i=0; i<8; i++){
            for(int j=0; j<8;j++){
                if(game.board[i][j]==1 ||game.board[i][j]==2 ){
                    redPiece.setPosition(i*constants::tileSize+(constants::tileSize/4),j*constants::tileSize+
                                                                                       (constants::tileSize/4));
                    window.draw(redPiece);


                }
                else if(game.board[i][j]==-1||game.board[i][j]==-2){
                    blackPiece.setPosition(i*constants::tileSize+(constants::tileSize/4),j*constants::tileSize+
                                                                                         (constants::tileSize/4));
                    window.draw(blackPiece);
                }

                if(game.board[i][j]==-2 || game.board[i][j]==2  ){
                    kingImage.setPosition(i*constants::tileSize+ constants::tileSize*15/48,
                                           j*constants::tileSize+constants::tileSize*15/48);
                    window.draw(queenImage);
                }

            }

        }
        window.display();
    }

}

void createGraphics(){
    redPiece.setFillColor(Color(50,0,255));
    redPiece.setRadius(constants::tileSize/4);

    blackPiece.setFillColor(Color(150,0,150));
    blackPiece.setRadius(constants::tileSize/4);

    tile.setSize(Vector2f(constants::tileSize,constants::tileSize));

    selectedTile.setFillColor(Color(0,255,0));
    selectedTile.setSize(Vector2f(constants::tileSize,constants::tileSize));

    kingTexture.loadFromFile("king.png");

    kingImage.setTexture(queenTexture);
    kingImage.setScale(constants::tileSize/125,constants::tileSize/125);

    /* Texture gameOverTexture;
     gameOverTexture.loadFromFile("game_over.png");

     Sprite gameOverImage;
     gameOverImage.setTexture(gameOverTexture);
     gameOverImage.setScale(constants::tileSize/80,constants::tileSize/80);
     gameOverImage.setPosition(constants::tileSize*(constants::tileSize/48),constants::tileSize*
     (constants::tileSize/48));*/

}
