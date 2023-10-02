#include "pch.h"
#include "TransformationBuffer.h"

#include "TransformUtils.h"

 std::shared_ptr<TransformationBuffer> TransformationBuffer::MakeFromTransform(IRenderingContext& graphics, const GioTransform& transform)
{
    DirectX::XMMATRIX matrix = TransformUtils::CalculateFinalMatrix(graphics, transform);
    return std::make_shared<TransformationBuffer>(graphics, &matrix,static_cast<UINT>(sizeof(matrix)));
}

TransformationBuffer::TransformationBuffer(IRenderingContext& graphics, const void* data, UINT dataWidth)
    : VertexConstantBuffer(graphics, data, dataWidth)
{ }

void TransformationBuffer::Update(IRenderingContext& graphics, const GioTransform& transform)
{
    DirectX::XMMATRIX matrix = TransformUtils::CalculateFinalMatrix(graphics, transform);
    ConstantBuffer::Update(graphics, &matrix, sizeof(matrix));
}
