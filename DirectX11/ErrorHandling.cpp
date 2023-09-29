#include "pch.h"
#include "ErrorHandling.h"
#include <sstream>
#include <iomanip>
#include <dxgidebug.h>

GioException::GioException(const char* what, const char* file, int line, std::string extraInfo)
    : std::exception(what), file(file), line(line)
{
    UpdateFormattedString(what, std::move(extraInfo));
}

char const* GioException::what() const
{
    return formattedWhat.c_str();
}

void GioException::UpdateFormattedString(const char* what, const std::string& inExtraInfo)
{
    std::stringstream stream{};
    stream << "[Exception]: \"";
    stream << (what != nullptr ? what : "Unknown");
    stream << "\" (" << file << " @ " << line << ")" << std::endl;

    if(!inExtraInfo.empty())
    {
        stream << "[Extra Info]:\n" << inExtraInfo;
    }
    
    formattedWhat = stream.str();
}

GioHRESULTException::GioHRESULTException(HRESULT result, const char* file, int line)
    : GioException(FormatMessageHeader(result).c_str(), file, line, DXGIInfoUtils::Get()->GetMessages())
{ }

std::string GioHRESULTException::FormatMessageHeader(HRESULT result)
{
    std::stringstream stream{};
    stream <<"HRESULT code 0x" << std::hex << result;
    return stream.str();
}

DXGIInfoUtils* DXGIInfoUtils::instance{nullptr};

void DXGIInfoUtils::Init()
{
    if(!instance)
    {
        instance = new DXGIInfoUtils{};
    }
}

DXGIInfoUtils* DXGIInfoUtils::Get()
{
    assert(instance);
    return instance;
}

DXGIInfoUtils::DXGIInfoUtils()
{
    // define function signature of DXGIGetDebugInterface
    typedef HRESULT (WINAPI* DXGIGetDebugInterface)(REFIID,void **);

    // load the dll that contains the function DXGIGetDebugInterface
    const auto hModDxgiDebug = LoadLibraryEx( L"dxgidebug.dll",nullptr,LOAD_LIBRARY_SEARCH_SYSTEM32 );
    if( hModDxgiDebug == nullptr )
    {
        GIO_THROW("Failed to load library");
    }

    // get address of DXGIGetDebugInterface in dll
    const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
        reinterpret_cast<void*>(GetProcAddress( hModDxgiDebug,"DXGIGetDebugInterface" ))
    );
    if( DxgiGetDebugInterface == nullptr )
    {
        GIO_THROW("Failed to get DXGIDebugInterface");
    }

    DxgiGetDebugInterface( __uuidof(IDXGIInfoQueue),reinterpret_cast<void**>(&infoQueue) );
}

DXGIInfoUtils::~DXGIInfoUtils()
{
    infoQueue->Release();
}

std::string DXGIInfoUtils::GetMessages()
{
    std::stringstream messages{};
    const auto end = infoQueue->GetNumStoredMessages( DXGI_DEBUG_ALL );
    for( auto i = next; i < end; i++ )
    {
        SIZE_T messageLength;
        // get the size of message i in bytes
        GIO_THROW_IF_FAILED(infoQueue->GetMessage( DXGI_DEBUG_ALL,i,nullptr,&messageLength ) );
        // allocate memory for message
        auto bytes = std::make_unique<byte[]>( messageLength );
        auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
        // get the message and push its description into the vector
        GIO_THROW_IF_FAILED( infoQueue->GetMessage( DXGI_DEBUG_ALL,i,pMessage,&messageLength ) );
        messages << pMessage->pDescription << std::endl;
    }

    next = end;
    return messages.str();
}
