#include "pch.h"
#include "Graphics.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "ErrorHandling.h"
#include "IndexBuffer.h"

using namespace Microsoft;

#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND window, int width, int height)
    : outputWindow(window), outputWidth(width), outputHeight(height)
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
}

void Graphics::Update(float timeSinceStart, float deltaTime)
{
    ClearBuffer(.7f,.9f,.7f);

    POINT cursorPos{};
    GetCursorPos(&cursorPos);

    std::tuple<float,float> halfDimensions{outputWidth/2.f, outputHeight/2.f};
    float cursorX = cursorPos.x/ std::get<0>(halfDimensions) -1.f;
    float cursorY = 1-(cursorPos.y/std::get<1>(halfDimensions) - 1.f);
    
    DrawTriangle(timeSinceStart, cursorX, cursorY);
    
    DrawTriangle(timeSinceStart, -cursorX, -cursorY);
    
    SwapBuffers();
}

void Graphics::SwapBuffers()
{
    GIO_THROW_IF_FAILED(swapChain->Present(1, 0));
}

void Graphics::ClearBuffer(float r, float g, float b)
{
    const float colors[] = { r,g,b };
    deviceContext->ClearRenderTargetView(backBufferView.Get(), colors);
    deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::DrawTriangle(float angle, float x, float y)
{
    struct Vertex
    {
        float x{0.f};
        float y{0.f};
        float z{0.f};
    };

    const Vertex vertices[] =
    {
        {-1.f, -1.f, -1.f},
        {1.f, -1.f, -1.f,},
        {-1.f, 1.f, -1.f,},
        {1.f, 1.f, -1.f, },
        {-1.f, -1.f, 1.f,},
        {1.f, -1.f, 1.f, },
        {-1.f, 1.f, 1.f, },
        {1.f, 1.f, 1.f, }
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

    std::vector<USHORT> indices
    {
        0, 2, 1, 2, 3, 1,
        1, 3, 5, 3, 7, 5,
        2, 6, 3, 3, 6, 7,
        4, 5, 7, 4, 7, 6,
        0, 4, 2, 2, 4, 6,
        0, 1, 4, 1, 5, 4
    };
    IndexBuffer indexBuffer{*this, indices};
    indexBuffer.Bind(*this);
    
    float aspectRatio = outputHeight/static_cast<float>(outputWidth);
    
    struct ConstantBuffer
    {
        DirectX::XMMATRIX transform{};
    };
    const ConstantBuffer constantBufferData
    {
        {
            XMMatrixTranspose(
            DirectX::XMMatrixRotationZ(angle) *
            DirectX::XMMatrixRotationX(angle) *
            DirectX::XMMatrixTranslation(x, y, 4.f) *
            DirectX::XMMatrixPerspectiveLH(1.0f, aspectRatio, 0.5f, 10.f)
            )
        }
    };
    WRL::ComPtr<ID3D11Buffer> constantBuffer{};
    D3D11_BUFFER_DESC constantBufferDesc
    {
        sizeof(constantBufferData),
        D3D11_USAGE_DYNAMIC,
        D3D11_BIND_CONSTANT_BUFFER,
        D3D11_CPU_ACCESS_WRITE,
        0,
        // Stride unnecessary because this is not an index or vertex buffer
        0,
    };
    D3D11_SUBRESOURCE_DATA constantBufferSubresource
    {
        &constantBufferData,
    };
    device->CreateBuffer(&constantBufferDesc, &constantBufferSubresource, &constantBuffer);

    deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
    
    struct OtherConstantBuffer
    {
        struct
        {
            float r;
            float g;
            float b;
            float a;
        } face_colors[6];
    };
    const OtherConstantBuffer otherConstantBufferData
    {
        {
            {1.f, 0.f, 1.f},
            {1.f, 0.f, 0.f},
            {0.f, 1.f, 0.f},
            {0.f, 0.f, 1.f},
            {1.f, 1.f, 0.f},
            {0.f, 1.f, 1.f},
        }
    };
    WRL::ComPtr<ID3D11Buffer> otherConstantBuffer{};
    D3D11_BUFFER_DESC otherConstantBufferDesc
    {
        sizeof(otherConstantBufferData),
        D3D11_USAGE_DYNAMIC,
        D3D11_BIND_CONSTANT_BUFFER,
        D3D11_CPU_ACCESS_WRITE,
        0,
        // Stride unnecessary because this is not an index or vertex buffer
        0,
    };
    D3D11_SUBRESOURCE_DATA otherConstantBufferSubresource
    {
        &otherConstantBufferData,
    };
    device->CreateBuffer(&otherConstantBufferDesc, &otherConstantBufferSubresource, &otherConstantBuffer);

    deviceContext->PSSetConstantBuffers(0, 1, otherConstantBuffer.GetAddressOf());
    
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
        {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    GIO_THROW_IF_FAILED(device->CreateInputLayout(inputElementDesc, static_cast<UINT>(std::size(inputElementDesc)), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), &inputLayout));
    deviceContext->IASetInputLayout(inputLayout.Get());
    
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
