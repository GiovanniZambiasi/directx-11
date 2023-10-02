struct SurfaceData
{
    float3 position : Position;
    float3 normal : Normal;
    float2 texCoord : TexCoord;
    uint faceId : SV_PrimitiveID;
};

float4 main( SurfaceData surf ) : SV_Target
{
    return float4(surf.normal, 1.0f);
}