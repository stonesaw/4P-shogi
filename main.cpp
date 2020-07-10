#include "DxLib.h"

/*
    4P-shogi : 4l«Šû

    Author Sou, Fukasato, Chisato
*/


class Window {
public:
    int base_width = 640;
    int base_height = 480;
    double scale;
    int width;
    int height;

    Window(double scale) {
        this->scale = scale;
        this->width =  (int)(base_width  * this->scale);
        this->height = (int)(base_height * this->scale);
    }
};


class Ban {
public:
    int ox, oy;
    int width, height;
    int masu_size;
    int color;
    int line_width;
    
    Ban(Window window, int masu_size, unsigned int color, int line_width) {
        this->masu_size = masu_size * window.scale;
        this->width = this->masu_size * 9;
        this->height = this->masu_size * 9;
        this->ox = (window.width  - this->width) / 2;
        this->oy = (window.height - this->height) / 2;
        this->color = color;
        this->line_width = line_width;
    }

    void Draw(Window window);
};

void Ban::Draw(Window window) {
    DrawBox(this->ox, this->oy, this->ox + this->width, this->oy + this->height, this->color, TRUE);
    for (int y = 0; y < 10; y++)
        DrawBox(this->ox,                                                 this->oy + y * this->masu_size, 
                this->ox + this->width + this->line_width * window.scale, this->oy + y * this->masu_size + this->line_width * window.scale, GetColor(0, 0, 0), TRUE);
    for (int x = 0; x < 10; x++)
        DrawBox(this->ox + x * this->masu_size,                                     this->oy, 
                this->ox + x * this->masu_size + this->line_width * window.scale, this->oy + this->height,  GetColor(0, 0, 0), TRUE);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int Cr;

    Window window(3);
    Ban ban(window, 50, GetColor(240, 181, 46), 2);

    SetGraphMode(window.width, window.height, 32);
    SetBackgroundColor(255, 255, 255);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1) {
        return -1;
    }

    Cr = GetColor(255, 255, 255);

    // main loop
    while (1) {
        if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)) {
            DxLib_End();
            return 0;
        }

        ban.Draw(window);

        WaitTimer(10);
    }

    WaitKey();

    DxLib_End();

    return 0;
}
