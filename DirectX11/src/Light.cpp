#include "pch.h"
#include "Light.h"

#include "AssetUtils.h"
#include "GioMesh.h"
#include "graphics/RenderingSharedResources.h"
#include "graphics/IndexBuffer.h"
#include "graphics/BindableTexture.h"
#include "graphics/Shader.h"
#include "graphics/VertexBuffer.h"

Light::Light(IRenderingContext& graphics, const GioTransform& inTransform, const LightParams& inParams)
    : Entity("Light", inTransform), params(inParams)
{
    auto& drawable = GetDrawable();

    GioMesh mesh = AssetUtils::ImportMesh(L"res/cube.obj");
    drawable.CreateBinding<VertexBuffer>({graphics, mesh});
    drawable.CreateBinding<IndexBuffer>({graphics, mesh});
    ShaderUtils::BindStandardShaders(graphics, drawable);
    
    params.position = GetTransform().position;
}

void Light::Update(float deltaTime)
{
    timeSinceStart += deltaTime;

    auto sin = std::sin(timeSinceStart);
    auto cos = std::cos(timeSinceStart);

    GioVector pos{sin, 0.f, cos};
    pos *= 5.f;
    GetTransform().position = pos;
    params.position = pos;
}
