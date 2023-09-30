#include "pch.h"
#include "AssetUtils.h"

#include <iostream>

#include "GioMesh.h"

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

GioMesh AssetUtils::ImportMesh(const std::string& path)
{
    Assimp::Importer imp{};
    const aiScene* model = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    assert(model->mNumMeshes);
    aiMesh* mesh = model->mMeshes[0];
    std::cout << "Model '" << path << "' has " << mesh->mNumVertices << " vertices!" << std::endl;

    std::vector<GioVector> vertices{};
    vertices.reserve(mesh->mNumVertices);
    for (int i = 0; i < mesh->mNumVertices; ++i)
    {
        aiVector3D vertex = mesh->mVertices[i];
        vertices.emplace_back(vertex.x, vertex.y, vertex.z);
    }

    std::vector<UINT> indices{};
    indices.reserve(mesh->mNumFaces);
    for (int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        for (int j = 0; j < face.mNumIndices; ++j)
        {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    return GioMesh{std::move(vertices), std::move(indices)};
}
