#pragma once
#include "Core.h"
#include "graphics/IBindable.h"

class GioTexture;
class InputLayout;
class VertexShader;
class PixelShader;

class GioMaterial : public IBindable
{
    std::shared_ptr<VertexShader> vertexShader{};
    
    std::shared_ptr<PixelShader> pixelShader{};
    
    std::shared_ptr<InputLayout> inputLayout{};

    std::vector<std::shared_ptr<GioTexture>> textures{};

public:
    GioMaterial() = default;

    GioMaterial(IRenderingContext& graphics, const std::shared_ptr<VertexShader>& inVertexShader, const std::shared_ptr<PixelShader>& inPixelShader, const std::shared_ptr<InputLayout>& inInputLayout);

    void Bind(IRenderingContext& graphics) override;

    void AddTexture(const std::shared_ptr<GioTexture>& texture);
};
