﻿#pragma once

/**
 * Facilitates creation of "padding" variables to match byte alignment with hlsl 
 * \param Id An arbitrary name for the padding variables
 */
#define PADDING(Bytes, Id) char Id[Bytes];

enum class CBufferTypesVertex
{
    Invalid = -1,
    Transformation,
};

enum class CBufferTypesPixel
{
    Invalid = -1,
    Lights,
};
