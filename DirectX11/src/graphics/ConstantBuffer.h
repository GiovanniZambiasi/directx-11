#pragma once
#include "IBindable.h"

class ConstantBuffer : public IBindable
{
protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{};

    UINT index;
    
public:
    ConstantBuffer(IRenderingContext& graphics, UINT inIndex, const void* data, UINT dataWidth);

    void Update(IRenderingContext& graphics, const void* data, UINT dataWidth);

    UINT GetIndex() const { return index; }
};

class PixelConstantBuffer : public ConstantBuffer
{
public:
    PixelConstantBuffer(IRenderingContext& graphics, UINT inIndex, const void* data, UINT dataWidth)
        : ConstantBuffer(graphics, inIndex, data, dataWidth)
    { }

    void Bind(IRenderingContext& graphics) override;
};

class VertexConstantBuffer : public ConstantBuffer
{
public:
    VertexConstantBuffer(IRenderingContext& graphics, UINT inIndex, const void*  data, UINT dataWidth)
        : ConstantBuffer(graphics, inIndex, data, dataWidth)
    {  }

    void Bind(IRenderingContext& graphics) override;
};