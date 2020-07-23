#pragma once
#include <string>
#include <vector>


class Piece {
public:
    int id;
    int player;
    bool canMove;

    Piece(int id = -1, int player = -1, bool canMove = false) {
        this->id = id; // 1 - 16 (0 is empty) (-1 is out of board)
        this->player = player; // 0 or 1 (TO DO change player size)
        this->canMove = canMove;
    }
};


class Calc {
private:
    template<typename T>
    std::vector<std::vector<T>> rotate2dVector(std::vector<std::vector<T>> vec, std::string direction);

public:
    std::vector<std::vector<Piece>> board;
    std::vector<std::vector<int>> pieceStarter = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 6, 0, 0, 0, 0, 0, 7, 0},
        {2, 3, 4, 5, 8, 5, 4, 3, 2}
    };

    Calc();

    static std::string id2name(size_t id);
    static size_t name2id(std::string);
};
