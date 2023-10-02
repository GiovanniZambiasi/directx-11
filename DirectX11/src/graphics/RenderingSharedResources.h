#pragma once

class PixelConstantBuffer;
class TransformationBuffer;
class InputLayout;
class VertexShader;
class PixelShader;

struct RenderingSharedResources
{
    std::shared_ptr<PixelShader> standardPixelShader{};
    std::shared_ptr<VertexShader> standardVertexShader{};
    std::shared_ptr<InputLayout> standardInputLayout{};
    std::shared_ptr<PixelShader> texturedPixelShader{};
    std::shared_ptr<VertexShader> texturedVertexShader{};
    std::shared_ptr<TransformationBuffer> transformationBuffer{};
    std::shared_ptr<PixelConstantBuffer> faceColorBuffer{};
};
