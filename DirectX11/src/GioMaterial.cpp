#include "pch.h"
#include "GioMaterial.h"

#include "GioTexture.h"
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
    
    for (auto& texture : textures)
    {
        texture->Bind(graphics);
    }

    if(textures.size() == 0)
    {
        ID3D11ShaderResourceView* views[1] = { nullptr};
        graphics.GetDeviceContext()->PSSetShaderResources(0, 1, views);
    }
    
    inputLayout->Bind(graphics);
    vertexShader->Bind(graphics);
    pixelShader->Bind(graphics);
}

void GioMaterial::AddTexture(const std::shared_ptr<GioTexture>& texture)
{
    textures.push_back(texture);
}
