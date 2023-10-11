/**
 * Input to the pixel shader
 */
struct SurfaceData
{
    float3 position : Position;
    float3 normal : Normal;
    float2 texCoord : TexCoord;
};

/**
 * Output of the vertex shader 
 */
struct VSOut
{
    SurfaceData surfaceData;
    float3 positionWS : PositionWS;
    float3 normalWS : NormalWS;
    float4 pos : SV_Position;
};

struct Light
{
    float3 position : LPosition;
    float3 color : LColor;
    float radius : LRadius;
    float attenuation : LAttenuation;
};

cbuffer LightBuffer : register(b0)
{
    Light lights[3];
}