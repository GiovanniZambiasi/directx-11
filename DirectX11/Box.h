#pragma once
#include "GioTransform.h"
#include "graphics/Drawable.h"

class IRenderingContext;
struct GioVector;

class Box : public IDrawable
{
    GioTransform transform{};
    
    Drawable drawable{};

public:
    Box(IRenderingContext& graphics, const GioVector& extents);
    
    Box(IRenderingContext& graphics, const GioVector& extents, const GioTransform& spawnTransform);
    
    Drawable& GetDrawable() override { return drawable;}
    
    void Draw(IRenderingContext& graphics) override;

    GioTransform& GetTransform() { return transform; }
};
