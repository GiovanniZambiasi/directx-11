#include "Core.hlsli"

Texture2D diffuseTexture : register(t0);
SamplerState samplerLinear : register(s0);

float4 main( VSOut surf ) : SV_Target
{
    float4 textureColor = diffuseTexture.Sample(samplerLinear, surf.surfaceData.texCoord);
    return textureColor;
}