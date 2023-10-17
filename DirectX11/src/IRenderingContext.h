#pragma once

struct AmbientLightParams;
class RenderingComponent;
struct LightParams;
struct GioTransform;
class RenderingResources;

class IRenderingContext
{
public:
    virtual ~IRenderingContext() = default;

    virtual ID3D11Device* GetDevice() const = 0;
    
    virtual ID3D11DeviceContext* GetDeviceContext() const = 0;

    virtual DirectX::XMMATRIX GetCameraMatrix() const = 0;

    virtual RenderingResources& GetSharedResources() = 0;
 
    virtual GioTransform& GetCameraTransform() = 0;

    virtual void AddLight(const LightParams& lightParams) = 0;

    virtual void SetAmbientLight(const AmbientLightParams& inLightParams) = 0;
    
};
