#include "pch.h"
#include "ConstantBuffer.h"

#include "ErrorHandling.h"
#include "Graphics.h"

ConstantBuffer::ConstantBuffer(Graphics& graphics, const void* data, UINT dataWidth)
{
    D3D11_BUFFER_DESC desc
    {
        dataWidth,
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
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateBuffer(&desc, &subresourceData, &buffer));
}

void PixelConstantBuffer::Bind(Graphics& graphics)
{
    graphics.GetDeviceContext()->PSSetConstantBuffers(0u, 1u, buffer.GetAddressOf());
}

void VertexConstantBuffer::Bind(Graphics& graphics)
{
    graphics.GetDeviceContext()->VSSetConstantBuffers(0u, 1u, buffer.GetAddressOf());
}
