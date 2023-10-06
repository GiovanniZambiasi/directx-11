﻿#include "pch.h"
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

GioVector GioVector::operator-(const GioVector& other) const
{
    return { x - other.x, y - other.y, z - other.z };
}

GioVector GioVector::operator*(float rhs) const
{
    return { x * rhs, y * rhs, z * rhs};
}

GioVector GioVector::operator-() const
{
    return *this * -1.f;
}

GioVector& GioVector::operator+=(const GioVector& other)
{
    GioVector& thisRef = *this;
    thisRef.x += other.x;
    thisRef.y += other.y;
    thisRef.z += other.z;

    return thisRef;
}

GioVector::operator DirectX::XMVECTOR() const
{
    return {x, y, z};
}

float GioVector::Magnitude() const
{
    return std::sqrt(x*x + y*y + z*z);
}

GioVector GioVector::Normalized() const
{
    float magnitude = Magnitude();
    
    if(magnitude == 0.f)
    {
        return {0.f};
    }

    return *this/magnitude;
}

void GioVector::Normalize()
{
    *this = Normalized();
}

GioVector GioVector::EulerToRadians() const
{
    return
    {
        DirectX::XMConvertToRadians(x),
        DirectX::XMConvertToRadians(y),
        DirectX::XMConvertToRadians(z),
    };
}

GioVector GioVector::RadiansToEuler() const
{
    return
    {
        DirectX::XMConvertToDegrees(x),
        DirectX::XMConvertToDegrees(y),
        DirectX::XMConvertToDegrees(z),
    };
}

float GioVector::Dot(const GioVector& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

std::string GioVector::ToString() const
{
    std::stringstream stream{};
    stream.setf(std::ios::fixed);
    stream.precision(2);
    stream << "(x: " << x <<" y: " << y << " z: " << z << ")";
    return stream.str();
}
