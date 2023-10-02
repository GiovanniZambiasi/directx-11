#pragma once

#include <exception>
#include <vector>

#define GIO_THROW(what) throw GioException{what, __FILE__, __LINE__};

#define GIO_THROW_INFO(what, extraInfo) throw GioException{what, __FILE__, __LINE__, extraInfo};

#define GIO_THROW_IF_FAILED(methodCall)\
    if(HRESULT result = (methodCall))\
        if (FAILED(result)) throw GioHRESULTException{result, __FILE__, __LINE__};

class GioException : public std::exception
{
    std::string formattedWhat{};

    std::string file{};

    std::string extraInfo{};
    
    int line{};
    
public:
    GioException(const char* what, const char* file, int line, std::string extraInfo = {} );

    char const* what() const override;

protected:
    void UpdateFormattedString(const char* what, const std::string& inExtraInfo);
};

class GioHRESULTException : public GioException
{
    std::string extraInfo{};
    
public:
    GioHRESULTException(HRESULT result, const char* file, int line);

private:
    static std::string FormatMessageHeader(HRESULT result);
};

class DXGIInfoUtils
{
    UINT64 next = 0u;
    
    struct IDXGIInfoQueue* infoQueue{};

    static DXGIInfoUtils* instance;
    
public:
    static void Init();
    
    static DXGIInfoUtils* Get();

    std::string GetMessages();
    
private:
    DXGIInfoUtils();

    ~DXGIInfoUtils();
};