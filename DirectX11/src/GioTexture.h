#pragma once
#include <vector>

#include "Core.h"
#include "GioColor.h"
#include "graphics/IBindable.h"

class Sampler;
class BindableTexture;
class IRenderingContext;

class GioTexture : public IBindable
{
    uint32_t width{};
    
    uint32_t height{};

    std::vector<GioColor32> pixels{};

    std::shared_ptr<BindableTexture> textureResource{};

    std::shared_ptr<Sampler> sampler{};
    
public:
    GioTexture() = default;

    GioTexture(IRenderingContext& graphics, UINT inWidth, UINT inHeight, std::vector<GioColor32>&& inPixels);

    NO_COPY_MOVE(GioTexture)
    
    bool IsValid() const;

    void Flip(bool horizontal);
    
    void Bind(IRenderingContext& graphics) override;
};

