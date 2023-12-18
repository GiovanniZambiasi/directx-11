#include "pch.h"
#include "PythonSystemLibrary.h"

#include "Logger.h"

PyObject* PythonSystemLibrary::handshake_cpp(PyObject* self, PyObject* args)
{
    GIO_LOG(Log, "C++ is shaking hands!");
    Py_RETURN_NONE;
}

PyObject* PythonSystemLibrary::CreateModule()
{
    return PyModule_Create(&moduleDef);
}
