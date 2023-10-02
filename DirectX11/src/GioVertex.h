#pragma once
#include "GioVector.h"

struct GioVertex
{
    GioVector position{.0f};
    GioVector normal{.0f};
    GioUV texCoords{.0f};
};
