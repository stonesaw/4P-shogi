#include "DxLib.h"
#include "General.h"

/*
    4P-shogi : 4êlè´ä˚

    Author stonesaw
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Window window(2);
    Ban ban(window, 40, GetColor(255, 200, 65), 2);
    Mouse mouse;

    SetGraphMode(window.width, window.height, 32);
    SetBackgroundColor(255, 255, 255);
    ChangeWindowMode(TRUE);

    SetFontSize(32);

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
        window.DrawBG(255, 255, 255);
        ban.DrawBase(window);
        mouse.DrawBanShade(window, ban);
        ban.DrawFrame(window);

        WaitTimer(10);
    }

    WaitKey();
    DxLib_End();

    return 0;
}
