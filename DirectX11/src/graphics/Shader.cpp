#include "pch.h"
#include "Shader.h"

#include "IRenderingContext.h"
#include "RenderingResources.h"

VertexShader::VertexShader(IRenderingContext& graphics, const wchar_t* const fileName)
    : Shader(graphics, fileName)
{
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, shaderInstance.GetAddressOf()));
}

void VertexShader::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->VSSetShader(shaderInstance.Get(), nullptr, 0);
}

PixelShader::PixelShader(IRenderingContext& graphics, const wchar_t* const fileName)
    : Shader(graphics, fileName)
{
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, shaderInstance.GetAddressOf()));
}

void PixelShader::Bind(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->PSSetShader(shaderInstance.Get(), nullptr, 0);
}

