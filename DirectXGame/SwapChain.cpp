#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
}

bool SwapChain::Init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;

	// Структура описывающая цепь связей 
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));	// Очищаем её (заполнение нулями)
	desc.BufferCount = 1;	// Кол-во дополнительных буферов
	desc.BufferDesc.Width = width;	// Шырина буфера
	desc.BufferDesc.Height = height;	// Высота буфера
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// Формат пикселей RGBA
	desc.BufferDesc.RefreshRate.Numerator = 60;		// частота обновления
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// Назначение
	desc.OutputWindow = hwnd;	// Привязка к окну
	desc.SampleDesc.Count = 1;	
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;	// Оконный режим

	// Create the swap chain for the window indicated by HWND parameter
	HRESULT result = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);
	
	if (FAILED(result))
		return false;
	
	ID3D11Texture2D* buffer;
	result = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer));

	if (FAILED(result))
		return false;
	
	result = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(result))
		return false;


	return true;
}

bool SwapChain::Present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);
	return true;
}

bool SwapChain::Release()
{
	m_swap_chain->Release();
	delete this;
	return false;
}

SwapChain::~SwapChain()
{
}
