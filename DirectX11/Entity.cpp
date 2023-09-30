#include "pch.h"
#include "Entity.h"

#include "graphics/IRenderingContext.h"

Entity::Entity(const GioTransform& spawnTransform)
    : transform(spawnTransform)
{
}

void Entity::Draw(IRenderingContext& graphics)
{
    graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    drawable.Draw(graphics, transform);
}
