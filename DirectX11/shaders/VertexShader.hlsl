cbuffer ConstBuffer
{
    matrix transform;
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
    float4 pos : SV_Position;
};


VSOut main(SurfaceData surf)
{
    VSOut output;
    output.surfaceData = surf;
    output.pos = mul(float4(surf.position, 1.0f), transform);
    
    return output;
}