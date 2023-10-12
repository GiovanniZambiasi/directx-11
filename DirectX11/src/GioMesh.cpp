#include "pch.h"
#include "GioMesh.h"

#include "graphics/IndexBuffer.h"
#include "graphics/VertexBuffer.h"

GioMesh::GioMesh(IRenderingContext& graphics, std::vector<GioVertex>&& inVertices, std::vector<UINT>&& inIndices)
    : vertices(std::move(inVertices)), indices(std::move(inIndices))
{
    if(IsValid())
    {
        indexBuffer = std::make_shared<IndexBuffer>(graphics, indices);
        vertexBuffer = std::make_shared<VertexBuffer>(graphics, vertices);
    }
}

bool GioMesh::IsValid() const
{
    return vertices.size() > 0 && indices.size() > 0;
}

void GioMesh::Bind(IRenderingContext& graphics)
{
    indexBuffer->Bind(graphics);
    vertexBuffer->Bind(graphics);
}

void GioMesh::Draw(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->DrawIndexed(indexBuffer->GetIndexCount(), 0u, 0u);
}
