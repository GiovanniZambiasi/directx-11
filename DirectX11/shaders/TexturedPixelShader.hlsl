struct SurfaceData
{
    float3 position : Position;
    float3 normal : Normal;
    float2 texCoord : TexCoord;
    uint faceId : SV_PrimitiveID;
};

Texture2D diffuseTexture : register(t0);
SamplerState samplerLinear : register(s0);

float4 main( SurfaceData surf ) : SV_Target
{
    float4 textureColor = diffuseTexture.Sample(samplerLinear, surf.texCoord);
    return textureColor;
}