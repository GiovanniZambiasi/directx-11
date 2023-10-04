#pragma once

struct GioVector;

template<typename TNumericType, typename = std::enable_if_t<std::is_arithmetic_v<TNumericType>>>
struct GioColor
{
    TNumericType r{};
    
    TNumericType g{};
    
    TNumericType b{};
    
    TNumericType a{};

    GioColor() = default;

    GioColor(TNumericType v)
        : r{v}, g{v}, b{v}, a{v}
    {  }

    GioColor(TNumericType inR, TNumericType inG, TNumericType inB, TNumericType inA)
        : r{inR}, g{inG}, b{inB}, a{inA}
    {  }

    GioColor(TNumericType inR, TNumericType inG, TNumericType inB)
        : GioColor(inR, inG, inB, 1.f)
    {  }
};

using GioColorF = GioColor<float>;

using GioColor32 = GioColor<uint8_t>;

