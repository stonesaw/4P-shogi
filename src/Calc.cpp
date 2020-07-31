#include "Clac.h"


Calc::Calc() {
    // size = 9+2 : check out of board
    this->board.resize(11, std::vector<Piece>(11, (-1, 0)));
    std::vector<std::vector<int>> opponentPieceStarter = rotate2dVector(this->pieceStarter, "reverse");
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            if (1 <= x && x <= 9 && 1 <= y && y <= 9) {
                if (y <= 3)      this->board.at(y).at(x) = Piece(opponentPieceStarter[y - 1][x - 1], 2);
                else if (7 <= y) this->board.at(y).at(x) = Piece(this->pieceStarter[y - 7][x - 1], 1);
                else             this->board.at(y).at(x) = Piece(0);
            }
            else {
                this->board.at(y).at(x) = Piece();
            }
        }
    }
    this->turn = 1;
}

void Calc::Update() {
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

std::string Calc::setMoveType(size_t id) {
    return std::string();
}


std::vector<std::vector<int>> Calc::GetPieceMoveMap(std::string name) {
    return pieceMoveMap[name];
}


// ˆø”‚Ìid‚©‚ç‹î‚Ì–¼‘O(name_var)‚ð•Ô‚·
/* •ÏX’† fukasato
std::string Calc::id2name(size_t id) {
    if (id > 17 && id < 0)
        throw std::invalid_argument("Calc::id2name()");

    return this->name_var[id];
}

// ‹î‚Ì–¼‘O(name_var)‚©‚çid‚ð•Ô‚·
/*size_t Calc::name2id(std::string name) {
    for (int i = 0; i < 17; i++)
    {
        if (name == this->name_var[i])
            int id = i;
            break;
    }
    return id;
<<<<<<< HEAD
}
=======
}
>>>>>>> be4c87524d9e2d58ba87ba895f4c3850fd046b25
*/
