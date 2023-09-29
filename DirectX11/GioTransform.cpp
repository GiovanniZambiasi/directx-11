#include "pch.h"
#include "GioTransform.h"

GioTransform GioTransform::operator+(const GioTransform& other) const
{
    return GioTransform
    {
        position + other.position,
        rotation + other.rotation,
    };
}

void GioTransform::Translate(const GioVector& factor)
{
    position += factor;
}

void GioTransform::Rotate(const GioVector& factor)
{
    rotation += factor;
}
