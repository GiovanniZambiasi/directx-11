#include "pch.h"
#include "ErrorHandling.h"
#include <sstream>
#include <iomanip>

GioException::GioException(const char* what, const char* file, int line)
    : std::exception(what), file(file), line(line)
{
    UpdateFormattedString(what);
}

char const* GioException::what() const
{
    return formattedWhat.c_str();
}

void GioException::UpdateFormattedString(const char* what)
{
    std::stringstream stream{};
    stream << "[Exception]: \"" << what << "\" (" << file << " @ " << line << ")" << std::endl;
    formattedWhat = stream.str();
}

GioHRESULTException::GioHRESULTException(HRESULT result, const char* file, int line)
    : GioException(std::string{"HRESULT code " + std::to_string(result)}.c_str(), file, line)
{
    std::stringstream stream{};
    stream <<"HRESULT code 0x" << std::hex << result;
    UpdateFormattedString(stream.str().c_str());
}

