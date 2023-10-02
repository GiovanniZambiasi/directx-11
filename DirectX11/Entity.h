#pragma once
#include "Core.h"
#include "GioTransform.h"
#include "graphics/Drawable.h"

class Entity : public IDrawable
{
    std::string name{"Unnamed Entity"};
    
    GioTransform transform{};

    Drawable drawable{};

public:
    Entity(std::string&& inName);
    
    Entity(std::string&& inName, const GioTransform& spawnTransform);

    NO_COPY_MOVE(Entity)

    const std::string& GetName() const { return name; }
    
    Drawable& GetDrawable() final override { return drawable; }

    GioTransform& GetTransform() { return transform; }

    virtual void Update(float deltaTime) { }
    
    void Draw(IRenderingContext& graphics) override;
};
