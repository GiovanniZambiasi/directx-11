#pragma once

class PythonEmbedding
{
public:
    PythonEmbedding();
    
    ~PythonEmbedding();
    
    void Init();

private:
    void AddWorkingDirToSysPath();
};
