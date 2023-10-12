#pragma once

class BindableTexture;
class Sampler;
class PixelConstantBuffer;
class TransformationBuffer;
class InputLayout;
class VertexShader;
class PixelShader;

struct RenderingResources
{
    std::shared_ptr<InputLayout> standardInputLayout{};
    
    std::shared_ptr<VertexShader> standardVertexShader{};
    
    std::shared_ptr<PixelShader> texturedPixelShader{};

    std::shared_ptr<Sampler> standardSampler{};
    std::shared_ptr<BindableTexture> testTexture{};
    std::shared_ptr<BindableTexture> checkeredTexture{};
    
    std::shared_ptr<TransformationBuffer> transformationBuffer{};
    std::shared_ptr<PixelConstantBuffer> lightBuffer{};
};
