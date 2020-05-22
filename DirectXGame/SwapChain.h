#pragma once
#include <d3d11.h>

class DeviceContex;

class SwapChain
{
public:
	SwapChain();

	// Initialize SwapChain for a window
	bool Init(HWND hwnd, UINT width, UINT height);

	bool Present(bool vsync);

	// Release SwapChain
	bool Release();

	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain;	// Цепь связи буфера с экраном

	ID3D11RenderTargetView* m_rtv;

private:
	friend class DeviceContex;
};

