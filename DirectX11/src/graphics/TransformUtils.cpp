#include "pch.h"
#include "TransformUtils.h"

#include "GioTransform.h"
#include "IRenderingContext.h"

DirectX::XMMATRIX TransformUtils::CalculateModelMatrix(const GioTransform& transform)
{
    GioVector rotationRadians = transform.RotationRadians();
    return
        DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z) *
        DirectX::XMMatrixRotationRollPitchYaw(rotationRadians.x, rotationRadians.y, rotationRadians.z) *
        DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
}

DirectX::XMMATRIX TransformUtils::CalculateMVPMatrix(IRenderingContext& graphics, const GioTransform& transform)
{
    return CalculateMVPMatrix(graphics, CalculateModelMatrix(transform));
}

DirectX::XMMATRIX TransformUtils::CalculateMVPMatrix(IRenderingContext& graphics, const DirectX::XMMATRIX& modelMatrix)
{
    return modelMatrix * graphics.GetCameraMatrix();
}
