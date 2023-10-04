#include "pch.h"
#include "TransformUtils.h"

#include "GioTransform.h"
#include "IRenderingContext.h"

DirectX::XMMATRIX TransformUtils::TransformToMatrix(const GioTransform& transform)
{
    GioVector rotationRadians = transform.RotationRadians();
    return
        DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z) *
        DirectX::XMMatrixRotationRollPitchYaw(rotationRadians.x, rotationRadians.y, rotationRadians.z) *
        DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
}

DirectX::XMMATRIX TransformUtils::CalculateFinalMatrix(IRenderingContext& graphics, const GioTransform& transform)
{
    return TransformToMatrix(transform) *
        graphics.GetCameraMatrix();
}
