cbuffer TransformBuffer
{
    matrix transform;
    matrix inverseTransform;
}

struct SurfaceData
{
    float3 position : Position;
    float3 normal : Normal;
    float2 texCoord : TexCoord;
};

struct VSOut
{
    SurfaceData surfaceData;
    float3 normalWS : NormalWS;
    float4 pos : SV_Position;
};

Texture2D diffuseTexture : register(t0);
SamplerState samplerLinear : register(s0);

float4 main( VSOut surf ) : SV_Target
{
    float4 textureColor = diffuseTexture.Sample(samplerLinear, surf.surfaceData.texCoord);
    return textureColor;
}