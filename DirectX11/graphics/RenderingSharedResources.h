#pragma once

class InputLayout;
class VertexShader;
class PixelShader;

struct RenderingSharedResources
{
    std::shared_ptr<PixelShader> standardPixelShader{};
    std::shared_ptr<VertexShader> standardVertexShader{};
    std::shared_ptr<InputLayout> standardInputLayout{};
};
