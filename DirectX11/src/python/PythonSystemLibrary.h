// ReSharper disable CppInconsistentNaming
#pragma once

class PythonSystemLibrary
{
public:
    static PyObject* handshake_cpp(PyObject* self, PyObject* args);

    inline static PyMethodDef handshakeDef[] = {
        {"handshake_cpp", handshake_cpp, METH_VARARGS, "Shakes hand from C++!"}, {nullptr, nullptr, 0, nullptr}
    };

    static inline const std::string moduleName = "PythonSystemLibrary";

    inline static PyModuleDef moduleDef = {PyModuleDef_HEAD_INIT, moduleName.c_str(), nullptr, -1, handshakeDef};

    static PyObject* CreateModule();
    
private:
    
};
