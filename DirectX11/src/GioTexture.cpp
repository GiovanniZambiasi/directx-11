#include "pch.h"
#include "GioTexture.h"

#include "IRenderingContext.h"
#include "RenderingResources.h"
#include "graphics/BindableTexture.h"
#include "graphics/Sampler.h"

GioTexture::GioTexture(IRenderingContext& graphics, UINT inWidth, UINT inHeight, std::vector<GioColor32>&& inPixels)
    : width(inWidth), height(inHeight), pixels(std::move(inPixels))
{
    if(IsValid())
    {
        textureResource = std::make_shared<BindableTexture>(graphics, width, height, pixels);
        sampler = graphics.GetSharedResources().standardSampler;
    }
}

bool GioTexture::IsValid() const
{
    return width > 0 && height > 0 && pixels.size() > 0;
}

void GioTexture::Flip(bool horizontal)
{
    int w = static_cast<int>(width);
    int h = static_cast<int>(height);
    
    int iterations = static_cast<int>(std::floorf( (horizontal ? w : h) / 2.f));
    for (int i = 0; i < iterations; ++i)
    {
        int topRowFirstElementIndex = horizontal ? i : i * w; 
        int bottomRowFirstElementIndex = horizontal ? (w - 1) - i : ((h - 1) - i) * w;

        int elementsToSwap = static_cast<int>(horizontal ? height : width);
        for (int j = 0; j < elementsToSwap; ++j)
        {
            int topElementIndex = topRowFirstElementIndex + (horizontal ? j * w : j);
            int bottomElementIndex = bottomRowFirstElementIndex + (horizontal ? j * w : j);

            auto top = pixels[topElementIndex];
            pixels[topElementIndex] = pixels[bottomElementIndex];
            pixels[bottomElementIndex] = top;
        }
    }
}

void GioTexture::Bind(IRenderingContext& graphics)
{
    textureResource->Bind(graphics);
    sampler->Bind(graphics);
}
