#pragma once

struct GioColor;

class Graphics
{
    HWND outputWindow;
    UINT outputWidth;
    UINT outputHeight;

    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain{};
    Microsoft::WRL::ComPtr<ID3D11Device> device{};
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext{};
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBufferView{};
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView{};
    
public:
    Graphics(HWND window, UINT width, UINT height);

    ID3D11Device* GetDevice() const { return device.Get(); }
    
    ID3D11DeviceContext* GetDeviceContext() const { return deviceContext.Get(); }

    std::tuple<UINT, UINT> GetOutputDimensions() const { return {outputWidth, outputHeight}; }

    FLOAT GetAspectRatio() const { return static_cast<FLOAT>(outputHeight)/static_cast<FLOAT>(outputWidth); }
    
    void ClearBuffer(const GioColor& color);
    
    void SwapBuffers();

    void DrawTriangle(float angle, float x, float y);
    
};
