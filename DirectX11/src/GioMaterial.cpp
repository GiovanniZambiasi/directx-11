#include <pch.h>
#include "GioMaterial.h"

#include "GioTexture.h"
#include "IRenderingContext.h"
#include "RenderingResources.h"
#include "graphics/InputLayout.h"
#include "graphics/Shader.h"

GioMaterial::GioMaterial(IRenderingContext& graphics, const std::shared_ptr<VertexShader>& inVertexShader,
                         const std::shared_ptr<PixelShader>& inPixelShader,
                         const std::shared_ptr<InputLayout>& inInputLayout,
                         std::vector<MaterialParameter>&& inParameters)
    : vertexShader(inVertexShader),
      pixelShader(inPixelShader),
      inputLayout(inInputLayout),
      parameters(std::move(inParameters))
{
}

void GioMaterial::Bind(IRenderingContext& graphics)
{
    assert(pixelShader && vertexShader);

    for (const auto& parameter : parameters)
    {
        if(parameter.texture && parameter.texture->IsValid())
        {
            parameter.texture->Bind(graphics);
        }
        else
        {
            graphics.GetSharedResources().whiteTexture->Bind(graphics);
        }
    }
    
    inputLayout->Bind(graphics);
    vertexShader->Bind(graphics);
    pixelShader->Bind(graphics);
}

void GioMaterial::SetTexture(const std::shared_ptr<GioTexture>& texture, int index)
{
    assert(texture->IsValid());
    assert(index >= 0 && index < parameters.size());
    parameters[index].texture = texture;
}
