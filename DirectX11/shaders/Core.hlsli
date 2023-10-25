/**
 * Input to the vertex shader
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
    float4 color : LColor;
    float radius : LRadius;
    float attenuation : LAttenuation;
    float sanity;
};

struct AmbientLight
{
    float4 color : ALColor;
    float intensity : ALIntensity;
    float sanity;
};
