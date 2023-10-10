#include "pch.h"
#include "GioTransform.h"

#include <iostream>
#include <sstream>

#include "Logger.h"

GioTransform GioTransform::operator+(const GioTransform& other) const
{
    return GioTransform
    {
        position + other.position,
        rotation + other.rotation,
    };
}

GioRotation GioTransform::Rotation() const
{
    return rotation;
}

GioVector GioTransform::GetForward() const
{
    return rotation.ToDirection();
}

GioVector GioTransform::GetUp() const
{
    return TransformDirection(GioVector{0.f, 1.f, 0.f});
}

GioVector GioTransform::TransformDirection(const GioVector& inDirection) const
{
    DirectX::XMMATRIX matrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.pitch, rotation.yaw, rotation.roll);
    return XMVector3Transform(inDirection, matrix);
}

void GioTransform::Translate(const GioVector& factor)
{
    position += factor;
}

void GioTransform::Rotate(const GioRotation& factor)
{
    rotation += factor;
}

void GioTransform::LookAt(const GioVector& target)
{
    GioVector direction = (target - position).Normalized();
    rotation = GioRotation::FromDirection(direction);
}

std::string GioTransform::ToString() const
{
    std::stringstream stream{};
    stream << "{ P: " << position.ToString() << " | R: " << rotation.ToString(false) << " | S: " << scale.ToString() << "}";
    return stream.str();
}

