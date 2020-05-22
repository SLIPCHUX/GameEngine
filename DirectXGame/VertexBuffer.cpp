#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer()
	: m_buffer(0), m_layout(0)
{
}

bool VertexBuffer::Load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	if (m_buffer) m_buffer->Release();
	if (m_layout) m_layout->Release();

	D3D11_BUFFER_DESC buff_desc = {};	// First param
	buff_desc.Usage = D3D11_USAGE_DEFAULT;	// Usage by GPU
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// Bind this vertex to the graphics pipeline
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data;	// Second param
	init_data.pSysMem = list_vertices; // pointer of memory with list of vertices

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list; 

	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// SEMATCI NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT size_layout = ARRAYSIZE(layout);


	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
		return false;

	return true;
}

UINT VertexBuffer::GetSizeVertexList()
{
	return this->m_size_list;
}

bool VertexBuffer::Release()
{
	m_layout->Release();
	m_buffer->Release();
	delete this;
	return true;
}

VertexBuffer::~VertexBuffer()
{
}
