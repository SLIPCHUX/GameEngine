#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class DeviceContex
{
public:
	DeviceContex(ID3D11DeviceContext* device_contex);
	
	void ClearTargetRenderColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);

	void SetVertexBuffer(VertexBuffer* vertex_buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);

	void SetViewportSize(UINT width, UINT height);

	bool Release();

	~DeviceContex();

private:
	ID3D11DeviceContext* m_device_contex; // Контекст устройста (рисование)
};

