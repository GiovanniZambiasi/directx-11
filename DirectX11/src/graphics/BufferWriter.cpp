#include "pch.h"
#include "BufferWriter.h"

BufferWriter::BufferWriter(UINT inPadding): padding(inPadding)
{  }

void BufferWriter::Reserve(UINT size)
{
    bytes.reserve(size);
}

void BufferWriter::Reset()
{
    bytes.clear();
}

void BufferWriter::AddPaddingIfNecessary(size_t dataTypeSize)
{
    size_t totalBytes = bytes.size();
    size_t remainingBytesInChunk = padding - totalBytes % padding;

    if(remainingBytesInChunk >= dataTypeSize || remainingBytesInChunk == padding)
        return;
    
    for (size_t i = 0; i < remainingBytesInChunk; ++i)
    {
        bytes.emplace_back(0);
    }
}

void BufferWriter::WriteBytes(const char* start, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        bytes.emplace_back(*start);
        start += 1;
    };
}
