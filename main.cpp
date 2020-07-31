#include "DxLib.h"
#include "General.h"
#include "Clac.h"

/*
    4P-shogi

    Author stonesaw
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    try {
        //std::cout << "Current Directory: " << PATH << std::endl;
        //ImageLoader::currentDir();
        Window window(1.5); // able to change (screen scale)
        std::map<std::string, int> image = ImageLoader::Load(ImageLoader::data);

        Ban ban(window, GetColor(255, 200, 65));
        Mouse mouse;
        Calc calc;

        SetGraphMode(window.width, window.height, 32);
        SetBackgroundColor(255, 255, 255);
        ChangeWindowMode(TRUE);
        SetFontSize((int)(ban.masu_size * 0.4));

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
            calc.Update();
            
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
    catch (std::runtime_error& e) {
        std::cout << "Runtime Error : " << e.what() << std::endl;
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
