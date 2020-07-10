#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int Cr;
	double scale = 3;
	SetGraphMode(640*scale, 480*scale, 32);
	SetBackgroundColor(255, 255, 255);
	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1) {
		return -1;
	}

	Cr = GetColor(255, 255, 255);

	while (1)
	{
		DrawBox(100, 100, 150, 150, Cr, FALSE);
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE)) {
			DxLib_End();
			return 0;
		}

		WaitTimer(10);
	}

	WaitKey();

	DxLib_End();

	return 0;
}
