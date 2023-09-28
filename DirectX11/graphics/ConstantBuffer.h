#pragma once
#include "IBindable.h"

class ConstantBuffer : public IBindable
{
protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
    
public:
    ConstantBuffer(Graphics& graphics, const void* data, UINT dataWidth);
    
};

class PixelConstantBuffer : public ConstantBuffer
{
public:
    PixelConstantBuffer(Graphics& graphics, const void* data, UINT dataWidth)
        : ConstantBuffer(graphics, data, dataWidth)
    { }

    void Bind(Graphics& graphics) override;
};

class VertexConstantBuffer : public ConstantBuffer
{
public:
    VertexConstantBuffer(Graphics& graphics, const void*  data, UINT dataWidth)
        : ConstantBuffer(graphics, data, dataWidth)
    {  }

    void Bind(Graphics& graphics) override;
};