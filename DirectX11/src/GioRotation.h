#pragma once
#include "GioVector.h"

struct GioVector;

struct GioRotation
{
    float pitch{};
    float yaw{};
    float roll{};

    GioRotation() = default;
    
    GioRotation(float inV);

    static GioRotation FromDirection(GioVector inDirection);
    
    static GioRotation FromRadians(float inPitch, float inYaw, float inRoll);
    
    static GioRotation FromDegrees(float inPitch, float inYaw, float inRoll);

    GioRotation operator+(const GioRotation& other) const;

    GioRotation& operator+=(const GioRotation& factor);
    
    GioRotation ToEuler() const;

    GioVector ToDirection() const;

    std::string ToString(bool inRadians = true) const;

private:
    GioRotation(float inPitch, float inYaw, float inRoll);
    
};
