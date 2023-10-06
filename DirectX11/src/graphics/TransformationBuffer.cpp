#include "pch.h"
#include "TransformationBuffer.h"

#include "MatrixUtils.h"

TransformationBuffer::Data::Data(IRenderingContext& graphics, const GioTransform& inTransform)
{
    DirectX::XMMATRIX model = MatrixUtils::CalculateModelMatrix(inTransform);
    modelMatrix = XMMatrixTranspose(model);
    modelMatrixInverse = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, model));
    DirectX::XMMATRIX mvp = MatrixUtils::CalculateMVPMatrix(graphics, model);
    MVPMatrix = XMMatrixTranspose(mvp);
}

 std::shared_ptr<TransformationBuffer> TransformationBuffer::MakeFromTransform(IRenderingContext& graphics, const GioTransform& transform)
{
    Data data{graphics, transform};
    return std::make_shared<TransformationBuffer>(graphics, &data,static_cast<UINT>(sizeof(data)));
}

TransformationBuffer::TransformationBuffer(IRenderingContext& graphics, const void* data, UINT dataWidth)
    : VertexConstantBuffer(graphics, data, dataWidth)
{ }

void TransformationBuffer::Update(IRenderingContext& graphics, const GioTransform& transform)
{
    Data data{graphics, transform};
    ConstantBuffer::Update(graphics, &data, sizeof(data));
}
