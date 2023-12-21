#include <Python.h>

// Function to compute the sum of an array
static PyObject* sum_array(PyObject* self, PyObject* args) {
    PyObject *listObj;
    if (!PyArg_ParseTuple(args, "O", &listObj)) {
        return NULL;
    }

    long length = PyList_Size(listObj);
    long sum = 0;
    for (long i = 0; i < length; i++) {
        PyObject* temp = PyList_GetItem(listObj, i);
        if (!PyLong_Check(temp)) {
            return NULL;
        }
        sum += PyLong_AsLong(temp);
    }
    return PyLong_FromLong(sum);
}

// Method definitions for this module
static PyMethodDef SumMethods[] = {
    {"sum_array", sum_array, METH_VARARGS, "Sum an array of integers."},
    {NULL, NULL, 0, NULL}
};

// Module definition
static struct PyModuleDef summodule = {
    PyModuleDef_HEAD_INIT,
    "summodule",
    NULL,
    -1,
    SumMethods
};

// Initialization function for this module
PyMODINIT_FUNC PyInit_summodule(void) {
    return PyModule_Create(&summodule);
}

