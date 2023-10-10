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
    stream << "{ P: " << position.ToString() << " | R: " << rotation.ToString() << " | S: " << scale.ToString() << "}";
    return stream.str();
}

