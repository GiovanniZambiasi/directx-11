#pragma once

class GioMesh;

class AssetUtils
{
public:
    static GioMesh ImportMesh(const std::string& path);

private:
    AssetUtils() = delete;
};
