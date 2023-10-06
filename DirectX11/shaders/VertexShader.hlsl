#include "Core.hlsli"

VSOut main(SurfaceData surf)
{
    VSOut output;
    output.surfaceData = surf;
    output.positionWS = mul(float4(surf.position, 1.0f), model);
    float3x3 rotationComponent = (float3x3)modelInverse;
    output.normalWS = mul(rotationComponent, surf.normal);
    output.pos = mul(float4(surf.position, 1.0f), mvp);
    
    return output;
}