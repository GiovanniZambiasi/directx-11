#pragma once
#include "IRenderingContext.h"

struct GioColor;

class Graphics : public IRenderingContext
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

    ID3D11Device* GetDevice() const  override { return device.Get(); }
    
    ID3D11DeviceContext* GetDeviceContext() const override  { return deviceContext.Get(); }

    std::tuple<UINT, UINT> GetOutputDimensions() const { return {outputWidth, outputHeight}; }

    FLOAT GetAspectRatio() const { return static_cast<FLOAT>(outputHeight)/static_cast<FLOAT>(outputWidth); }
    
    void ClearBuffer(const GioColor& color);
    
    void SwapBuffers();

    void DrawTriangle(float angle, float x, float y);
    
};
