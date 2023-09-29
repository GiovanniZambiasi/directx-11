#pragma once
#include "IBindable.h"

class ConstantBuffer : public IBindable
{
protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};
    
public:
    ConstantBuffer(IRenderingContext& graphics, const void* data, UINT dataWidth);

    void Update(IRenderingContext& graphics, const void* data, UINT dataWidth);
};

class PixelConstantBuffer : public ConstantBuffer
{
public:
    PixelConstantBuffer(IRenderingContext& graphics, const void* data, UINT dataWidth)
        : ConstantBuffer(graphics, data, dataWidth)
    { }

    void Bind(IRenderingContext& graphics) override;
};

class VertexConstantBuffer : public ConstantBuffer
{
public:
    VertexConstantBuffer(IRenderingContext& graphics, const void*  data, UINT dataWidth)
        : ConstantBuffer(graphics, data, dataWidth)
    {  }

    void Bind(IRenderingContext& graphics) override;
};