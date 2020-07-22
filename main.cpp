#include "DxLib.h"
#include "General.h"
#include "Clac.h"

/*
    4P-shogi : 4人将棋

    Author stonesaw
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Window window(1.5); // able to change (screen scale)
    Ban ban(window, GetColor(255, 200, 65));
    Mouse mouse;
    Calc calc;

    SetGraphMode(window.width, window.height, 32);
    SetBackgroundColor(255, 255, 255);
    ChangeWindowMode(TRUE);
    SetFontSize(ban.masu_size * 0.4);

    if (DxLib_Init() == -1) {
        return -1;
    }

    // main loop
    while (1) {
        if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)) {
            DxLib_End();
            return 0;
        }

        // update
        mouse.Update();
        mouse.SetMapPoint(ban);
        
        // draw
        window.DrawBG(240, 240, 240);
        ban.DrawBase();
        mouse.DrawBanShade(ban);
        ban.DrawPiece(calc);
        ban.DrawFrame();

        WaitTimer(10);
    }

    WaitKey();
    DxLib_End();

    return 0;
}
