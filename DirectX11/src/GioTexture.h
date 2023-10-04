#pragma once
#include <vector>

#include "GioColor.h"

struct GioTexture
{
    uint32_t width{};
    
    uint32_t height{};

    std::vector<GioColor32> pixels{};

    bool IsValid() const;

    void Flip(bool horizontal);
};

