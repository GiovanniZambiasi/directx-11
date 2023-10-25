#pragma once

#include "GioColor.h"
#include "GioVector.h"

struct LightParams
{
    GioVector position{};

    GioColorF color{1.f};

    FLOAT radius{5.f};

    FLOAT attenuation{1.f};

    FLOAT sanityCheck{24.f};
    
    LightParams() = default;
};

struct AmbientLightParams
{
    GioColorF color{1.f};

    FLOAT intensity{.12f};

    FLOAT sanityCheck{10.f};
};
