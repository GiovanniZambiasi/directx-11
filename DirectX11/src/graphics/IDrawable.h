#pragma once
#include "IBindable.h"

class IDrawable : public IBindable
{
public:
    virtual ~IDrawable() =default;

    virtual void Draw(IRenderingContext& graphics) = 0;
};
