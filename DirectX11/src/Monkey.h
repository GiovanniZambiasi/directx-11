#pragma once
#include "Entity.h"

class Monkey : public Entity
{
public:
    Monkey(IGameContext& inGame, const GioTransform& spawnTransform);
    
};
