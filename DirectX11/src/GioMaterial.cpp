#include "pch.h"
#include "GioMaterial.h"

#include "IRenderingContext.h"
#include "graphics/InputLayout.h"
#include "graphics/Shader.h"

GioMaterial::GioMaterial(IRenderingContext& graphics, const std::shared_ptr<VertexShader>& inVertexShader,
    const std::shared_ptr<PixelShader>& inPixelShader, const std::shared_ptr<InputLayout>& inInputLayout)
    : vertexShader(inVertexShader), pixelShader(inPixelShader), inputLayout(inInputLayout)
{
}

void GioMaterial::Bind(IRenderingContext& graphics)
{
    assert(pixelShader && vertexShader);
    inputLayout->Bind(graphics);
    vertexShader->Bind(graphics);
    pixelShader->Bind(graphics);
}
