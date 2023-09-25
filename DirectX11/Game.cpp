//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <iostream>

#include "ErrorHandling.h"

extern void ExitGame() noexcept;

using namespace DirectX;

Game::Game() noexcept :
    outputWindow(nullptr),
    outputWidth(800),
    outputHeight(600)
{}

void Game::Initialize(HWND window, int width, int height)
{
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
    0,
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
    ClearBuffer(1,0,0);
    SwapBuffers();
}

void Game::SwapBuffers()
{
    GIO_THROW_IF_FAILED(swapChain->Present(1, 0));
}

void Game::ClearBuffer(float r, float g, float b)
{
    const float colors[] = { r,g,b };
    deviceContext->ClearRenderTargetView(backBufferView, colors);
}
