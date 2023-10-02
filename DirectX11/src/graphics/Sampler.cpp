#include "pch.h"
#include "Sampler.h"

#include "ErrorHandling.h"
#include "IRenderingContext.h"

Sampler::Sampler(IRenderingContext& graphics)
{
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateSamplerState(&samplerDesc, &sampler));
}

void Sampler::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->PSSetSamplers(0u, 1u, sampler.GetAddressOf());
}
