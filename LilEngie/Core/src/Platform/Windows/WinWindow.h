#pragma once

struct GLFWwindow;

namespace WinWindow
{
	//Public


	void Init(int width, int height, char *title);
	bool Open();
	void PollEvents();
	void SwapBuffer();
	void SetFullScreen(bool mode, int widthBeforeFull, int heightBeforeFull);
	void Close();
	void Clean();
}
