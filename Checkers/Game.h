//
// Created by Osher Steel on 1/20/23.
//

#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H

#include <vector>
#include <list>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Game {
public:
    explicit Game(int);

    bool pieceSelected;
    Vector2i selectedPosition;

    int board[8][8] =
            {-1, 0,-1, 0,0, 0,1, 0,
             0,-1, 0,0, 0,1, 0,1,
             -1, 0,-1, 0,0, 0,1, 0,
             0, -1, 0, 0, 0, 1, 0, 1,
             -1, 0, -1, 0, 0, 0, 1, 0,
             0, -1, 0, 0, 0, 1, 0, 1,
             -1, 0, -1, 0, 0, 0, 1, 0,
             0, -1, 0, 0, 0, 1, 0, 1 };

    void turnProgress(Vector2i);

    void allAvailableMoves( bool);
    bool canPlayerMove();
    bool canPieceMove(int,int,int,bool);

    bool canPieceMoveCheck(int,int);
    bool isMoveLegal();
    bool wasMoveAJump() const;
    void pawnEaten();

    void clearVectors();
private:
    vector<Vector2i> piecesThatCanMove;
    vector<Vector2i> piecesThatCanEat;
    vector<vector<Vector2i>> piecesMoves;
    int turn;
    int tileSize;
    Vector2i mousePosition;

    static bool isInbounds(int,int);

};


#endif //CHECKERS_GAME_H
