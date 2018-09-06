#include <d3d11_4.h>
#include <Application/Debug.h>
#include <Application/Window.h>
#include "../Windows/WinWindow.h"
#include "../Gfx.h"
#include "DXRenderer.h"

namespace DXRenderer
{
	//Private
	IDXGISwapChain *swapchain;
	ID3D11Device *device;
	ID3D11DeviceContext *devCtx;
	ID3D11RenderTargetView *renderTargetView;
	ID3D11Texture2D *depthStencilBuffer;
	ID3D11DepthStencilState *depthStencilState;
	ID3D11DepthStencilView *depthStencilView;
	float backgroundColor[4];

	unsigned int TranslateBlendingMode(Gfx::BlendFunction func);
	bool GetRefreshRate(float *numerator, float *denominator);
	bool DeviceAndSwapChain(float numerator, float denominator);
	bool MakeRenderTargetView();
	bool SetupDepthStencilBuffer();
}

void DXRenderer::SetClearColor(float r, float g, float b, float a)
{
	backgroundColor[0] = r;
	backgroundColor[1] = g;
	backgroundColor[2] = b;
	backgroundColor[3] = a;
}

bool DXRenderer::Init()
{
	HRESULT result;

	float numerator, denominator;
	if (!GetRefreshRate(&numerator, &denominator))
		return false;

	if (!DeviceAndSwapChain(numerator, denominator))
		return false;

	if (!MakeRenderTargetView())
		return false;

	if (!SetupDepthStencilBuffer())
		return false;

	//Set the render target views
	devCtx->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	return true;
}

//TODO
void DXRenderer::SetBlendingMode(Gfx::BlendFunction source, Gfx::BlendFunction destination)
{

}

//TODO
void DXRenderer::DepthTest(bool mode)
{

}

void DXRenderer::Render()
{
	swapchain->Present(1, 0);
}

void DXRenderer::Clear()
{
	devCtx->ClearRenderTargetView(renderTargetView, backgroundColor);
	devCtx->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);
}

//TODO
void DXRenderer::Blending(bool mode)
{

}

//TODO
void DXRenderer::Viewport(int x, int y, int width, int height)
{

}

//TODO
void DXRenderer::SubVertData(unsigned int vbo, int size, void *data)
{

}

void DXRenderer::Shutdown()
{
	swapchain->Release();
	renderTargetView->Release();
	devCtx->Release();
	device->Release();
	depthStencilBuffer->Release();
	depthStencilState->Release();
	depthStencilView->Release();
}

//TODO?
unsigned int DXRenderer::TranslateBlendingMode(Gfx::BlendFunction func)
{
	return 0;
}

bool DXRenderer::GetRefreshRate(float *numerator, float *denominator)
{
	//As of now, do this. Might want to change later
	*numerator = 60;
	*denominator = 1;

	return true;
}

bool DXRenderer::DeviceAndSwapChain(float numerator, float denominator)
{
	HRESULT result;

	//Swap chain description
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Window::width;
	sd.BufferDesc.Height = Window::height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = numerator;
	sd.BufferDesc.RefreshRate.Denominator = denominator;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = (HWND)WinWindow::GetHWND();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//Feature level required (probably should change later)
	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_1;

	//Create the device and swap chain
	result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&swapchain,
		&device,
		NULL,
		&devCtx
	);
	if (FAILED(result)) return false;

	return true;
}

bool DXRenderer::MakeRenderTargetView()
{
	HRESULT result;

	//Get pointer to back of buffer
	ID3D11Texture2D *backBuffer;
	result = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (FAILED(result)) return false;

	//Create render target view
	result = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	if (FAILED(result)) return false;

	//Cleanup
	backBuffer->Release();
	backBuffer = nullptr;

	return true;
}

bool DXRenderer::SetupDepthStencilBuffer()
{
	HRESULT result;

	//Stencil buffer setup
	D3D11_DEPTH_STENCIL_DESC sbd = {};
	sbd.DepthEnable = true;
	sbd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	sbd.DepthFunc = D3D11_COMPARISON_LESS;
	sbd.StencilEnable = true;
	sbd.StencilReadMask = 255;
	sbd.StencilWriteMask = 255;
	sbd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	sbd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	sbd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	sbd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	sbd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	sbd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	sbd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	sbd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	result = device->CreateDepthStencilState(&sbd, &depthStencilState);
	if (FAILED(result)) return false;
	devCtx->OMSetDepthStencilState(depthStencilState, 1);

	//Create texture for the depth stencil buffer
	D3D11_TEXTURE2D_DESC dbd = {};
	dbd.Width = Window::width;
	dbd.Height = Window::height;
	dbd.MipLevels = 1;
	dbd.ArraySize = 1;
	dbd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dbd.SampleDesc.Count = 1;
	dbd.SampleDesc.Quality = 0;
	dbd.Usage = D3D11_USAGE_DEFAULT;
	dbd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dbd.CPUAccessFlags = 0;
	dbd.MiscFlags = 0;
	result = device->CreateTexture2D(&dbd, NULL, &depthStencilBuffer);
	if (FAILED(result)) return false;

	//Create the depth/stencil buffer view and use the texture
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;
	result = device->CreateDepthStencilView(depthStencilBuffer, &dsvd, &depthStencilView);
	if (FAILED(result)) return false;

	return true;
}
