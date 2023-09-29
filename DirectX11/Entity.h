#pragma once
#include "GioTransform.h"
#include "graphics/Drawable.h"

class Entity : public IDrawable
{
    GioTransform transform{};

    Drawable drawable{};
    
public:
    Drawable& GetDrawable() override { return drawable; }

    GioTransform& GetTransform() { return transform; }
    
    void Draw(IRenderingContext& graphics) override;
};
