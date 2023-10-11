﻿#pragma once
#include <vector>

#include "GioColor.h"
#include "GioTransform.h"
#include "IRenderingContext.h"
#include "RenderingSharedResources.h"

class Light;
class Box;
class InputLayout;
class VertexShader;
class PixelShader;

class Graphics : public IRenderingContext
{
    HWND outputWindow;
    UINT outputWidth;
    UINT outputHeight;
    GioColorF clearColor{};

    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain{};
    Microsoft::WRL::ComPtr<ID3D11Device> device{};
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext{};
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBufferView{};
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView{};

    RenderingSharedResources sharedResources{};
    GioTransform cameraTransform{};
    DirectX::XMMATRIX cameraMatrix{};

    std::vector<std::weak_ptr<Light>> lights{};

public:
    Graphics(HWND window, UINT width, UINT height, GioColorF inClearColor);

    void Initialize();

    ID3D11Device* GetDevice() const  override { return device.Get(); }
    
    ID3D11DeviceContext* GetDeviceContext() const override  { return deviceContext.Get(); }

    DirectX::XMMATRIX GetCameraMatrix() const override;

    RenderingSharedResources& GetSharedResources() override { return sharedResources; }

    std::tuple<UINT, UINT> GetOutputDimensions() const { return {outputWidth, outputHeight}; }

    FLOAT GetAspectRatio() const { return static_cast<FLOAT>(outputHeight)/static_cast<FLOAT>(outputWidth); }

    GioTransform& GetCameraTransform() override { return cameraTransform; }

    void PreRender();
    
    void SetLights(std::vector<std::weak_ptr<Light>>&& inLights) { lights = std::move(inLights); }

    void UpdateCameraMatrix();
    
    void SwapBuffers();

private:
    void ClearBuffer(const GioColorF& color);
    
    void SetupSharedResources();

    void UpdateLightBuffer();

};
