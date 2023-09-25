#include "pch.h"
#include "Game.h"
#include <iostream>
#include "ErrorHandling.h"
#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

extern void ExitGame() noexcept;

using namespace DirectX;

using namespace Microsoft;

Game::Game() noexcept :
    outputWindow(nullptr),
    outputWidth(800),
    outputHeight(600)
{
}

void Game::Initialize(HWND window, int width, int height)
{
    DXGIInfoUtils::Init();
    
    outputWindow = window;
    outputWidth = std::max(width, 1);
    outputHeight = std::max(height, 1);

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
        window,
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
}

void Game::Update()
{
    ClearBuffer(.7f,.9f,.7f);

    DrawTriangle();
    
    SwapBuffers();
}

void Game::SwapBuffers()
{
    GIO_THROW_IF_FAILED(swapChain->Present(1, 0));
}

void Game::ClearBuffer(float r, float g, float b)
{
    const float colors[] = { r,g,b };
    deviceContext->ClearRenderTargetView(backBufferView.Get(), colors);
}

void Game::DrawTriangle()
{
    struct Vertex
    {
        float x{0.f};
        float y{0.f};
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    const Vertex vertices[] =
    {
        {0.f, .5f, 255, 0, 0},
        {.5f, -.5f, 0, 255, 0},
        {-.5f, -.5f, 0, 0, 255},
    };

    const UINT stride = sizeof(Vertex);
    const UINT offset = 0u;

    // Create vertex buffer
    WRL::ComPtr<ID3D11Buffer> vertexBuffer{};
    D3D11_BUFFER_DESC vertexBufferDesc
    {
        sizeof(vertices),
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_VERTEX_BUFFER,
        0,
        0,
        stride
    };
    D3D11_SUBRESOURCE_DATA vertexBufferData{vertices};
    GIO_THROW_IF_FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer));
    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

    unsigned short indices[]
    {
        0,1,2,
    };
    WRL::ComPtr<ID3D11Buffer> indexBuffer{};
    D3D11_BUFFER_DESC indexBufferDesc
    {
        sizeof(indices),
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_INDEX_BUFFER,
        0,
        0,
        sizeof(unsigned short),
    };
    D3D11_SUBRESOURCE_DATA indexBufferData{indices};
    GIO_THROW_IF_FAILED(device->CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer));
    deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    
    // Load shaders
    WRL::ComPtr<ID3DBlob> shaderBlob{};
    
    GIO_THROW_IF_FAILED(D3DReadFileToBlob(L"PixelShader.cso", &shaderBlob));
    WRL::ComPtr<ID3D11PixelShader> pixelShader{};
    GIO_THROW_IF_FAILED(device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &pixelShader));
    deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);
    
    GIO_THROW_IF_FAILED(D3DReadFileToBlob(L"VertexShader.cso", &shaderBlob));
    WRL::ComPtr<ID3D11VertexShader> vertexShader{};
    GIO_THROW_IF_FAILED(device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &vertexShader));
    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    
    // Create input layout
    WRL::ComPtr<ID3D11InputLayout> inputLayout{};
    const D3D11_INPUT_ELEMENT_DESC inputElementDesc[]
    {
        {"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, offsetof(Vertex, r), D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    GIO_THROW_IF_FAILED(device->CreateInputLayout(inputElementDesc, static_cast<UINT>(std::size(inputElementDesc)), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), &inputLayout));
    deviceContext->IASetInputLayout(inputLayout.Get());
    
    deviceContext->OMSetRenderTargets(1, backBufferView.GetAddressOf(), nullptr);
    
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
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
    
    deviceContext->DrawIndexed(static_cast<UINT>(std::size(indices)), 0, 0);
}
