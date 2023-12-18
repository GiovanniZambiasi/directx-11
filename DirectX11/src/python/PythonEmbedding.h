#pragma once
#include "PythonEmbedding.h"

class PythonEmbedding
{
public:
    PythonEmbedding();
    
    ~PythonEmbedding();
    
    void Init();

private:
    void AddWorkingDirToSysPath();

    void InitializeSystemLibraries();
};

