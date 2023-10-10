#include "pch.h"
#include "GioRotation.h"

#include <sstream>

#include "GioVector.h"

GioRotation::GioRotation(float inV)
    : pitch(inV), yaw(inV), roll(inV)
{
}

GioRotation::GioRotation(float inPitch, float inYaw, float inRoll)
    : pitch(inPitch), yaw(inYaw), roll(inRoll)
{
}

GioRotation GioRotation::FromDirection(GioVector inDirection)
{
    inDirection.Normalize();
    auto pitch = atan2f(-inDirection.y, std::sqrtf(inDirection.x*inDirection.x + inDirection.z*inDirection.z));
    auto yaw = atan2f(inDirection.x, inDirection.z);
    return {pitch, yaw, 0.f};
}

GioRotation GioRotation::FromRadians(float inPitch, float inYaw, float inRoll)
{
    return {inPitch, inYaw, inRoll};
}

GioRotation GioRotation::FromDegrees(float inPitch, float inYaw, float inRoll)
{
    return
    {
        DirectX::XMConvertToRadians(inPitch),
        DirectX::XMConvertToRadians(inYaw),
        DirectX::XMConvertToRadians(inRoll)
    };
}

GioRotation GioRotation::operator+(const GioRotation& other) const
{
    return
    {
        pitch + other.pitch,
        yaw + other.yaw,
        roll + other.roll,
    };
}

GioRotation& GioRotation::operator+=(const GioRotation& factor)
{
    GioRotation& thisRef = *this;
    thisRef = thisRef + factor;
    return thisRef;
}

GioRotation GioRotation::operator-() const
{
    return {-pitch, -yaw, -roll};
}

GioRotation GioRotation::ToEuler() const
{
    return
    {
        DirectX::XMConvertToDegrees(pitch),
        DirectX::XMConvertToDegrees(yaw),
        DirectX::XMConvertToDegrees(roll),
    };
}

GioVector GioRotation::ToDirection() const
{
    static const GioVector forward{0.f, 0.f, 1.f};
    static const GioVector up{0.f, 1.f, 0.f};

    return DirectX::XMVector3Transform(forward, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

}

std::string GioRotation::ToString(bool inRadians) const
{
    std::stringstream stream{};
    stream.setf(std::ios::fixed);
    stream.precision(2);
    stream << "(pitch: " << (inRadians ? pitch : DirectX::XMConvertToDegrees(pitch));
    stream <<" yaw: " << (inRadians ? yaw : DirectX::XMConvertToDegrees(yaw));
    stream << " roll: " << (inRadians ? roll : DirectX::XMConvertToDegrees(roll)) << ")";
    return stream.str();
}

