#include <Application/Window.h>
#include <Application/Debug.h>
#include <Graphics/Renderer.h>
#include <Platform/Gfx.h>
#include "WinInput.h"
#include "WinWindow.h"

//Save from Windows.h intrusive defines
#include <Windows.h>
#include <windowsx.h>

namespace WinWindow
{
	//Private
	HWND hwnd;
	HINSTANCE hInstance;
	HDC hdc;
	const char *className = "Lil Engie Window";
	bool closeWindow;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

void WinWindow::Init(int width, int height, char *title)
{
	//Setup window class struct
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = className;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	//Register class name
	if (!RegisterClassEx(&wcex))
		Debug::Popup("Could not register window class.");

	//Create window
	hwnd = CreateWindow(
		className,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
		Debug::Popup("Could not create window.");

	//Get device context
	hdc = GetDC(hwnd);

	//Describe pixel format
	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;

	//Setup pixel format
	int pf = ChoosePixelFormat(hdc, &pfd);
	if (pf == 0)
		Debug::Popup("Could not choose pixel format.");
	if (SetPixelFormat(hdc, pf, &pfd) == FALSE)
		Debug::Popup("Could not set pixel format.");
	DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	//This is opengl and windows specific
	if (Gfx::api == Gfx::API::OpenGL)
	{
		HGLRC hglrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hglrc);
	}

	//Show the window
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

bool WinWindow::Open()
{
	return !closeWindow;
}

void WinWindow::PollEvents()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			closeWindow = true;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void WinWindow::SwapBuffer()
{
	SwapBuffers(hdc);
}

void WinWindow::SetFullScreen(bool mode, int widthBeforeFull, int heightBeforeFull)
{
	Debug::Log("My master did not tell me how to set full screen yet.", DebugType::Warning);
}

void WinWindow::GetWinPos(int *posX, int *posY)
{
	RECT r;
	GetWindowRect(hwnd, &r);
	*posX = r.left;
	*posY = r.top;
}

void WinWindow::Close()
{
	DestroyWindow(hwnd);
}

void WinWindow::Clean()
{
	
}

void* WinWindow::GetHWND()
{
	return (void*)hwnd;
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
		case WM_SIZE:
			Window::Resize(LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_XBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP:
		case WM_INPUT:
			WinInput::KeyCallback(msg, wParam, lParam);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
			break;
	}

	return 0;
}
