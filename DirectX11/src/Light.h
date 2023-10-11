#pragma once
#include "Entity.h"
#include "GioColor.h"

struct LightParams
{
    GioVector position{};
    
    GioColorF color{1.f};

    float radius{5.f};

    float attenuation{1.f};
};

class Light : public Entity
{
    LightParams params{};

    float timeSinceStart{0.f};
    
public:
    Light(IRenderingContext& graphics, const GioTransform& inTransform, const LightParams& inParams);

    LightParams& GetParams() { return params; } 
    
    void Update(float deltaTime) override;

};
