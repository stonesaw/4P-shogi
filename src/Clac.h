#pragma once
#include <string>


class Piece {
public:
    std::string name;
    unsigned int player;
    bool canMove;
};


class CalcBase {
public:
    std::string pieceKind[17] = {
        /*  index
        0    1     2     3     4     5       6     7     8*/
        "", "��", "��", "�j", "��", "��",   "�p", "��", "��",
        //   9     10    11    12    13      14    15    16
            "��", "��", "�\", "�S", "None", "�n", "��", "None"
    };
    int pieceStarter[3][9] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 6, 0, 0, 0, 0, 0, 7, 0},
        {2, 3, 4, 5, 8, 5, 4, 3, 2}
    };
protected:
    template<typename T>
    void rotate2dAry(T ary, std::string direction, unsigned int times);

};


class Calc : CalcBase {
public:
    int board[9 + 2][9 + 2]; // +2 : check board inside
    
    Calc();
    void init();
};


