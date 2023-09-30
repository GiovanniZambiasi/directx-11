#include "pch.h"
#include "Monkey.h"

#include "AssetUtils.h"
#include "GioMesh.h"
#include "graphics/IndexBuffer.h"
#include "graphics/RenderingSharedResources.h"
#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"
#include "graphics/ConstantBuffer.h"

Monkey::Monkey(IRenderingContext& graphics, const GioTransform& spawnTransform)
    : Entity(spawnTransform)
{
    Drawable& drawable = GetDrawable();
    
    GioMesh mesh = AssetUtils::ImportMesh("res/monkey.obj");
    assert(mesh.IsValid());
    
    auto vertexBuffer = std::make_shared<VertexBuffer>(graphics, mesh);
    drawable.AddBinding(vertexBuffer);

    auto indexBuffer = std::make_shared<IndexBuffer>(graphics, mesh);
    drawable.SetIndexBuffer(indexBuffer);

    drawable.AddBinding(graphics.GetSharedResources().faceColorBuffer);
    
    ShaderUtils::BindStandardShaders(graphics, drawable);
}
