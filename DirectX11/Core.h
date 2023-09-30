#pragma once

#include "ErrorHandling.h"

#define NO_COPY(TypeName)\
    TypeName(const TypeName&) = delete;\
    TypeName& operator=(const TypeName&) = delete;

#define NO_MOVE(TypeName)\
TypeName(TypeName&&) = delete;\
TypeName& operator=(TypeName&&) = delete;

#define NO_COPY_MOVE(TypeName)\
    NO_COPY(TypeName) NO_MOVE(TypeName)