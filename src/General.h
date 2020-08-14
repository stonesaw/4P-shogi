#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "DxLib.h"
#include "Clac.h"
#include <filesystem>


const std::filesystem::path PATH = std::filesystem::current_path();


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
    void DrawPiece(Calc calc, std::map<std::string, int> image);
};


class Mouse {
    bool is_click = false;
    //int beforePosX = -1, beforePosY = -1;

public:
    int posX = -1, posY = -1;
    int mapX = -1, mapY = -1;
    bool isChoose = false;
    int chooseX = -1, chooseY = -1;

    void Update();
    bool isBanOn(Ban ban);
    bool isClick();
    bool onPiece(Calc calc);
    void SetMapPoint(Ban ban);
    void DrawBanShade(Ban ban, Calc calc);
};


/* class ImageLoader */
class ImageLoader {
    static bool file_exists(const char* str);

public:
    // return : map<"name", handle>
    // using LoadGraph Because Don't use always
    static std::map<std::string, int> Load(std::vector<std::vector<std::string>> nameAndPath);
    static std::vector<std::vector<std::string>> data;
    static void currentDir();
};
