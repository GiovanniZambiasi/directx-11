#include "pch.h"
#include "Box.h"

#include <vector>

#include "GioColor.h"
#include "GioVector.h"
#include "graphics/IndexBuffer.h"
#include "graphics/RenderingSharedResources.h"
#include "graphics/TransformationBuffer.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Shader.h"
#include "graphics/InputLayout.h"

Box::Box(IRenderingContext& graphics, const GioVector& extents)
    :Box(graphics, extents, GioTransform{})
{ }

Box::Box(IRenderingContext& graphics, const GioVector& extents, const GioTransform& spawnTransform)
    : transform(spawnTransform)
{
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
    
    std::vector<USHORT> indices
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

    std::vector<GioColor> faceColors
    {
            {
                {1.f, 0.f, 1.f},
                {1.f, 0.f, 0.f},
                {0.f, 1.f, 0.f},
                {0.f, 0.f, 1.f},
                {1.f, 1.f, 0.f},
                {0.f, 1.f, 1.f},
            }
    };
    auto faceColorsBuffer = std::make_shared<PixelConstantBuffer>(graphics, faceColors.data(), static_cast<UINT>(faceColors.size() * sizeof(GioColor)));
    drawable.AddBinding(faceColorsBuffer);

    RenderingSharedResources& sharedResources = graphics.GetSharedResources();
    drawable.AddBinding(sharedResources.standardVertexShader);
    drawable.AddBinding(sharedResources.standardPixelShader);
    drawable.AddBinding(sharedResources.standardInputLayout);
    drawable.SetTransformationBuffer(sharedResources.transformationBuffer);
}

void Box::Draw(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    drawable.Draw(graphics, transform);
}
