#pragma once
#include <vector>

#include "GioVertex.h"

class GioMesh
{
public:
    std::vector<GioVertex> vertices{};

    std::vector<UINT> indices{};

    bool IsValid() const;
};
