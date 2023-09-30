#include "pch.h"
#include "Box.h"

#include <iostream>
#include <vector>

#include "GioColor.h"
#include "GioVector.h"
#include "graphics/IndexBuffer.h"
#include "graphics/RenderingSharedResources.h"
#include "graphics/TransformationBuffer.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Shader.h"

Box::Box(IRenderingContext& graphics, const GioVector& extents)
    : Box(graphics, extents, GioTransform{})
{ }

Box::Box(IRenderingContext& graphics, const GioVector& extents, const GioTransform& spawnTransform)
    : Entity(spawnTransform)
{
    auto& drawable = GetDrawable();
    
    GioVector halved = extents/2.f;
    
    std::vector<GioVector> vertices
    {
            {-halved.x, -halved.y, -halved.z},
            {halved.x, -halved.y, -halved.z},
            {-halved.x, halved.y, -halved.z},
            {halved.x, halved.y, -halved.z},
            {-halved.x, -halved.y, halved.z},
            {halved.x, -halved.y, halved.z},
            {-halved.x, halved.y, halved.z},
            {halved.x, halved.y, halved.z},
        };
    auto vertexBuffer = std::make_shared<VertexBuffer>(graphics, vertices);
    drawable.AddBinding(vertexBuffer);
    
    std::vector<UINT> indices
    {
        0, 2, 1, 2, 3, 1,
        1, 3, 5, 3, 7, 5,
        2, 6, 3, 3, 6, 7,
        4, 5, 7, 4, 7, 6,
        0, 4, 2, 2, 4, 6,
        0, 1, 4, 1, 5, 4
    };
    auto indexBuffer = std::make_shared<IndexBuffer>(graphics, indices);
    drawable.SetIndexBuffer(indexBuffer);
    
    drawable.AddBinding(graphics.GetSharedResources().faceColorBuffer);

    ShaderUtils::BindStandardShaders(graphics, drawable);
}

