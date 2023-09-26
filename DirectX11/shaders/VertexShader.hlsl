struct VSOut
{
    float3 color : Color;
    float4 pos : SV_Position;
};

cbuffer ConstBuffer
{
    row_major matrix transform;
}

VSOut main(float2 pos : Position, float3 color : Color)
{
    VSOut output;
    output.pos = mul(float4(pos.x, pos.y, .0f, 1.f), transform);
    output.color = color;
    return output;
}