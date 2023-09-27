#pragma once

struct GioVertex
{
    float x{};
    float y{};
    float z{};

    GioVertex() = default;
    
    GioVertex(float v)
        : x(v), y(v), z(v)
    {}

    GioVertex(float inX, float inY, float inZ)
        : x(inX), y(inY), z(inZ)
    {}
};
