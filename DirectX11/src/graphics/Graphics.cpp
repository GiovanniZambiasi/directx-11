#include "pch.h"
#include "Graphics.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "BindableTexture.h"
#include "ErrorHandling.h"
#include "GioColor.h"
#include "GioVertex.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Sampler.h"
#include "Shader.h"
#include "TransformationBuffer.h"

using namespace Microsoft;

#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND window, UINT width, UINT height)
    : outputWindow(window), outputWidth(width), outputHeight(height)
{
    DXGIInfoUtils::Init();
    
    outputWindow = window;
    outputWidth = std::max(width, 1u);
    outputHeight = std::max(height, 1u);
}

void Graphics::Initialize()
{
    DXGI_SWAP_CHAIN_DESC swapChainDescription
    {
        // A width/height of 0 means "use whatever dimensions the window has"
        DXGI_MODE_DESC
        {
            0,
            0,
            {0},
            DXGI_FORMAT_B8G8R8A8_UNORM,
            DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            DXGI_MODE_SCALING_UNSPECIFIED
        },
        // AA
        DXGI_SAMPLE_DESC{1, 0},
        // This buffer will be used as the render target of our pipeline
        DXGI_USAGE_RENDER_TARGET_OUTPUT,
        // 1 Here means 1 front + 1 back buffers
        1,
        outputWindow,
        true,
        DXGI_SWAP_EFFECT_DISCARD,
        0
    };

    GIO_THROW_IF_FAILED(D3D11CreateDeviceAndSwapChain(
    nullptr,
    D3D_DRIVER_TYPE_HARDWARE,
    nullptr,
    D3D11_CREATE_DEVICE_DEBUG,
    nullptr,
    0,
    D3D11_SDK_VERSION,
    &swapChainDescription,
    &swapChain,
    &device,
    nullptr,
    &deviceContext))
    
    ID3D11Resource* backBuffer{nullptr};
    
    GIO_THROW_IF_FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Resource),reinterpret_cast<void**>(&backBuffer)));
    
    GIO_THROW_IF_FAILED(device->CreateRenderTargetView(backBuffer, nullptr, &backBufferView));
    backBuffer->Release();

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc
    {
        true,
        D3D11_DEPTH_WRITE_MASK_ALL,
        D3D11_COMPARISON_LESS,
        false,
        0,
        0,        
    };
    WRL::ComPtr<ID3D11DepthStencilState> depthStencilState{};
    GIO_THROW_IF_FAILED(device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState))

    deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);

    WRL::ComPtr<ID3D11Texture2D> depthStencil{};
    D3D11_TEXTURE2D_DESC depthDescription
    {
        static_cast<UINT>(outputWidth),
        static_cast<UINT>(outputHeight),
        1,
        1,
        DXGI_FORMAT_D32_FLOAT,
        { 1, 0 },
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_DEPTH_STENCIL
    };
    GIO_THROW_IF_FAILED(device->CreateTexture2D(&depthDescription, nullptr, &depthStencil))

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc
    {
        DXGI_FORMAT_D32_FLOAT,
        D3D11_DSV_DIMENSION_TEXTURE2D
    };
    device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &depthStencilView);

    deviceContext->OMSetRenderTargets(1, backBufferView.GetAddressOf(), depthStencilView.Get());

    SetupSharedResources();
}

DirectX::XMMATRIX Graphics::GetCameraMatrix() const
{
    return cameraMatrix;
}

void Graphics::ClearBuffer(const GioColorF& color)
{
    deviceContext->ClearRenderTargetView(backBufferView.Get(), reinterpret_cast<const FLOAT*>(&color));
    deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    D3D11_VIEWPORT viewport
    {
        0,
        0,
        static_cast<FLOAT>(outputWidth),
        static_cast<FLOAT>(outputHeight),
        0,
        1.f
    };
    deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::UpdateCameraMatrix()
{
    GioVector camPos = cameraTransform.position;
    GioVector focusPos = cameraTransform.position + cameraTransform.GetForward();

    cameraMatrix =
        DirectX::XMMatrixLookAtLH(camPos, focusPos, GioVector{0.f, 1.f, 0.f}) *
        DirectX::XMMatrixPerspectiveLH(1.f, GetAspectRatio(), .5f, 100.f);
}

void Graphics::SwapBuffers()
{
    GIO_THROW_IF_FAILED(swapChain->Present(1, 0));
}

void Graphics::SetupSharedResources()
{
    sharedResources.standardPixelShader = std::make_shared<PixelShader>(*this, L"PixelShader.cso");
    sharedResources.standardVertexShader = std::make_shared<VertexShader>(*this, L"VertexShader.cso");
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc
    {
        {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(GioVertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(GioVertex, texCoords), D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    sharedResources.standardInputLayout = std::make_shared<InputLayout>(*this, inputElementDesc, sharedResources.standardVertexShader->GetBlob());
    sharedResources.texturedPixelShader = std::make_shared<PixelShader>(*this, L"TexturedPixelShader.cso");
    sharedResources.standardSampler = std::make_shared<Sampler>(*this);
    sharedResources.testTexture = std::make_shared<BindableTexture>(*this, L"res/texture.jpg");
    sharedResources.checkeredTexture = std::make_shared<BindableTexture>(*this, L"res/checkered.jpg");
    sharedResources.transformationBuffer = std::make_shared<TransformationBuffer>(*this, nullptr, 0u);
    std::vector<GioColorF> faceColors
    {
        {1.f, 0.f, 1.f},
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, 0.f, 1.f},
        {1.f, 1.f, 0.f},
        {0.f, 1.f, 1.f},
    };
    sharedResources.faceColorBuffer = std::make_shared<PixelConstantBuffer>(*this, faceColors.data(), static_cast<UINT>(faceColors.size() * sizeof(GioColorF)));
}

