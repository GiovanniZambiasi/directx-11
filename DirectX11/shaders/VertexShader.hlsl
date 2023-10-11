#include "Core.hlsli"

cbuffer TransformBuffer : register(b0)
{
    matrix model;
    matrix modelInverse;
    matrix mvp;
}

VSOut main(SurfaceData surf)
{
    VSOut output;
    output.surfaceData = surf;
    float4 res = mul(float4(surf.position.xyz, 1), model);
    output.positionWS = res.xyz;
    float3x3 rotationComponent = (float3x3)modelInverse;
    output.normalWS = mul(rotationComponent, surf.normal);
    output.pos = mul(float4(surf.position, 1.0f), mvp);
    
    return output;
}