#include "pch.h"
#include "TransformUtils.h"

#include "GioTransform.h"
#include "IRenderingContext.h"

DirectX::XMMATRIX TransformUtils::TransformToMatrix(const GioTransform& transform)
{
    return
        DirectX::XMMatrixRotationX(transform.rotation.x) *
        DirectX::XMMatrixRotationY(transform.rotation.y) *
        DirectX::XMMatrixRotationZ(transform.rotation.z) *
        DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
}

DirectX::XMMATRIX TransformUtils::CalculateFinalMatrix(IRenderingContext& graphics, const GioTransform& transform)
{
    return XMMatrixTranspose(
        TransformToMatrix(transform) *
            graphics.GetProjectionMatrix()
        );
}
