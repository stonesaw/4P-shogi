#pragma once
#include <string>
#include <vector>
#include <iostream>

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

    const std::vector<std::vector<std::vector<int>>> pieceMoveMap = {
        { },
        {
            {0, 1,  0},
            {0, -1, 0},
            {0, 0,  0}
        },
        {
            {1,  0, 1},
            {0,  0, 0},
            {0, -1, 0}
        },
        {
            {1,  1, 1},
            {0, -1, 0},
            {1,  0, 1}
        },
        {
            {1,  1, 1},
            {1, -1, 1},
            {0,  1, 0}
        },
        {
            {1,  1, 1},
            {1, -1, 1},
            {1,  1, 1}
        }
    };
};