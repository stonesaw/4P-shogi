#include "DxLib.h"
#include "General.h"
#include "Clac.h"


/* class Window */
void Window::DrawBG(int red, int green, int blue) {
    DrawBox(0, 0, this->width, this->height, GetColor(red, green, blue), TRUE);
}


/* class Mouse */
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


/* class Ban */
Ban::Ban(Window window, int color, double base_scale, double scale, int line_width) {
    int windowMinSize = min(window.width, window.height);
    this->base_scale = base_scale;
    this->base_width = (double)windowMinSize * base_scale;
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

void Ban::DrawPiece(Calc calc) {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            DrawFormatString(this->ox + this->masu_size * x, this->oy + this->masu_size * y,
                GetColor(0, 0, 0), "%d:%d", calc.board[y + 1][x + 1].player, calc.board[y + 1][x + 1].id);
        }
    }
}
