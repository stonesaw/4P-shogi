#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Clac.h"


class Window {
    int base_width;
    int base_height;
public:
    double scale;
    int width;
    int height;

    Window(double scale = 1.0, int width = 640, int height = 480) {
        this->scale = scale;
        this->base_width = width;
        this->base_height = height;
        this->width = (int)(base_width * this->scale);
        this->height = (int)(base_height * this->scale);
    }

    void DrawBG(int red, int green, int blue);
};


class Ban {
public:
    int base_ox, base_oy;
    int base_width, base_height;
    double base_scale;
    int ox, oy;
    int size;
    double scale;
    int color;
    int masu_size;
    int line_width;
    
    Ban(Window window, int color, double base_scale = 0.8, double scale = 0.85, int line_width = 2);

    void DrawBase();
    void DrawFrame();
    void DrawPiece(Calc calc);
};


class Mouse {
public:
    int posX, posY;
    int mapX, mapY;

    Mouse() {
        this->posX = -1, this->posY = -1;
        this->mapX = -1, this->mapY = -1;
    }

    void Update();
    bool isBanOn(Ban ban);
    void SetMapPoint(Ban ban);
    void DrawBanShade(Ban ban);
};

/* func ImageLoader */
inline bool file_exists(const char* str) {
    std::ifstream fs(str);
    return fs.is_open();
}


inline std::map<std::string, int> imageLoader(std::vector<std::vector<const char*>> nameAndPath) {
    std::map<std::string, int> map;
    for (size_t i = 0; i < nameAndPath.size(); i++) {
        if (file_exists(nameAndPath.at(i).at(1))) 
            throw std::invalid_argument("ImageLoder wrong to Path!");
        map[nameAndPath.at(i).at(0)] = LoadGraph(nameAndPath.at(i).at(1));
    }
    return map;
}
