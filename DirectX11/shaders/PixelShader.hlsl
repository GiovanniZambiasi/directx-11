cbuffer CBuf
{
    float4 face_colors[6];
}

float4 main( uint tId : SV_PrimitiveID ) : SV_Target
{
    return face_colors[tId%6];
}