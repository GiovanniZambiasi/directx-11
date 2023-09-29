#pragma once
#include "IRenderingContext.h"

class Box;
class InputLayout;
class VertexShader;
class PixelShader;
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

    std::shared_ptr<PixelShader> standardPixelShader{};
    std::shared_ptr<VertexShader> standardVertexShader{};
    std::shared_ptr<InputLayout> standardInputLayout{};

public:
    Graphics(HWND window, UINT width, UINT height);

    void Initialize();

    ID3D11Device* GetDevice() const  override { return device.Get(); }
    
    ID3D11DeviceContext* GetDeviceContext() const override  { return deviceContext.Get(); }

    DirectX::XMMATRIX GetProjectionMatrix() const override;
    
    std::tuple<UINT, UINT> GetOutputDimensions() const { return {outputWidth, outputHeight}; }

    FLOAT GetAspectRatio() const { return static_cast<FLOAT>(outputHeight)/static_cast<FLOAT>(outputWidth); }

    std::shared_ptr<PixelShader> GetStandardPixelShader() const { return standardPixelShader; }
    
    std::shared_ptr<VertexShader> GetStandardVertexShader() const { return standardVertexShader; }
    
    std::shared_ptr<InputLayout> GetStandardInputLayout() const { return standardInputLayout; }
    
    void ClearBuffer(const GioColor& color);
    
    void SwapBuffers();

};
