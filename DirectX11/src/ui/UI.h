#pragma once

class UI
{
public:
    UI(HWND window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
    
    ~UI();

    void PreRender();

    void Render();

    void Update();
};
