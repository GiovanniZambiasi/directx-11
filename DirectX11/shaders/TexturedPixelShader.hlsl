#include "Core.hlsli"

cbuffer LightBuffer : register(b0)
{
    AmbientLight ambient;
    //Light lights[3];
    Light light;
}

Texture2D diffuseTexture : register(t0);
SamplerState samplerLinear : register(s0);

float4 CalculateLight(Light light, float3 surfacePos, float3 surfaceNormal)
{
    float3 dirToLight = normalize(light.position - surfacePos);
    float3 normal = normalize(surfaceNormal);    
    float intensity = max(dot(dirToLight, normal), 0.0f);
    return light.color * intensity;
}

float4 main( VSOut surf ) : SV_Target
{
    float4 pointLight = CalculateLight(light, surf.positionWS, surf.normalWS);
    float4 ambientLight = saturate(ambient.color * ambient.intensity);

    float4 light = pointLight + ambientLight;

    float4 outputColor = diffuseTexture.Sample(samplerLinear, surf.surfaceData.texCoord);
    outputColor *= light;
    
    return saturate(outputColor);
}