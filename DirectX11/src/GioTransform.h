#pragma once
#include "GioRotation.h"
#include "GioVector.h"

struct GioTransform
{
    GioVector position{};

    GioRotation rotation{};

    GioVector scale{1.f};

    GioTransform operator+ (const GioTransform& other) const;

    GioRotation Rotation() const;

    GioVector GetForward() const;

    GioVector GetUp() const;

    GioVector TransformDirection(const GioVector& inDirection) const;
    
    void Translate(const GioVector& factor);

    void Rotate(const GioRotation& factor);

    void LookAt(const GioVector& target);

    std::string ToString() const;
};
