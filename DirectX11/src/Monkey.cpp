#include "pch.h"
#include "Monkey.h"

#include "AssetUtils.h"
#include "GioMesh.h"
#include "GioMaterial.h"
#include "IRenderingContext.h"
#include "RenderingResources.h"

Monkey::Monkey(IGameContext& inGame, const GioTransform& spawnTransform)
    : Entity("Monkey", inGame, spawnTransform)
{
    RenderingComponent& drawable = GetRenderingComponent();
    IRenderingContext& graphics = inGame.GetRenderingContext();
    
    auto mesh = AssetUtils::Get().FindOrLoadMesh(graphics, L"res/monkey.obj");
    drawable.AddBinding(mesh);
    drawable.AddBinding(graphics.GetSharedResources().standardMaterial);
}
