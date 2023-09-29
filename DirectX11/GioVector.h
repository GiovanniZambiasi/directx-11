#pragma once

struct GioVector
{
    float x{};
    float y{};
    float z{};

    GioVector() = default;
    
    GioVector(float v)
        : x(v), y(v), z(v)
    {}

    GioVector(float inX, float inY, float inZ)
        : x(inX), y(inY), z(inZ)
    {}

    GioVector operator/(float factor) const; 
};
