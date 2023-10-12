#pragma once

#include "GioColor.h"
#include "GioVector.h"

struct LightParams
{
    GioVector position{};
    
    GioColorF color{1.f};

    float radius{5.f};

    float attenuation{1.f};
};
