#include "pch.h"
#include "GioVector.h"

#include <sstream>

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

std::string GioVector::ToString() const
{
    std::stringstream stream{};
    stream.setf(std::ios::fixed);
    stream.precision(2);
    stream << "(x: " << x <<" y: " << y << " z: " << z << ")";
    return stream.str();
}
