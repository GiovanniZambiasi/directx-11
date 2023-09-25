#pragma once

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
    HWND outputWindow;
    int outputWidth;
    int outputHeight;
    
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain{};
    Microsoft::WRL::ComPtr<ID3D11Device> device{};
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext{};
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBufferView{};
    
public:
    Game() noexcept;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    Game(Game&&) = delete;
    Game& operator= (Game&&) = delete;

    void Initialize(HWND window, int width, int height);

    void Update();
    
    std::tuple<int, int> GetDefaultSize() const noexcept { return {1240, 720}; }

private:
    void SwapBuffers();

    void ClearBuffer(float r, float g, float b);

    void DrawTriangle();
    
};
