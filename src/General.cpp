#include "DxLib.h"
#include "General.h"



void Window::DrawBG(int red, int green, int blue) {
    DrawBox(0, 0, this->width, this->height, GetColor(red, green, blue), TRUE);
}


void Mouse::Update() {
    GetMousePoint(&posX, &posY);
}

bool Mouse::isBanOn(Ban ban) {
    if (ban.ox <= this->posX && this->posX <= ban.ox + ban.size &&
        ban.oy <= this->posY && this->posY <= ban.oy + ban.size) {
        return true;
    }
    else {
        return false;
    }
}

void Mouse::SetMapPoint(Ban ban) {
    if (this->isBanOn(ban)) {
        this->mapX = (this->posX - ban.ox) / ban.masu_size;
        this->mapY = (this->posY - ban.oy) / ban.masu_size;
    }
    else {
        this->mapX = -1;
        this->mapY = -1;
    }
}

void Mouse::DrawBanShade(Ban ban) {
    if (this->isBanOn(ban)) {
        DrawBox(ban.ox +  this->mapX      * ban.masu_size, ban.oy +  this->mapY      * ban.masu_size,
                ban.ox + (this->mapX + 1) * ban.masu_size, ban.oy + (this->mapY + 1) * ban.masu_size,
            GetColor(240, 181, 46), TRUE);
    }
}


/*
BanBase::BanBase(Window window, std::string type, int ox, int oy, int width = 0, int height = 0, double scale = 1.0, int color = GetColor(0, 0, 0)) {
    this->scale = scale;
    this->color = color;
    if (type == "square") {
        this->type = type;
        double windowSize = pow(window.width, 2.0) + pow(window.height, 2.0);
        int size = sqrt(windowSize * pow(scale, 2.0));
        this->width = size;
        this->height = size;
    }
    else if (type == "rect") {

    }
    else {
        throw stderr;
    }
}
*/


void Ban::DrawBase() {
    DrawBox(this->base_ox, this->base_oy, this->base_ox + this->base_width, this->base_oy + this->base_height, this->color, TRUE);
}


void Ban::DrawFrame() {
    for (int y = 0; y < 10; y++) {
        DrawBox(this->ox,              this->oy + y * this->masu_size,
                this->ox + this->size, this->oy + y * this->masu_size + this->line_width,
                GetColor(0, 0, 0), TRUE);
    }
    for (int x = 0; x < 10; x++) {
        DrawBox(this->ox + x * this->masu_size,                    this->oy,
                this->ox + x * this->masu_size + this->line_width, this->oy + this->size,
                GetColor(0, 0, 0), TRUE);
    }
}

