#pragma once

#include <exception>

class GioException : public std::exception
{
    std::string formattedWhat{};

    std::string file{};
    
    int line{};
    
public:
    GioException(const char* what, const char* file, int line);

    char const* what() const override;

protected:
    void UpdateFormattedString(const char* what);
};

class GioHRESULTException : public GioException
{
public:
    GioHRESULTException(HRESULT result, const char* file, int line);
};

#define GIO_THROW(what) throw GioException{what, __FILE__, __LINE__};

#define GIO_THROW_IF_FAILED(methodCall)\
    if(HRESULT result = (methodCall))\
        if (FAILED(result)) throw GioHRESULTException{result, __FILE__, __LINE__};