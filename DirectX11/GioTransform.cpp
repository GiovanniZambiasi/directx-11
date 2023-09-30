#include "pch.h"
#include "GioTransform.h"

GioTransform GioTransform::operator+(const GioTransform& other) const
{
    return GioTransform
    {
        position + other.position,
        rotationEuler + other.rotationEuler,
    };
}

GioVector GioTransform::RotationRadians() const
{
    return GioVector
    {
        DirectX::XMConvertToRadians(rotationEuler.x),
        DirectX::XMConvertToRadians(rotationEuler.y),
        DirectX::XMConvertToRadians(rotationEuler.z),
    };
}

void GioTransform::Translate(const GioVector& factor)
{
    position += factor;
}

void GioTransform::Rotate(const GioVector& factor)
{
    rotationEuler += factor;
}
