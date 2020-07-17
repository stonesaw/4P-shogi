#pragma once

class Window {
public:
    int base_width;
    int base_height;
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
    int ox, oy;
    int width, height;
    int masu_size;
    int color;
    int line_width;
    double scale;
    

    Ban(Window window, int masu_size, unsigned int color, int line_width = 2) {
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
    int mapX, mapY;

    Mouse() {
        this->posX = -1, this->posY = -1;
        this->mapX = -1, this->mapY = -1;
    }

    void Update();
    bool isBanOn(Ban ban);
    void SetMapPoint(Ban ban);
    //int CheckMouseOnX(Window window, Ban ban);
    //int CheckMouseOnY(Window window, Ban ban);
    void DrawBanShade(Window window, Ban ban);
};
