#pragma once
#include "GioVector.h"

struct GioTransform
{
    GioVector position{};

    GioVector rotationEuler{};

    GioVector scale{1.f};

    GioTransform operator+ (const GioTransform& other) const;

    GioVector RotationRadians() const;

    GioVector GetForward() const;

    void Translate(const GioVector& factor);

    void Rotate(const GioVector& factor);
};
