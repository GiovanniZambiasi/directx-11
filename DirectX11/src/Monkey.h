#pragma once
#include "Entity.h"

class Monkey : public Entity
{
public:
    Monkey(IRenderingContext& graphics, const GioTransform& spawnTransform);
    
};
