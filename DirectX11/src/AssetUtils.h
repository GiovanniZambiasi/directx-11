#pragma once
#include <vector>

struct GioVector;
struct GioTexture;
struct GioMesh;

class AssetUtils
{
public:
    static GioMesh ImportMesh(const std::wstring& path);

    static GioTexture ImportTexture(const std::wstring& path);
    
    static std::vector<uint8_t> LoadBGRAImage(const wchar_t* path, uint32_t& outWidth, uint32_t& outHeight);

private:
    AssetUtils() = delete;
};
