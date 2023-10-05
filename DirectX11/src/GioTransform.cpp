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
        rotationEuler + other.rotationEuler,
    };
}

GioVector GioTransform::RotationRadians() const
{
    return rotationEuler.EulerToRadians();
}

GioVector GioTransform::GetForward() const
{
    return
    {
        std::cos(rotationEuler.y) * std::cos(rotationEuler.x),
        std::sin(rotationEuler.y) * std::cos(rotationEuler.x),
        sin(rotationEuler.x)
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

void GioTransform::LookAt(const GioVector& target)
{
    GioVector direction = (target - position).Normalized();
    GioVector targetRotation
    {
         DirectX::XMConvertToDegrees(std::atan2(direction.y,std::sqrt(direction.x*direction.x + direction.z*direction.z))),
        DirectX::XMConvertToDegrees(std::atan2(direction.x,direction.z)),
        0.f,
    };

    rotationEuler = targetRotation;
    
    GIO_LOG_F(Log, "Rot is %s", targetRotation.ToString().c_str());
}

std::string GioTransform::ToString() const
{
    std::stringstream stream{};
    stream << "{ P: " << position.ToString() << " | R: " << rotationEuler.ToString() << " | S: " << scale.ToString() << "}";
    return stream.str();
}

