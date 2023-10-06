#include "Core.hlsli"

float4 main( VSOut surf ) : SV_Target
{
    return float4(surf.normalWS, 1.0f);
}