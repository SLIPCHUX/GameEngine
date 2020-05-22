#include "DeviceContex.h"
#include "SwapChain.h"
#include "VertexBuffer.h"


DeviceContex::DeviceContex(ID3D11DeviceContext* device_contex)
	: m_device_contex(device_contex)
{

}

void DeviceContex::ClearTargetRenderColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha };

	m_device_contex->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_contex->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);
}

void DeviceContex::SetVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;

	m_device_contex->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_contex->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContex::DrawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_contex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_device_contex->Draw(vertex_count, start_vertex_index);
}

void DeviceContex::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MaxDepth = 0.0f;
	vp.MaxDepth = 1.f;

	m_device_contex->RSSetViewports(1, &vp);
}

bool DeviceContex::Release()
{
	m_device_contex->Release();
	delete this;
	return true;
}

DeviceContex::~DeviceContex()
{

}
