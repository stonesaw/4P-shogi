#pragma once
#include <string>


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
    
    Ban(Window window, int color, double base_scale = 0.8, double scale = 0.85, int line_width = 2) {
        int windowMinSize = min(window.width, window.height);
        this->base_scale = base_scale;
        this->base_width =  (double)windowMinSize * base_scale;
        this->base_height = (double)windowMinSize * base_scale;
        this->base_ox = (window.width - this->base_width) / 2;
        this->base_oy = (window.height - this->base_height) / 2;

        this->scale = scale;
        this->size = (int)(this->base_width * this->scale);
        this->ox = this->base_ox + (this->base_width - this->size) / 2;
        this->oy = this->base_oy + (this->base_height - this->size) / 2;
        this->masu_size = (this->size / 9);
        this->color = color;
        this->line_width = line_width * window.scale;
    }

    void DrawBase();
    void DrawFrame();
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
    void DrawBanShade(Ban ban);
};
