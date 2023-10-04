#include "pch.h"
#include "TransformationBuffer.h"

#include "TransformUtils.h"

TransformationBuffer::Data::Data(DirectX::XMMATRIX inWorldTransform)
    : worldTransform(XMMatrixTranspose(inWorldTransform)),
    worldTransformInverse(XMMatrixTranspose(XMMatrixInverse(nullptr, inWorldTransform)))
{ }

 std::shared_ptr<TransformationBuffer> TransformationBuffer::MakeFromTransform(IRenderingContext& graphics, const GioTransform& transform)
{
    Data data{TransformUtils::CalculateFinalMatrix(graphics, transform)};
    return std::make_shared<TransformationBuffer>(graphics, &data,static_cast<UINT>(sizeof(data)));
}

TransformationBuffer::TransformationBuffer(IRenderingContext& graphics, const void* data, UINT dataWidth)
    : VertexConstantBuffer(graphics, data, dataWidth)
{ }

void TransformationBuffer::Update(IRenderingContext& graphics, const GioTransform& transform)
{
    Data data{TransformUtils::CalculateFinalMatrix(graphics, transform)};
    ConstantBuffer::Update(graphics, &data, sizeof(data));
}
