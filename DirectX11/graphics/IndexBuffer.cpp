#include "pch.h"
#include "IndexBuffer.h"

#include "ErrorHandling.h"
#include "IRenderingContext.h"

IndexBuffer::IndexBuffer(IRenderingContext& graphics, const std::vector<USHORT>& indices)
{
    D3D11_BUFFER_DESC desc
        {
            static_cast<UINT>(indices.size() * sizeof(USHORT)),
            D3D11_USAGE_DEFAULT,
            D3D11_BIND_INDEX_BUFFER,
            0,
            0,
            sizeof(USHORT),
        };
    D3D11_SUBRESOURCE_DATA data{indices.data()};
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateBuffer(&desc, &data, buffer.GetAddressOf()));
}

void IndexBuffer::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}
