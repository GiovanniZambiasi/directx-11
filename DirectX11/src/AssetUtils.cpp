#include "pch.h"
#include "AssetUtils.h"

#include <iostream>

#include "GioMesh.h"

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <wincodec.h>

#include "ErrorHandling.h"
#include "GioColor.h"
#include "GioTexture.h"

using namespace Microsoft::WRL;

std::unique_ptr<AssetUtils> AssetUtils::instance{};

AssetUtils& AssetUtils::Get()
{
    if(!instance)
    {
        instance = std::unique_ptr<AssetUtils>{new AssetUtils{}};
    }

    return *instance;
}

std::shared_ptr<GioMesh> AssetUtils::FindOrLoadMesh(IRenderingContext& graphics, const std::wstring& path)
{
    auto resourceEntry = meshes.find(path);

    if(resourceEntry == meshes.end())
    {
        std::shared_ptr<GioMesh> resource = LoadMesh(graphics, path);
        meshes.emplace(path, resource);
        return resource;
    }
    
    return resourceEntry->second;
}

std::shared_ptr<GioTexture> AssetUtils::FindOrLoadTexture(IRenderingContext& graphics, const std::wstring& path)
{
    auto textureIt = textures.find(path);

    if(textureIt == textures.end())
    {
        std::shared_ptr<GioTexture> texture = LoadTexture(graphics, path);
        textures.emplace(path, texture);
        return texture;
    }

    return textureIt->second;
}

std::vector<uint8_t> AssetUtils::LoadBGRAImage(const wchar_t* path, uint32_t& outWidth, uint32_t& outHeight)
{
    ComPtr<IWICImagingFactory> wicFactory;
    GIO_THROW_IF_FAILED(CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory)));

    ComPtr<IWICBitmapDecoder> decoder;
    GIO_THROW_IF_FAILED(wicFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, decoder.GetAddressOf()));

    ComPtr<IWICBitmapFrameDecode> frame;
    GIO_THROW_IF_FAILED(decoder->GetFrame(0, frame.GetAddressOf()));

    GIO_THROW_IF_FAILED(frame->GetSize(&outWidth, &outHeight));

    WICPixelFormatGUID pixelFormat;
    GIO_THROW_IF_FAILED(frame->GetPixelFormat(&pixelFormat));

    uint32_t rowPitch = outWidth * sizeof(uint32_t);
    uint32_t imageSize = rowPitch * outHeight;

    std::vector<uint8_t> image;
    image.resize(size_t(imageSize));

    if (memcmp(&pixelFormat, &GUID_WICPixelFormat32bppBGRA, sizeof(GUID)) == 0)
    {
        GIO_THROW_IF_FAILED(frame->CopyPixels(nullptr, rowPitch, imageSize, reinterpret_cast<BYTE*>(image.data())));
    }
    else
    {
        ComPtr<IWICFormatConverter> formatConverter;
        GIO_THROW_IF_FAILED(wicFactory->CreateFormatConverter(formatConverter.GetAddressOf()));

        BOOL canConvert = FALSE;
        GIO_THROW_IF_FAILED(formatConverter->CanConvert(pixelFormat, GUID_WICPixelFormat32bppBGRA, &canConvert));
        if (!canConvert)
        {
            throw std::exception("CanConvert");
        }

        GIO_THROW_IF_FAILED(formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppBGRA,
            WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeMedianCut));

        GIO_THROW_IF_FAILED(formatConverter->CopyPixels(nullptr, rowPitch, imageSize, reinterpret_cast<BYTE*>(image.data())));
    }

    return image;
}

std::shared_ptr<GioMesh> AssetUtils::LoadMesh(IRenderingContext& graphics, const std::wstring& path)
{
    std::string narrowPath{path.begin(), path.end()};
    Assimp::Importer imp{};
    const aiScene* model = imp.ReadFile(narrowPath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded);
    assert(model);
    assert(model->mNumMeshes);
    aiMesh* mesh = model->mMeshes[0];
    bool hasNormals = mesh->HasNormals();
    bool hasTexCoords = mesh->HasTextureCoords(0);
    aiVector3D* textureCoordinatesArray = mesh->mTextureCoords[0];

    std::vector<GioVertex> vertices{};
    vertices.reserve(mesh->mNumVertices);
    for (int i = 0; i < mesh->mNumVertices; ++i)
    {
        aiVector3D vertex = mesh->mVertices[i];
        aiVector3D normal = hasNormals ? mesh->mNormals[i] : aiVector3D{0.f};
        aiVector3D texCoords = hasTexCoords ? textureCoordinatesArray[i] : aiVector3D{0.f};
        
        vertices.push_back(
            GioVertex
            {
                {vertex.x, vertex.y, vertex.z},
                {normal.x, normal.y, normal.z},
                {texCoords.x, texCoords.y}
            });
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

    return std::make_shared<GioMesh>(graphics, std::move(vertices), std::move(indices));
}

std::shared_ptr<GioTexture> AssetUtils::LoadTexture(IRenderingContext& graphics, const std::wstring& path)
{
    uint32_t width{0};
    uint32_t height{0};
    
    std::vector<uint8_t> data = LoadBGRAImage(path.c_str(), width, height);
    std::vector<GioColor32> colors{};
    colors.reserve(data.size()/4);
    for (size_t i = 0; i < data.size(); i += 4)
    {
        assert(i + 3 < data.size());
        uint8_t r = data[i];
        uint8_t g = data[i + 1];
        uint8_t b = data[i + 2];
        uint8_t a = data[i + 3];
        colors.emplace_back(r,g,b,a);
    }
    
    return std::make_shared<GioTexture>(graphics, width, height, std::move(colors));
}
