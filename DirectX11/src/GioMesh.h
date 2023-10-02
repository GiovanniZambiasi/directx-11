#pragma once
#include <vector>

#include "GioVertex.h"

struct GioMesh
{
    std::vector<GioVertex> vertices{};

    std::vector<UINT> indices{};

    bool IsValid() const;
};
