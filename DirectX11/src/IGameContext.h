#pragma once
#include <vector>

#include "Core.h"

class IRenderingContext;
class Entity;

class IGameContext
{
public:
    virtual ~IGameContext() = default;

    NO_COPY_MOVE(IGameContext);
    
    template<typename TEntity>
    std::enable_if_t<std::is_base_of_v<Entity, TEntity>> FindEntitiesOfType(std::vector<std::weak_ptr<TEntity>>& outEntities)
    {
        auto& entities = GetEntities();
        for (std::shared_ptr<Entity>& entity : entities)
        {
            if(std::shared_ptr<TEntity> casted = std::dynamic_pointer_cast<TEntity>(entity))
            {
                outEntities.push_back(casted);
            }
        }
    }

    virtual IRenderingContext& GetRenderingContext() = 0;
    
protected:
    IGameContext() = default;
    
    virtual std::vector<std::shared_ptr<Entity>>& GetEntities() = 0;

};
