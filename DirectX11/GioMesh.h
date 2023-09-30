#pragma once
#include <vector>

#include "GioVector.h"

class GioMesh
{
public:
    std::vector<GioVector> vertices{};

    std::vector<UINT> indices{};

    bool IsValid() const;
};
