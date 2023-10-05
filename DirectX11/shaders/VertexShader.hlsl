cbuffer TransformBuffer
{
    matrix model;
    matrix modelInverse;
    matrix mvp;
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
    float3 positionWS : PositionWS;
    float3 normalWS : NormalWS;
    float4 pos : SV_Position;
};

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