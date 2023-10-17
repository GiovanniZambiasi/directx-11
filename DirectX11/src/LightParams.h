#pragma once

#include "GioColor.h"
#include "GioVector.h"

struct LightParams
{
    GioVector position{};
    
    GioColorF color{1.f};

    FLOAT radius{5.f};

    FLOAT attenuation{1.f};
};

struct AmbientLightParams
{
    GioColorF color{1.f};

    FLOAT intensity{.1f};
};
