#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContex.h"
#include "VertexBuffer.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::Init()
{
	// DirectX API
	D3D_DRIVER_TYPE driver_types[] =	// ������ ��������� ��������������		
	{
		D3D_DRIVER_TYPE_HARDWARE,	
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = // ������ �������������� ������ DX
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_types = ARRAYSIZE(feature_levels);

	//ID3D11DeviceContext* m_imn_contex; 
	HRESULT result = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)	// ���������� �� �����������
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, 
			num_feature_types, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(result))
			break;
	}
	if (FAILED(result))
		return false;
	
	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgi_device));
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&m_dxgi_adapter));
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_dxgi_factory));

	m_imn_device_contex = new DeviceContex(m_imm_context);


	return true;
}

bool GraphicsEngine::Release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imn_device_contex->Release();
	m_d3d_device->Release();
	return false;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContex* GraphicsEngine::GetImmediateDeviceContex()
{
	return m_imn_device_contex;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

bool GraphicsEngine::CreateShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
	return true;
}

bool GraphicsEngine::SetShaders()
{
	m_imm_context->VSSetShader(m_vs, nullptr, 0);
	m_imm_context->PSSetShader(m_ps, nullptr, 0);
	return true;
}


void GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	
	return &engine;
}



GraphicsEngine::~GraphicsEngine()
{

}


