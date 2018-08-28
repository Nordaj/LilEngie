#include <Application/Window.h>
#include <Application/Debug.h>
#include <Graphics/Renderer.h>
#include "WinWindow.h"

//Save from Windows.h intrusive defines
#include <Windows.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace WinWindow
{
	//Public
	GLFWwindow *window;

	//Private
	HWND hwnd;

	void Resize(GLFWwindow *win, int width, int height);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

void WinWindow::Init(int width, int height, char *title)
{
	//Init glfw
	if (!glfwInit())
		ERROR("Could not init glfw");

	//Create window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);

	//Setup resize callback
	glfwSetFramebufferSizeCallback(window, Resize);

	//Setup my own window stuff
	hwnd = glfwGetWin32Window(window);
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
}

bool WinWindow::Open()
{
	return !glfwWindowShouldClose(window);
}

void WinWindow::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void WinWindow::PollEvents()
{
	glfwPollEvents();
}

void WinWindow::SetFullScreen(bool mode, int widthBeforeFull, int heightBeforeFull)
{
	if (mode == true)
	{
		const GLFWvidmode *winMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, winMode->width, winMode->height, 0);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, 15, 45, widthBeforeFull, heightBeforeFull, 0);
	}
}

void WinWindow::Close()
{
	glfwDestroyWindow(window);
}

void WinWindow::Clean()
{
	glfwTerminate();
}

void WinWindow::Resize(GLFWwindow *win, int width, int height)
{
	Renderer::Resize(width, height);
	Window::width = width;
	Window::height = height;
}

LRESULT CALLBACK WinWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
			break;
	}

	return 0;
}
