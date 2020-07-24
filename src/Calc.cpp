#include "Clac.h"
#include <vector>
#include <stdexcept>


Calc::Calc() {
    // size = 9+2 : check out of board
    this->board.resize(11, std::vector<Piece>(11, (-1, -1, false)));
    std::vector<std::vector<int>> opponentPieceStarter = rotate2dVector(this->pieceStarter, "reverse");
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (1 <= x && x <= 9 && 1 <= y && y <= 9) {
                if (y <= 3)      this->board.at(y).at(x) = Piece(opponentPieceStarter[y - 1][x - 1], 1);
                else if (7 <= y) this->board.at(y).at(x) = Piece(pieceStarter[y - 7][x - 1], 0);
                else             this->board.at(y).at(x) = Piece(0);
            }
            else {
                this->board.at(y).at(x) = Piece();
            }
        }
    }
}


template<typename T>
std::vector<std::vector<T>> Calc::rotate2dVector(std::vector<std::vector<T>> vec, std::string direction) {
    size_t vec_w = vec.at(0).size();
    size_t vec_h = vec.size();

    if (direction == "right" || direction == "left") {
        std::vector<std::vector<T>> temp(vec_w, std::vector<T>(vec_h));
        for (size_t y = 0; y < vec_h; y++) {
            for (size_t x = 0; x < vec_w; x++) {
                if      (direction == "right") temp[y][x] = vec.at(vec_w - 1 - x).at(y);
                else if (direction == "left" ) temp[y][x] = vec.at(x).at(vec_h - 1 - y);
            }
        }
        return temp;
    }
    else if (direction == "reverse") {
        std::vector<std::vector<T>> temp(vec_h, std::vector<T>(vec_w));
        for (size_t y = 0; y < vec_h; y++) {
            for (size_t x = 0; x < vec_w; x++) {
                temp[y][x] = vec.at(vec_h - 1 - y).at(vec_w - 1 - x);
            }
        }
        return temp;
    }
    else {
        return vec;
    }
}

// TO DO
// Developnoteを見て引数のidから駒の名前(name_var)を返すプログラムを書こう
std::string Calc::id2name(size_t id) {
    if (id > 17 && id < 0)
        throw std::invalid_argument("Calc::id2name()");

    return Calc::name_var[id];
}

// TO DO : 上の逆 駒の名前(name_var)からid
size_t Calc::name2id(std::string name) {
    for (int i = 0; i < 17; i++)
    {
        if (name == Calc::name_var[i])
            
            break;
    }

    return i;
}