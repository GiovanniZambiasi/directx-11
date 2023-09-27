#pragma once

class Graphics;

class Bindable
{
public:
    virtual ~Bindable() = default;

    virtual void Bind(Graphics& graphics) = 0;
    
protected:
    
    
    
};
