#pragma once

class Graphics
{
    HWND outputWindow;
    int outputWidth;
    int outputHeight;

    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain{};
    Microsoft::WRL::ComPtr<ID3D11Device> device{};
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext{};
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBufferView{};
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView{};
    
public:
    Graphics(HWND window, int width, int height);

    void Update(float timeSinceStart, float deltaTime);

    ID3D11Device* GetDevice() const { return device.Get(); }
    
    ID3D11DeviceContext* GetDeviceContext() const { return deviceContext.Get(); }
    
private:
    void SwapBuffers();

    void ClearBuffer(float r, float g, float b);

    void DrawTriangle(float angle, float x, float y);
    
};
