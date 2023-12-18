#include "pch.h"
#include "PythonEmbedding.h"

#include <filesystem>
#include <sstream>
#include <thread>

#include "Logger.h"
#include "PythonSystemLibrary.h"

PythonEmbedding::PythonEmbedding()
 
{
}

PythonEmbedding::~PythonEmbedding()
{
}

void PythonEmbedding::Init()
{
    InitializeSystemLibraries();
    Py_Initialize();
    AddWorkingDirToSysPath();
    
    auto fileName = PyUnicode_DecodeFSDefault("Handshake");
    auto module = PyImport_Import(fileName);
    auto function = PyObject_GetAttrString(module, "handshake_python");
    
    if(function && PyCallable_Check(function))
    {
        PyObject_CallObject(function, nullptr);
    }
    
    Py_Finalize();
}

void PythonEmbedding::AddWorkingDirToSysPath()
{
    /* TODO - This conversion to narrow strings may result in the path being broken. Test if the path is still valid after
     conversion, and warn if not. Fix this in the future to use wide path */
    std::filesystem::path scriptsPath{std::filesystem::current_path()};
    scriptsPath.append("res");
    scriptsPath.append("scripts");
    std::string scriptsPathNarrow = scriptsPath.string();
    for (int i = 0; i < scriptsPathNarrow.length(); ++i)
    {
        if(scriptsPathNarrow[i] == '\\')
        {
            scriptsPathNarrow.insert(scriptsPathNarrow.begin() + i, '\\');
            ++i;
        }
    }
    std::replace(scriptsPathNarrow.begin(), scriptsPathNarrow.end(), L'\\', L'\\');
    PyRun_SimpleString("import sys");
    std::stringstream stream{};
    stream << "sys.path.append('" <<  scriptsPathNarrow << "')";
    PyRun_SimpleString(stream.str().c_str());
    GIO_LOG_F(Log, "Appending scripts path '%s' to python sys.path", scriptsPathNarrow.c_str());
}

void PythonEmbedding::InitializeSystemLibraries()
{
    PyImport_AppendInittab(PythonSystemLibrary::moduleName.c_str(), &PythonSystemLibrary::CreateModule);
}