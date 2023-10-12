#pragma once
#include "Entity.h"
#include "GioTransform.h"
#include "graphics/Drawable.h"

class IRenderingContext;
struct GioVector;

class Box : public Entity
{
public:
    Box(IGameContext& inGame);
    
    Box(IGameContext& inGame, const GioTransform& spawnTransform);
    
};
