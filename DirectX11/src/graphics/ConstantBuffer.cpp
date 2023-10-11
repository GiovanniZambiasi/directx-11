﻿#include "pch.h"
#include "ConstantBuffer.h"

#include "ErrorHandling.h"
#include "IRenderingContext.h"

ConstantBuffer::ConstantBuffer(IRenderingContext& graphics, UINT inIndex, const void* data, UINT dataWidth)
    : index(inIndex)
{
    D3D11_BUFFER_DESC desc
    {
        // If the constant buffer is being initialized with null data, byteWidth is set to the arbitrary minimum of 16 bytes  
        data ? dataWidth : 16,
        D3D11_USAGE_DYNAMIC,
        D3D11_BIND_CONSTANT_BUFFER,
        D3D11_CPU_ACCESS_WRITE,
        0,
        // Stride unnecessary because this is not an index or vertex buffer
        0,
    };

    D3D11_SUBRESOURCE_DATA subresourceData
    {
            data,
    };
    
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateBuffer(&desc, data ? &subresourceData : nullptr, &buffer));
}

void ConstantBuffer::Update(IRenderingContext& graphics, const void* data, UINT dataWidth)
{
    D3D11_MAPPED_SUBRESOURCE subresource{};
    GIO_THROW_IF_FAILED(graphics.GetDeviceContext()->Map(buffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &subresource))
    memcpy(subresource.pData, data, dataWidth);
    graphics.GetDeviceContext()->Unmap(buffer.Get(), 0u);
}

void PixelConstantBuffer::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->PSSetConstantBuffers(GetIndex(), 1u, buffer.GetAddressOf());
}

void VertexConstantBuffer::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->VSSetConstantBuffers(GetIndex(), 1u, buffer.GetAddressOf());
}
