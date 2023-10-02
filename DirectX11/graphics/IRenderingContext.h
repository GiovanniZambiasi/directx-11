#pragma once

struct GioTransform;
struct RenderingSharedResources;

class IRenderingContext
{
public:
    virtual ~IRenderingContext() = default;

    virtual ID3D11Device* GetDevice() const = 0;
    
    virtual ID3D11DeviceContext* GetDeviceContext() const = 0;

    virtual DirectX::XMMATRIX GetCameraMatrix() const = 0;

    virtual RenderingSharedResources& GetSharedResources() = 0;
 
    virtual GioTransform& GetCameraTransform() = 0;

};
