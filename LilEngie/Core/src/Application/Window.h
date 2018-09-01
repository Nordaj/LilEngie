#pragma once

namespace Window
{
	//Public
	extern int width;
	extern int height;
	extern char title[];

	void Init();
	bool Open();
	void PollEvents();
	void SwapBuffer();
	void SetFullScreen(bool mode);
	void Resize(int width, int height);
	void GetWinPos(int *posX, int *posY);
	void Close();
	void Clean();
}
