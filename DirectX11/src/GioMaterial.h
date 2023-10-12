#pragma once
#include "Core.h"
#include "graphics/IBindable.h"

class InputLayout;
class VertexShader;
class PixelShader;

class GioMaterial : public IBindable
{
    std::shared_ptr<VertexShader> vertexShader{};
    
    std::shared_ptr<PixelShader> pixelShader{};
    
    std::shared_ptr<InputLayout> inputLayout{};

public:
    GioMaterial() = default;

    GioMaterial(IRenderingContext& graphics, const std::shared_ptr<VertexShader>& inVertexShader, const std::shared_ptr<PixelShader>& inPixelShader, const std::shared_ptr<InputLayout>& inInputLayout);

    NO_COPY_MOVE(GioMaterial)

    void Bind(IRenderingContext& graphics) override;
};
