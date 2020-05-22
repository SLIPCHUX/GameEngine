#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContex;
class VertexBuffer;

 class GraphicsEngine
{
public:
     GraphicsEngine();

     // Initialize the GraphicsEngine and DirectX 11 Device
     bool Init();

     // Release all the resources loaded
     bool Release();

    ~GraphicsEngine();

public:
    SwapChain* CreateSwapChain();

    DeviceContex* GetImmediateDeviceContex();

    VertexBuffer* CreateVertexBuffer();

    bool CreateShaders();

    bool SetShaders();

    void GetShaderBufferAndSize(void** bytecode, UINT* size);

public:
    static GraphicsEngine* get();

private:
    DeviceContex* m_imn_device_contex; 

private:
    ID3D11Device* m_d3d_device; // Устройство для рисования объектов

    D3D_FEATURE_LEVEL m_feature_level;

private:
    IDXGIDevice* m_dxgi_device; 

    IDXGIAdapter* m_dxgi_adapter;

    IDXGIFactory* m_dxgi_factory;

    ID3D11DeviceContext* m_imm_context;

private:
	ID3DBlob* m_vsblob = nullptr;

	ID3DBlob* m_psblob = nullptr;
	
    ID3D11VertexShader* m_vs = nullptr;
	
    ID3D11PixelShader* m_ps = nullptr;

private:
    friend class SwapChain;
    friend class VertexBuffer;
};

