#include "pch.h"
#include "Light.h"

#include "AssetUtils.h"
#include "GioMesh.h"
#include "GioMaterial.h"
#include "IRenderingContext.h"
#include "Logger.h"
#include "RenderingResources.h"

Light::Light(IGameContext& inGame, const GioTransform& inTransform, const LightParams& inParams)
    : Entity("Light", inGame, inTransform), params(inParams)
{
    RenderingComponent& drawable = GetRenderingComponent();
    IRenderingContext& graphics = inGame.GetRenderingContext();

    auto mesh = AssetUtils::Get().FindOrLoadMesh(graphics, L"res/cube.obj");
    drawable.AddBinding(mesh);
    drawable.AddBinding(graphics.GetSharedResources().standardMaterial);
}

void Light::Update(float deltaTime)
{
    static bool flip = false;
    
    timeSinceStart += deltaTime;

    auto sin = std::sin(timeSinceStart);
    auto cos = std::cos(timeSinceStart);

    GioTransform& transform = GetTransform();
    GioVector pos{sin, 0.f, cos};
    pos *= 5.f;
    transform.position = flip ? -pos : pos;

    flip = !flip;

    params.position = transform.position;

    GetGameContext().GetRenderingContext().AddLight(params);
}