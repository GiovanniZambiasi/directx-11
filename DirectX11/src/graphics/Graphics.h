#pragma once
#include "GioTransform.h"
#include "IRenderingContext.h"
#include "RenderingSharedResources.h"

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

    RenderingSharedResources sharedResources{};
    GioTransform cameraTransform{};
    DirectX::XMMATRIX cameraMatrix{};

public:
    Graphics(HWND window, UINT width, UINT height);

    void Initialize();

    ID3D11Device* GetDevice() const  override { return device.Get(); }
    
    ID3D11DeviceContext* GetDeviceContext() const override  { return deviceContext.Get(); }

    DirectX::XMMATRIX GetCameraMatrix() const override;

    RenderingSharedResources& GetSharedResources() override { return sharedResources; }

    std::tuple<UINT, UINT> GetOutputDimensions() const { return {outputWidth, outputHeight}; }

    FLOAT GetAspectRatio() const { return static_cast<FLOAT>(outputHeight)/static_cast<FLOAT>(outputWidth); }

    GioTransform& GetCameraTransform() override { return cameraTransform; }
    
    void ClearBuffer(const GioColor& color);

    void UpdateCameraMatrix();
    
    void SwapBuffers();

private:
    void SetupSharedResources();

};
