#pragma once

namespace WinWindow
{
	void Init(int width, int height, char *title);
	bool Open();
	void PollEvents();
	void SwapBuffer();
	void SetFullScreen(bool mode, int widthBeforeFull, int heightBeforeFull);
	void GetWinPos(int *posX, int *posY);
	void Close();
	void Clean();
	void* GetHWND();
}
