#include "Core.hlsli"

Texture2D diffuseTexture : register(t0);
SamplerState samplerLinear : register(s0);

float4 main( VSOut surf ) : SV_Target
{
    float3 dirToLight = normalize(lights[0].position - surf.positionWS);
    float3 normal = normalize(surf.normalWS);

    float intensity = dot(dirToLight, normal);
    
    float4 textureColor = diffuseTexture.Sample(samplerLinear, surf.surfaceData.texCoord) * intensity;

    textureColor.xyz = textureColor;
    
    return textureColor;
}