#pragma once
#include "ConstantBuffer.h"
#include "GioTransform.h"

struct GioTransform;

/**
 * Constant buffer to be used with vertex shaders to apply object transformation
 */
class TransformationBuffer : public VertexConstantBuffer
{
public:
    static std::shared_ptr<TransformationBuffer> MakeFromTransform(IRenderingContext& graphics, const GioTransform& transform);
    
    TransformationBuffer(IRenderingContext& graphics, const void* data, UINT dataWidth);
    
    void Update(IRenderingContext& graphics, const GioTransform& transform);
    
};
