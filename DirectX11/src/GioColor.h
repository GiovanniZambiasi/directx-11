#pragma once

struct GioColor
{
    float r{};
    
    float g{};
    
    float b{};
    
    float a{};

    GioColor() = default;

    GioColor(float v)
        : r{v}, g{v}, b{v}, a{v}
    {  }

    GioColor(float inR, float inG, float inB, float inA)
        : r{inR}, g{inG}, b{inB}, a{inA}
    {  }

    GioColor(float inR, float inG, float inB)
        : GioColor(inR, inG, inB, 1.f)
    {  }

    static const GioColor White;
    static const GioColor Clear;
    static const GioColor Black;
    static const GioColor Red;
    static const GioColor Green;
    static const GioColor Blue;
};
