#pragma once

#include "GioColor.h"
#include "GioVector.h"
#include "graphics/CoreGraphics.h"

struct LightParams
{
    GioVector position{};

    PADDING(4, po);
    
    GioColorF color{1.f};

    FLOAT radius{5.f};

    FLOAT attenuation{1.f};

    LightParams() = default;

    LightParams(const GioVector& inPosition, GioColorF inColor, FLOAT inRadius, FLOAT inAttenuation);
};

struct AmbientLightParams
{
    GioColorF color{1.f};

    FLOAT intensity{.12f};
};
