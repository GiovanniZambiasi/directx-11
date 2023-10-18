#pragma once
#include <unordered_map>

#include "GioMesh.h"

class GioTexture;
class GioMaterial;
class RenderingComponent;
class IndexBuffer;
class VertexBuffer;
class BindableTexture;
class Sampler;
class PixelConstantBuffer;
class TransformationBuffer;
class InputLayout;
class VertexShader;
class PixelShader;

class RenderingResources
{
public:
    std::shared_ptr<InputLayout> standardInputLayout{};

    std::shared_ptr<GioMaterial> standardMaterial{};

    std::shared_ptr<Sampler> standardSampler{};
    
    std::shared_ptr<TransformationBuffer> transformationBuffer{};
    
    std::shared_ptr<PixelConstantBuffer> lightBuffer{};

    std::shared_ptr<GioTexture> whiteTexture{};

};
