#pragma once
#include "GioVector.h"

struct GioTransform
{
    GioVector position{};

    GioVector rotationEuler{};

    GioTransform operator+ (const GioTransform& other) const;

    GioVector RotationRadians() const;

    void Translate(const GioVector& factor);

    void Rotate(const GioVector& factor);
};
