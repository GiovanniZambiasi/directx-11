#pragma once

class IRenderingContext
{
public:
    virtual ~IRenderingContext() = default;

    virtual ID3D11Device* GetDevice() const = 0;
    
    virtual ID3D11DeviceContext* GetDeviceContext() const = 0;
};
