#pragma once

class Window {
public:
    int base_width = 640;
    int base_height = 480;
    double scale;
    int width;
    int height;

    Window(double scale) {
        this->scale = scale;
        this->width = (int)(base_width * this->scale);
        this->height = (int)(base_height * this->scale);
    }

    void DrawBG(int red, int green, int blue);
};


class Ban {
public:
    int ox, oy;
    int width, height;
    int masu_size;
    int color;
    int scale;
    int line_width;
    

    Ban(Window window, int masu_size, unsigned int color, int line_width) {
        this->masu_size = (int)(masu_size * window.scale);
        this->width = this->masu_size * 9;
        this->height = this->masu_size * 9;
        this->ox = (window.width - this->width) / 2;
        this->oy = (window.height - this->height) / 2;
        this->color = color;
        this->scale = window.scale;
        this->line_width = line_width;
    }

    void DrawBase(Window window);
    void DrawFrame(Window window);
};


class Mouse {
public:
    int posX, posY;
    int mapX = -2, mapY = -2;

    void Update();
    bool isBanOn(Ban ban);
    void SetMapPoint(Ban ban);
    //int CheckMouseOnX(Window window, Ban ban);
    //int CheckMouseOnY(Window window, Ban ban);
    void DrawBanShade(Window window, Ban ban);
};
