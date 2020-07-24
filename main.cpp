#include <iostream>
#include <string>
#include <map>
#include "DxLib.h"
#include "General.h"
#include "Clac.h"

/*
    4P-shogi

    Author stonesaw
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    try {
        Window window(1.5); // able to change (screen scale)
        std::map<std::string, int> image = ImageLoader::Load({
            { "fu",      "./lib/image/fuhyou.png" },
            { "kyo",     "./lib/image/kyousha.png" },
            { "kei",     "./lib/image/keima.png" },
            { "gin",     "./lib/image/ginshou.png" },
            { "kin",     "./lib/image/kinshou.png" },
            { "kaku",    "./lib/image/kakugyou.png" },
            { "hisya",   "./lib/image/hisha.png" },
            { "ou",      "./lib/image/oushou.png" },
            { "tokin",   "./lib/image/tokin.png" },
            { "narikyo", "./lib/image/narikyou.png" },
            { "narikei", "./lib/image/narikei.png" },
            { "narigin", "./lib/image/narigin.png" },
            { "uma",     "./lib/image/ryuuma.png" },
            { "ryu",     "./lib/image/ryuuou.png" }
            });

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
                std::cout << "Exit!" << std::endl;
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
            ban.DrawPiece(calc, image);
            ban.DrawFrame();

            WaitTimer(10);
        }

        std::cout << "Exit!" << std::endl;
        WaitKey();
        DxLib_End();

    }
    catch (std::invalid_argument& e) {
        std::cout << "Argument Error : " << e.what() << std::endl;
        DxLib_End();
        return 0;
    }
    catch (...) {
        std::cout << "Error!" << std::endl;
        DxLib_End();
        return 0;
    }

    return 0;
}
