#pragma once

class IRenderingContext;

class IBindable
{
public:
    virtual ~IBindable() = default;

    virtual void Bind(IRenderingContext& graphics) = 0;
    
};
