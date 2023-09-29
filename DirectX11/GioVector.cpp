#include "pch.h"
#include "GioVector.h"

GioVector GioVector::operator/(float factor) const
{
    return GioVector
    {
        x / factor,
        y / factor,
        z / factor,
    };
}

GioVector GioVector::operator+(const GioVector& other) const
{
    return GioVector
    {
        x + other.x,
        y + other.y,
        z + other.z,
    };
}

GioVector& GioVector::operator+=(const GioVector& other)
{
    GioVector& thisRef = *this;
    thisRef.x += other.x;
    thisRef.y += other.y;
    thisRef.z += other.z;

    return thisRef;
}
