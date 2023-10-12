#pragma once

#include "Entity.h"
#include "LightParams.h"

class Light : public Entity
{
    LightParams params{};

    float timeSinceStart{0.f};
    
public:
    Light(IGameContext& inGame, const GioTransform& inTransform, const LightParams& inParams);

    LightParams& GetParams() { return params; } 
    
    void Update(float deltaTime) override;

};
