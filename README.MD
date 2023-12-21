# Creating C modules and importing them as extensions in Python

Using C extensions in Python is a great way to speed up computation-intensive tasks. Here's a simple example where we will create a C extension module to speed up a computation task, such as summing an array of integers.

We'll do the following:

1. Write a C function that computes the sum of an array of integers.
2. Create a Python extension module using this C function.
3. Load and use this extension in a Jupyter notebook.


First, let's start with the C code for the sum function. We will use the Python C API to integrate this with Python.

## Create the C library file

```
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
```
## Create setup.py file

We need to compile this C code into a Python extension module. Typically, this is done using a setup.py script. Here's a simple example:

```
from setuptools import setup, Extension

module = Extension('summodule', sources=['summodule.c'])

setup(
    name='SumModule',
    version='1.0',
    description='Python Package with C Extension for summing arrays',
    ext_modules=[module]
)
```

## Build and install

To build and install this extension, you would normally run the following commands in your terminal:

Bash
<code> python setup.py build </code>
<code> python setup.py install </code>

## Use module in a script 

Once installed, you can use the extension in a Jupyter notebook like this:

```
import summodule

# Example usage
array = [1, 2, 3, 4, 5]
result = summodule.sum_array(array)
print(f"Sum of array: {result}")
```

Remember, this is a basic example. Real-world scenarios might require more complex handling, especially with regards to memory management and error checking in C code.