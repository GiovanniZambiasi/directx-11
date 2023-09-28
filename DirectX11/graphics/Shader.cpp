#include "pch.h"
#include "Shader.h"

#include "Graphics.h"

VertexShader::VertexShader(Graphics& graphics, const wchar_t* const fileName)
    : Shader(graphics, fileName)
{
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, shaderInstance.GetAddressOf()));
}

void VertexShader::Bind(Graphics& graphics)
{
    graphics.GetDeviceContext()->VSSetShader(shaderInstance.Get(), nullptr, 0);
}

PixelShader::PixelShader(Graphics& graphics, const wchar_t* const fileName)
    : Shader(graphics, fileName)
{
    GIO_THROW_IF_FAILED(graphics.GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, shaderInstance.GetAddressOf()));
}

void PixelShader::Bind(Graphics& graphics)
{
    graphics.GetDeviceContext()->PSSetShader(shaderInstance.Get(), nullptr, 0);
}
