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