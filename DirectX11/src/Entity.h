#pragma once
#include "Core.h"
#include "GioTransform.h"
#include "IGameContext.h"
#include "graphics/Drawable.h"

class IGameContext;

class Entity
{
    std::string name{"Unnamed Entity"};

    std::reference_wrapper<IGameContext> gameContext;
    
    GioTransform transform{};

    Drawable drawable{};

public:
    Entity(std::string&& inName, IGameContext& inGame);
    
    Entity(std::string&& inName,  IGameContext& inGame, const GioTransform& spawnTransform);

    virtual ~Entity() = default;

    NO_COPY_MOVE(Entity)

    const std::string& GetName() const { return name; }

    IGameContext& GetGameContext() const { return gameContext.get(); }
    
    Drawable& GetDrawable() { return drawable; }

    GioTransform& GetTransform() { return transform; }

    virtual void Update(float deltaTime) { }
    
    void Draw(IRenderingContext& graphics);
};
