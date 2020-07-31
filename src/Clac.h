#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "Data.h"

class Piece {
public:
    int id;
    size_t player;
    bool canMove;
    std::string moveType;

    Piece(int id = -1, int player = 0, bool canMove = false, std::string moveType = "null") {
        this->id = id; // 1 - 16 (0 is empty) (-1 is out of board)
        this->player = player; // 0 or 1 (TO DO change player size)
        this->canMove = canMove;
        this->moveType = moveType;
    }
};


class Calc : public Data {
private:
    template<typename T>
    std::vector<std::vector<T>> rotate2dVector(std::vector<std::vector<T>> vec, std::string direction);
    std::string setMoveType(size_t id); // set "map" or "proceed"

    std::vector<std::vector<int>> GetPieceMoveMap(std::string name);


public:
    std::vector<std::vector<Piece>> board;
    size_t turn;
    int chooseX = -1, chooseY = -1;
    bool isChoose = false;

    Calc();

    void Update();

    // Base Method
    std::string id2name(size_t id);
    size_t name2id(std::string);
};
