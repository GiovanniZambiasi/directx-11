#include "pch.h"
#include "PythonEmbedding.h"

#include <filesystem>
#include <sstream>
#include <thread>

#include "Logger.h"

// https://docs.python.org/3/c-api/intro.html#introduction
#define PY_SSIZE_T_CLEAN
// If _DEBUG flag is defined, python adds a dependency to the debug version of the python lib (which is not included by
// default in a python installation)
#ifdef _DEBUG
  #undef _DEBUG
  #include <python.h>
  #define _DEBUG
#else
  #include <python.h>
#endif

PythonEmbedding::PythonEmbedding()
 
{
}

PythonEmbedding::~PythonEmbedding()
{
}

void PythonEmbedding::Init()
{
    Py_Initialize();
    AddWorkingDirToSysPath();
    
    auto fileName = PyUnicode_DecodeFSDefault("HelloWorld");
    auto module = PyImport_Import(fileName);
    auto function = PyObject_GetAttrString(module, "HelloWorld");
    
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