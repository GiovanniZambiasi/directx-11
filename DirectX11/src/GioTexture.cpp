#include "pch.h"
#include "GioTexture.h"

bool GioTexture::IsValid() const
{
    return width > 0 && height > 0 && pixels.size() > 0;
}
