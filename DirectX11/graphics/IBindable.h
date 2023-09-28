#pragma once

class Graphics;

class IBindable
{
public:
    virtual ~IBindable() = default;

    virtual void Bind(Graphics& graphics) = 0;
    
protected:
    
    
    
};
