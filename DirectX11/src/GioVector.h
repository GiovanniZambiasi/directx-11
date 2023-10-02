﻿#pragma once

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

    GioVector operator+(const GioVector& other) const;

    GioVector& operator+=(const GioVector& other);

    operator DirectX::XMVECTOR() const;

    std::string ToString() const;
};

struct GioUV
{
    float u{};
    float v{};

    GioUV() = default;
    
    GioUV(float x)
        : u(x), v(x)
    {}

    GioUV(float inU, float inV)
        : u(inU), v(inV)
    {}

    std::string ToString() const;
};
