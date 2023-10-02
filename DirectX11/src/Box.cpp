#include "pch.h"
#include "Box.h"

#include <iostream>
#include <vector>

#include "AssetUtils.h"
#include "GioColor.h"
#include "GioMesh.h"
#include "GioVector.h"
#include "graphics/IndexBuffer.h"
#include "graphics/RenderingSharedResources.h"
#include "graphics/TransformationBuffer.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Shader.h"
#include "graphics/BindableTexture.h"

Box::Box(IRenderingContext& graphics)
    : Box(graphics,GioTransform{})
{ }

Box::Box(IRenderingContext& graphics, const GioTransform& spawnTransform)
    : Entity("Box", spawnTransform)
{
    auto& drawable = GetDrawable();

    GioMesh mesh = AssetUtils::ImportMesh(L"res/cube.obj");
    
    auto vertexBuffer = std::make_shared<VertexBuffer>(graphics, mesh);
    drawable.AddBinding(vertexBuffer);
    
    auto indexBuffer = std::make_shared<IndexBuffer>(graphics, mesh);
    drawable.SetIndexBuffer(indexBuffer);

    drawable.AddBinding(graphics.GetSharedResources().chandelleTexture);
    
    ShaderUtils::BindTexturedShaders(graphics, drawable);
}

