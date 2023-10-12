#pragma once
#include "Core.h"
#include "GioTransform.h"
#include "IGameContext.h"
#include "RenderingComponent.h"

class IGameContext;

class Entity
{
    std::string name{"Unnamed Entity"};

    std::reference_wrapper<IGameContext> gameContext;
    
    GioTransform transform{};

    RenderingComponent rendering{};

public:
    Entity(std::string&& inName, IGameContext& inGame);
    
    Entity(std::string&& inName,  IGameContext& inGame, const GioTransform& spawnTransform);

    virtual ~Entity() = default;

    NO_COPY_MOVE(Entity)

    const std::string& GetName() const { return name; }

    IGameContext& GetGameContext() const { return gameContext.get(); }
    
    RenderingComponent& GetRenderingComponent() { return rendering; }

    GioTransform& GetTransform() { return transform; }

    virtual void Update(float deltaTime) { }
    
    void Draw(IRenderingContext& graphics);
};
