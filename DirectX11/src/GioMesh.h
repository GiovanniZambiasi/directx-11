#pragma once
#include <vector>

#include "Core.h"
#include "GioVertex.h"
#include "graphics/IBindable.h"
#include "graphics/IDrawable.h"

class InputLayout;
class IRenderingContext;
class IndexBuffer;
class VertexBuffer;

class GioMesh : public IDrawable
{
    std::vector<GioVertex> vertices{};

    std::vector<UINT> indices{};
    
    std::shared_ptr<IndexBuffer> indexBuffer{};
    
    std::shared_ptr<VertexBuffer> vertexBuffer{};

public:
    GioMesh() = default;

    GioMesh(IRenderingContext& graphics, std::vector<GioVertex>&& inVertices, std::vector<UINT>&& inIndices);

    NO_COPY_MOVE(GioMesh)
    
    bool IsValid() const;
    
    void Bind(IRenderingContext& graphics) override;

    void Draw(IRenderingContext& graphics) override;
};
