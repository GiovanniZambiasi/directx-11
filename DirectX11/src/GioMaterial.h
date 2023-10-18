#pragma once
#include "Core.h"
#include "graphics/IBindable.h"

class GioTexture;
class InputLayout;
class VertexShader;
class PixelShader;

struct MaterialParameter
{
    std::string name{};

    std::shared_ptr<GioTexture> texture{};
};

class GioMaterial : public IBindable
{
    std::shared_ptr<VertexShader> vertexShader{};
    
    std::shared_ptr<PixelShader> pixelShader{};
    
    std::shared_ptr<InputLayout> inputLayout{};

    std::vector<MaterialParameter> parameters{};

public:
    GioMaterial() = default;

    GioMaterial(IRenderingContext& graphics, const std::shared_ptr<VertexShader>& inVertexShader,
                const std::shared_ptr<PixelShader>& inPixelShader, const std::shared_ptr<InputLayout>& inInputLayout,
                std::vector<MaterialParameter>&& inParameters);

    void Bind(IRenderingContext& graphics) override;

    void SetTexture(const std::shared_ptr<GioTexture>& texture, int index);
    
};
