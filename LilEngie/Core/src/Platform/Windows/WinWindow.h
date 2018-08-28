#pragma once

struct GLFWwindow;

namespace WinWindow
{
	//Public
	extern GLFWwindow *window;

	void Init(int width, int height, char *title);
	bool Open();
	void SwapBuffers();
	void PollEvents();
	void SetFullScreen(bool mode, int widthBeforeFull, int heightBeforeFull);
	void Close();
	void Clean();
}
