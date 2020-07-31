#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "DataLoader.h"

class Data {
public:
    const std::vector<std::string> name_var = {
        "enpty", "fu",    "kyo",     "kei",     "gin",     "kin",  "kaku", "hisya", "ou",
                 "tokin", "narikyo", "narikei", "narigin", "none", "uma",  "ryu",   "none"
    };

    const std::vector<std::vector<int>> pieceStarter = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 6, 0, 0, 0, 0, 0, 7, 0},
        {2, 3, 4, 5, 8, 5, 4, 3, 2}
    };

    //std::vector<std::vector<int>> pieceMoveMap = {
    //    {0, 1, 0},
    //    {0, 0, 0},
    //    {0, 0, 0}
    //};

    std::map<std::string, std::vector<std::vector<int>>> pieceMoveMap = DataLoader::LoadMap("src/lib/data/piece.txt");
};