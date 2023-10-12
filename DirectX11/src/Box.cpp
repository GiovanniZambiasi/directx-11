#include "pch.h"
#include "Box.h"

#include <iostream>

#include "AssetUtils.h"
#include "GioMesh.h"
#include "graphics/IndexBuffer.h"
#include "RenderingResources.h"
#include "graphics/VertexBuffer.h"
#include "graphics/BindableTexture.h"
#include "graphics/Shader.h"

Box::Box(IGameContext& inGame)
    : Box(inGame,GioTransform{})
{ }

Box::Box(IGameContext& inGame, const GioTransform& spawnTransform)
    : Entity("Box", inGame, spawnTransform)
{
    Drawable& drawable = GetDrawable();
    IRenderingContext& graphics = GetGameContext().GetRenderingContext();

    GioMesh mesh = AssetUtils::ImportMesh(L"res/cube.obj");
    drawable.CreateBinding<VertexBuffer>({graphics, mesh});
    drawable.CreateBinding<IndexBuffer>({graphics, mesh});
    drawable.AddBinding(graphics.GetSharedResources().testTexture);
    ShaderUtils::BindStandardShaders(graphics, drawable);
}

