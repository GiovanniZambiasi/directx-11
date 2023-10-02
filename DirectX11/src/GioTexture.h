#pragma once
#include <vector>

struct GioTexture
{
    uint32_t width{};
    
    uint32_t height{};

    std::vector<uint8_t> pixels{};

    bool IsValid() const;
};
