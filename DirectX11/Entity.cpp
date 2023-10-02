#include "pch.h"
#include "Entity.h"

#include "graphics/IRenderingContext.h"

Entity::Entity(std::string&& inName)
    : name(std::move(inName))
{
}

Entity::Entity(std::string&& inName, const GioTransform& spawnTransform)
    : name(std::move(inName)), transform(spawnTransform)
{
}

void Entity::Draw(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    drawable.Draw(graphics, transform);
}
