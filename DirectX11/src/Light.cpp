#include "pch.h"
#include "Light.h"

#include "AssetUtils.h"
#include "GioMesh.h"
#include "RenderingResources.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"

Light::Light(IGameContext& inGame, const GioTransform& inTransform, const LightParams& inParams)
    : Entity("Light", inGame, inTransform), params(inParams)
{
    Drawable& drawable = GetDrawable();
    IRenderingContext& graphics = inGame.GetRenderingContext();

    GioMesh mesh = AssetUtils::ImportMesh(L"res/cube.obj");
    drawable.CreateBinding<VertexBuffer>({graphics, mesh});
    drawable.CreateBinding<IndexBuffer>({graphics, mesh});
    ShaderUtils::BindStandardShaders(graphics, drawable);
}

void Light::Update(float deltaTime)
{
    timeSinceStart += deltaTime;

    auto sin = std::sin(timeSinceStart);
    auto cos = std::cos(timeSinceStart);

    GioTransform& transform = GetTransform();
    GioVector pos{sin, 0.f, cos};
    pos *= 5.f;
    transform.position = pos;

    params.position = transform.position;

    GetGameContext().GetRenderingContext().AddLight(params);
}