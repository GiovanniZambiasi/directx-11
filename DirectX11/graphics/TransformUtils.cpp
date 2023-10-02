#include "pch.h"
#include "TransformUtils.h"

#include "GioTransform.h"
#include "IRenderingContext.h"

DirectX::XMMATRIX TransformUtils::TransformToMatrix(const GioTransform& transform)
{
    GioVector rotationRadians = transform.RotationRadians();
    return
        DirectX::XMMatrixRotationX(rotationRadians.x) *
        DirectX::XMMatrixRotationY(rotationRadians.y) *
        DirectX::XMMatrixRotationZ(rotationRadians.z) *
        DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
}

DirectX::XMMATRIX TransformUtils::CalculateFinalMatrix(IRenderingContext& graphics, const GioTransform& transform)
{
    return XMMatrixTranspose(
        TransformToMatrix(transform) *
            graphics.GetCameraMatrix()
        );
}
