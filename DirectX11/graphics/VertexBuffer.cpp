#include "pch.h"
#include "VertexBuffer.h"

void VertexBuffer::Bind(Graphics& graphics)
{
    constexpr UINT offsets{0};
    graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offsets);
}
