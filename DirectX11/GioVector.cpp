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
