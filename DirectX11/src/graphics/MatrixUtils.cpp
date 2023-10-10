#include "pch.h"
#include "MatrixUtils.h"

#include "GioTransform.h"
#include "IRenderingContext.h"

DirectX::XMMATRIX MatrixUtils::CalculateModelMatrix(const GioTransform& transform)
{
    GioRotation rotationRadians = transform.Rotation();
    return
        DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z) *
        DirectX::XMMatrixRotationRollPitchYaw(rotationRadians.pitch, rotationRadians.yaw, rotationRadians.roll) *
        DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
}

DirectX::XMMATRIX MatrixUtils::CalculateMVPMatrix(IRenderingContext& graphics, const GioTransform& transform)
{
    return CalculateMVPMatrix(graphics, CalculateModelMatrix(transform));
}

DirectX::XMMATRIX MatrixUtils::CalculateMVPMatrix(IRenderingContext& graphics, const DirectX::XMMATRIX& modelMatrix)
{
    return modelMatrix * graphics.GetCameraMatrix();
}
