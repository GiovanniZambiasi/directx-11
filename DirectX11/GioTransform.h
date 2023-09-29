#pragma once
#include "GioVector.h"

struct GioTransform
{
    GioVector position{};

    GioVector rotation{};

    GioTransform operator+ (const GioTransform& other) const;

    void Translate(const GioVector& factor);

    void Rotate(const GioVector& factor);
};
