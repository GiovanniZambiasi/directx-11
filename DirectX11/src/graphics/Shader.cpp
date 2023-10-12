#include "pch.h"
#include "Shader.h"

#include "Drawable.h"
#include "IRenderingContext.h"
#include "Sampler.h"
#include "InputLayout.h"
#include "RenderingResources.h"
#include "cbuffers/TransformationBuffer.h" 

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

void ShaderUtils::BindStandardShaders(IRenderingContext& graphics, Drawable& drawable)
{
    RenderingResources& sharedResources = graphics.GetSharedResources();
    drawable.AddBinding(sharedResources.standardVertexShader);
    drawable.AddBinding(sharedResources.texturedPixelShader);
    drawable.AddBinding(sharedResources.standardInputLayout);
    drawable.AddBinding(sharedResources.standardSampler);
    drawable.AddBinding(sharedResources.transformationBuffer);
}
