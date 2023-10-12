#include "pch.h"
#include "Entity.h"

#include "IRenderingContext.h"

Entity::Entity(std::string&& inName, IGameContext& inGame)
    : Entity(std::move(inName), inGame, GioTransform{})
{
}

Entity::Entity(std::string&& inName, IGameContext& inGame, const GioTransform& spawnTransform)
    : name(std::move(inName)), gameContext(inGame), transform(spawnTransform)
{
}

void Entity::Draw(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    rendering.Draw(graphics, transform);
}
