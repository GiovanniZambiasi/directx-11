﻿#include "pch.h"
#include "Box.h"

#include <iostream>

#include "AssetUtils.h"
#include "GioMesh.h"
#include "GioTexture.h"
#include "GioMaterial.h"
#include "IRenderingContext.h"
#include "RenderingResources.h"

Box::Box(IGameContext& inGame)
    : Box(inGame,GioTransform{})
{ }

Box::Box(IGameContext& inGame, const GioTransform& spawnTransform)
    : Entity("Box", inGame, spawnTransform)
{
    RenderingComponent& drawable = GetRenderingComponent();
    IRenderingContext& graphics = GetGameContext().GetRenderingContext();

    std::shared_ptr<GioMesh> mesh = AssetUtils::Get().FindOrLoadMesh(graphics, L"res/cube.obj");
    drawable.AddBinding(mesh);
    std::shared_ptr<GioTexture> texture = AssetUtils::Get().FindOrLoadTexture(graphics, L"res/texture.jpg");
    assert(graphics.GetSharedResources().standardMaterial);
    GioMaterial& standardMaterial = *graphics.GetSharedResources().standardMaterial.get();
    std::shared_ptr<GioMaterial> material = std::make_shared<GioMaterial>(standardMaterial);
    material->SetTexture(texture, 0);
    drawable.AddBinding(material);
}

