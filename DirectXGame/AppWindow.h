#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContex.h"
#include "VertexBuffer.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// ������������ ����� Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	SwapChain* m_swap_chain;

	VertexBuffer* m_vertex_buffer;
};

