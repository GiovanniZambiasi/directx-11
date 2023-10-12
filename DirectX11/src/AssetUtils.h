#pragma once
#include <unordered_map>
#include <vector>

#include "Core.h"

class IRenderingContext;
struct GioVector;
class GioTexture;
class GioMesh;

class AssetUtils
{
    static std::unique_ptr<AssetUtils> instance;

    std::unordered_map<std::wstring, std::shared_ptr<GioMesh>> meshes{};
    
    std::unordered_map<std::wstring, std::shared_ptr<GioTexture>> textures{};
    
public:
    static AssetUtils& Get();
    
    std::shared_ptr<GioMesh> FindOrLoadMesh(IRenderingContext& graphics, const std::wstring& path);

    std::shared_ptr<GioTexture> FindOrLoadTexture(IRenderingContext& graphics, const std::wstring& path);
    
private:
    AssetUtils() = default;

    NO_COPY_MOVE(AssetUtils);

    static std::vector<uint8_t> LoadBGRAImage(const wchar_t* path, uint32_t& outWidth, uint32_t& outHeight);
    
    std::shared_ptr<GioMesh> LoadMesh(IRenderingContext& graphics, const std::wstring& path);
        
    std::shared_ptr<GioTexture> LoadTexture(IRenderingContext& graphics, const std::wstring& path);
};
