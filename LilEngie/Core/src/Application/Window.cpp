#include <iostream>
#include <Game/Game.h>
#include <Application/Debug.h>
#include <Input/Input.h>
#include <Graphics/Renderer.h>
#include <Platform/Windows/WinWindow.h>
#include "Window.h"

//Properites
namespace Window
{
	//Public
	int width = 1280;
	int height = 720;
	char title[] = "Lil Engie";

	//Private
	int widthBeforeFull;
	int heightBeforeFull;
}

void Window::Init()
{
	WinWindow::Init(width, height, title);
}

bool Window::Open()
{
	return WinWindow::Open();
}

void Window::PollEvents()
{
	WinWindow::PollEvents();
}

void Window::SwapBuffer()
{
	WinWindow::SwapBuffer();
}

void Window::SetFullScreen(bool mode)
{
	if (mode == true)
	{
		widthBeforeFull = width;
		heightBeforeFull = height;
	}

	WinWindow::SetFullScreen(mode, widthBeforeFull, heightBeforeFull);
}

void Window::Resize(int width, int height)
{
	Renderer::Resize(width, height);
	Window::width = width;
	Window::height = height;
}

void Window::Close()
{
	WinWindow::Close();
}

void Window::Clean()
{
	WinWindow::Clean();
}
