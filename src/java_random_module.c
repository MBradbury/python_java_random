#include <Python.h>

#include "java_random.h"

typedef struct {
    PyObject_HEAD
    java_random_t rnd;
} JavaRandomObject;

static int JavaRandom_init(JavaRandomObject* self, PyObject* args, PyObject* kwds)
{
    java_random_init(&self->rnd);

    seed_t seed;

    if (!PyArg_ParseTuple(args, "L", &seed))
    {
        return -1;
    }

    java_random_create(&self->rnd, seed);

    return 0;
}
static int JavaRandom_set_seed(JavaRandomObject* self, PyObject* value, void* closure)
{
    if (value == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the seed attribute");
        return -1;
    }

    if (!PyLong_CheckExact(value))
    {
        PyErr_SetString(PyExc_TypeError, "The first attribute value must be an int");
        return -1;
    }

    seed_t seed_value = PyLong_AsLongLong(value);

    java_random_set_seed(&self->rnd, seed_value);

    return 0;
}
static PyObject* JavaRandom_get_seed(JavaRandomObject* self, void* closure)
{
    const seed_t seed = java_random_get_seed(&self->rnd);

    PyObject* result = PyLong_FromLongLong(seed);

    return result;
}
static PyObject* JavaRandom_next(JavaRandomObject* self, PyObject* arg1)
{
    if (!PyLong_CheckExact(arg1))
    {
        PyErr_SetString(PyExc_TypeError, "The first attribute value must be an int");
        return NULL;
    }

    int bits = PyLong_AsLong(arg1);

    long long int next_rnd_bits = java_random_next(&self->rnd, bits);

    PyObject* result = PyLong_FromLongLong(next_rnd_bits);

    return result;
}
static PyObject* JavaRandom_double(JavaRandomObject* self)
{
    double rnd_double = java_random_double(&self->rnd);

    PyObject* result = PyFloat_FromDouble(rnd_double);

    return result;
}
static PyObject* JavaRandom_gaussian(JavaRandomObject* self)
{
    double rnd_gaussian = java_random_gaussian(&self->rnd);

    PyObject* result = PyFloat_FromDouble(rnd_gaussian);

    return result;
}

static PyGetSetDef JavaRandom_getseters[] = {
    {"seed", 
     (getter)JavaRandom_get_seed, (setter)JavaRandom_set_seed,
     "first name",
     NULL},
    {NULL}  /* Sentinel */
};

static PyMethodDef JavaRandom_methods[] = {
    {"next", (PyCFunction)JavaRandom_next, METH_O,
     "Return the next n bits"
    },
    {"nextDouble", (PyCFunction)JavaRandom_double, METH_NOARGS,
     "Return the next random double"
    },
    {"nextGaussian", (PyCFunction)JavaRandom_gaussian, METH_NOARGS,
     "Return the next random gaussian"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject JavaRandomType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "java_random.JavaRandom",             /*tp_name*/
    sizeof(JavaRandomObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "JavaRandom objects",      /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    JavaRandom_methods,             /* tp_methods */
    0,             /* tp_members */
    JavaRandom_getseters,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)JavaRandom_init,      /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

// Methods in the module
static PyMethodDef java_random_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initjava_random(void) 
{
    PyObject* m;

    JavaRandomType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&JavaRandomType) < 0)
        return;

    m = Py_InitModule3("java_random", java_random_methods,
                       "Provides a python interface to Java's random number generator.");

    Py_INCREF(&JavaRandomType);
    PyModule_AddObject(m, "JavaRandom", (PyObject *)&JavaRandomType);
}
