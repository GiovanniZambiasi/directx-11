#pragma once
#include <vector>

struct GioVector;
struct GioTexture;
class GioMesh;

class AssetUtils
{
public:
    static GioMesh ImportMesh(const std::wstring& path);

    static GioTexture ImportTexture(const std::wstring& path);
    
    static std::vector<uint8_t> LoadBGRAImage(const wchar_t* path, uint32_t& outWidth, uint32_t& outHeight);

private:
    AssetUtils() = delete;
};
