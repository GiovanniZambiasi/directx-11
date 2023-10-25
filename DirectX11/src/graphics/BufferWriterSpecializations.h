#pragma once
#include "BufferWriter.h"
#include "GioColor.h"
#include "GioVector.h"

struct LightBuffer
{
    static constexpr int num_lights = 3;
    
    GioVector viewPosition{};

    AmbientLightParams ambientLight{};

    LightParams lights[num_lights];

    float sanityCheck{1997.f};
        
};

template<>
inline void BufferWriter::WriteObjectInternal<FLOAT>(const FLOAT& data)
{
    WriteBytes(reinterpret_cast<const char*>(&data), sizeof(FLOAT));
}

template<>
inline void BufferWriter::WriteObjectInternal<GioVector>(const GioVector& data)
{
    *this << data.x << data.y << data.z;
}

template<>
inline void BufferWriter::WriteObjectInternal<GioColorF>(const GioColorF& data)
{
    *this << data.r << data.g << data.b << data.a;
}

template<>
inline void BufferWriter::WriteObjectInternal<AmbientLightParams>(const AmbientLightParams& data)
{
    *this << data.color << data.intensity << data.sanityCheck;
}

template<>
inline void BufferWriter::WriteObjectInternal<LightParams>(const LightParams& data)
{
    *this << data.position << data.color << data.radius << data.attenuation << data.sanityCheck;
}

template<>
inline void BufferWriter::WriteObjectInternal<LightBuffer>(const LightBuffer& data)
{
    *this << data.viewPosition << data.ambientLight;
    for (int i = 0; i < LightBuffer::num_lights; ++i)
    {
        const LightParams& light = data.lights[i];
        *this << light;
    }
    *this << data.sanityCheck;
}