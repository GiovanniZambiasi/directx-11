#pragma once
#include <vector>

#include "ErrorHandling.h"

class BufferWriter
{
    std::vector<char> bytes{};
    UINT padding{4};
    
public:
    BufferWriter(UINT inPadding);

    void Reserve(UINT size);

    void Reset();

    char* GetData() { return bytes.data(); }

    size_t GetSize() const { return bytes.size(); }

    /**
         * Writes raw data of type T into the buffer, taking padding into account. Data type must have a valid
         * specialization of WriteObjectInternal.
         */
    template <typename T>
    BufferWriter& operator<<(const T& data)
    {
        AddPaddingIfNecessary(sizeof(T));
        WriteObjectInternal(data);
        return *this;
    }

private:
    /**
     * Specialize this template to add support for writing custom types. Never call this method directly, it must
     * always be called from WriteObject, which handles padding.
     */
    template<typename T>
    void WriteObjectInternal(const T& data)
    {
        // Static assert that always fails to enforce specialization
        static_assert(std::is_void_v<T>, "Type provided to BufferWriter has no defined implementation");
    }
 
    void AddPaddingIfNecessary(size_t dataTypeSize);

    void WriteBytes(const char* start, size_t size);
};