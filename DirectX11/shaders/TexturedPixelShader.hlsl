#include "Core.hlsli"

cbuffer LightBuffer : register(b0)
{
    float3 viewPos;
    AmbientLight ambient;
    Light lights[3];
    float sanity;
}

Texture2D albedoTexture : register(t0);
SamplerState samplerLinear : register(s0);

struct LightOutput
{
    float4 diffuse;
    float4 specular;
};

LightOutput CalculateLight(Light light, float3 surfacePos, float3 surfaceNormal)
{
    LightOutput output;
    
    float3 dirToLight = normalize(light.position - surfacePos);
    float3 normal = normalize(surfaceNormal);    
    float intensity = max(dot(dirToLight, normal), 0.0f);
    output.diffuse = light.color * intensity;

    float3 viewDirection = normalize(viewPos - surfacePos);
    float3 reflection = reflect(-dirToLight, surfaceNormal);
    int specularExponent = 32;
    float specularStrength = 0.5;
    float specular = pow(max(dot(viewDirection,reflection),0.0), specularExponent);
    output.specular = specular * specularStrength * light.color;
    
    return output;
}

float4 main( VSOut surf ) : SV_Target
{
    float4 pointLight = float4(0.0f, 0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 3; ++i)
    {
        LightOutput output = CalculateLight(lights[i], surf.positionWS, surf.normalWS); 
        pointLight += output.diffuse;
        pointLight += output.specular;
    }
 
    float4 ambientLight = ambient.color * ambient.intensity;
    float4 light = pointLight + ambientLight;

    float4 outputColor = albedoTexture.Sample(samplerLinear, surf.surfaceData.texCoord);
    outputColor *= light;
    
    return outputColor;
}