#include "pch.h"
#include "GioMesh.h"

bool GioMesh::IsValid() const
{
    return vertices.size() > 0 && indices.size() > 0;
}
