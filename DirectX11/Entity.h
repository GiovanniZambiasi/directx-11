#pragma once
#include "Core.h"
#include "GioTransform.h"
#include "graphics/Drawable.h"

class Entity : public IDrawable
{
    GioTransform transform{};

    Drawable drawable{};
    
public:
    Entity() = default;
    
    Entity(const GioTransform& spawnTransform);

    NO_COPY_MOVE(Entity)
    
    Drawable& GetDrawable() final override { return drawable; }

    GioTransform& GetTransform() { return transform; }
    
    void Draw(IRenderingContext& graphics) override;
};
