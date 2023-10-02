#include "pch.h"
#include "VertexBuffer.h"

#include "GioMesh.h"

VertexBuffer::VertexBuffer(IRenderingContext& graphics, const GioMesh& mesh)
    : VertexBuffer(graphics, mesh.vertices)
{
}

void VertexBuffer::Bind(IRenderingContext& graphics)
{
    constexpr UINT offsets{0};
    graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offsets);
}
