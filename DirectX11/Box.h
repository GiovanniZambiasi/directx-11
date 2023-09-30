﻿#pragma once
#include "Entity.h"
#include "GioTransform.h"
#include "graphics/Drawable.h"

class IRenderingContext;
struct GioVector;

class Box : public Entity
{
public:
    Box(IRenderingContext& graphics, const GioVector& extents);
    
    Box(IRenderingContext& graphics, const GioVector& extents, const GioTransform& spawnTransform);
    
};
