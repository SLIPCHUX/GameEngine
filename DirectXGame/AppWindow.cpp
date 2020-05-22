#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

AppWindow::AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->Init();
	
	m_swap_chain = GraphicsEngine::get()->CreateSwapChain();
	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		//X - Y - Z
		{ -0.5f, -0.5f, 0.0f },	// Pos 1
		{  0.0f,  0.5f, 0.0f },	// Pos 2
		{  0.5f, -0.5f, 0.0f }	// Pos 3
	};
	m_vertex_buffer = GraphicsEngine::get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(list);
	
	GraphicsEngine::get()->CreateShaders();

	UINT size_shader = 0;
	void* shader_byte_code = nullptr;
	GraphicsEngine::get()->GetShaderBufferAndSize(&shader_byte_code, &size_shader);


	m_vertex_buffer->Load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->GetImmediateDeviceContex()->ClearTargetRenderColor(this->m_swap_chain, 1, 1, 0, 1);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::get()->GetImmediateDeviceContex()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->SetShaders();
	GraphicsEngine::get()->GetImmediateDeviceContex()->SetVertexBuffer(m_vertex_buffer);

	GraphicsEngine::get()->GetImmediateDeviceContex()->DrawTriangleList(m_vertex_buffer->GetSizeVertexList(), 0);
	m_swap_chain->Present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vertex_buffer->Release();
	m_swap_chain->Release();
	GraphicsEngine::get()->Release();


}

AppWindow::~AppWindow()
{
}
