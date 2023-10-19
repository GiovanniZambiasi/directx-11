#include "pch.h"
#include "LightParams.h"

LightParams::LightParams(const GioVector& inPosition, GioColorF inColor, FLOAT inRadius, FLOAT inAttenuation)
    : position(inPosition), color(inColor), radius(inRadius), attenuation(inAttenuation)
{
}
