#include "pch.h"
#include "Monkey.h"

#include "AssetUtils.h"
#include "GioMesh.h"
#include "graphics/IndexBuffer.h"
#include "RenderingResources.h"
#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"
#include "graphics/ConstantBuffer.h"

Monkey::Monkey(IGameContext& inGame, const GioTransform& spawnTransform)
    : Entity("Monkey", inGame, spawnTransform)
{
    Drawable& drawable = GetDrawable();
    IRenderingContext& graphics = inGame.GetRenderingContext();
    
    GioMesh mesh = AssetUtils::ImportMesh(L"res/monkey.obj");
    assert(mesh.IsValid());
    drawable.CreateBinding<VertexBuffer>({graphics, mesh});
    drawable.CreateBinding<IndexBuffer>({graphics, mesh});
    ShaderUtils::BindStandardShaders(graphics, drawable);
}
