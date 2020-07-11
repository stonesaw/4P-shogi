#include "DxLib.h"
#include "General.h"


void Window::DrawBG(int red, int green, int blue) {
    DrawBox(0, 0, this->width, this->height, GetColor(red, green, blue), TRUE);
}

void Mouse::Update() {
    GetMousePoint(&posX, &posY);
}

bool Mouse::isBanOn(Ban ban) {
    if (ban.ox <= this->posX && this->posX <= ban.ox + ban.width &&
        ban.oy <= this->posY && this->posY <= ban.oy + ban.height) {
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

void Mouse::DrawBanShade(Window window, Ban ban) {
    if (this->isBanOn(ban)) {
        DrawBox(ban.ox +      this->mapX  * ban.masu_size, ban.oy +      this->mapY  * ban.masu_size,
                ban.ox + (this->mapX + 1) * ban.masu_size, ban.oy + (this->mapY + 1) * ban.masu_size,
            GetColor(240, 181, 46), TRUE);
    }
}


void Ban::DrawBase(Window window) {
    DrawBox(this->ox, this->oy, this->ox + this->width, this->oy + this->height, this->color, TRUE);
}

void Ban::DrawFrame(Window window) {
    for (int y = 0; y < 10; y++) {
        DrawBox(this->ox, this->oy + y * this->masu_size,
            this->ox + this->width + (this->line_width * window.scale), this->oy + y * this->masu_size + this->line_width * window.scale,
            GetColor(0, 0, 0), TRUE);
    }
    for (int x = 0; x < 10; x++) {
        DrawBox(this->ox + x * this->masu_size, this->oy,
            this->ox + x * this->masu_size + this->line_width * window.scale, this->oy + this->height,
            GetColor(0, 0, 0), TRUE);
    }
}

