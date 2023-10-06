#include "pch.h"
#include "MatrixUtils.h"

#include "GioTransform.h"
#include "IRenderingContext.h"

DirectX::XMMATRIX MatrixUtils::CalculateModelMatrix(const GioTransform& transform)
{
    GioVector rotationRadians = transform.RotationRadians();
    return
        DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z) *
        DirectX::XMMatrixRotationRollPitchYaw(rotationRadians.x, rotationRadians.y, rotationRadians.z) *
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
