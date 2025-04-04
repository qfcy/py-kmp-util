#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cwchar>
#include <cstdlib>
using namespace std;

using uchar=unsigned char;
using ll=long long;
const ll ERR_STATE=-2;

// Helper function to compute the KMP "partial match" table for wide characters
template<typename T>
void compute_lps(const T *pattern, ll pattern_len, ll *lps) {
    ll length = 0;
    lps[0] = 0; // lps[0] is always 0
    ll i = 1;

    while (i < pattern_len) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm for finding a substring in a byte sequence
template<typename T> // T is char, unsigned char or wchar_t
ll kmp_search(const T *text, ll text_len, const T *pattern, ll pattern_len, ll start=0) {
    if (text_len < pattern_len || start < 0 || start >= text_len) return -1;
    if (pattern_len == 0) return 0; // Empty pattern matches at index 0

    ll *lps = (ll *)malloc(pattern_len * sizeof(ll));
    if (!lps){ // Memory allocation failed
        PyErr_NoMemory();
        return ERR_STATE;
    }

    compute_lps<T>(pattern, pattern_len, lps);

    ll i = start; // index for text
    ll j = 0; // index for pattern
    while (i < text_len) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == pattern_len) {
            free(lps);
            return i - j; // Match found
        } else if (i < text_len && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return -1; // No match found
}

// Python wrapper for find_bytes
static PyObject *find_bytes(PyObject *self, PyObject *args, PyObject *kwargs) {
    const uchar *text;
    const uchar *pattern;
    Py_ssize_t text_len;
    Py_ssize_t pattern_len;
    PyObject *start_arg = nullptr;

    static const char *kwlist[] = {"byte", "sub", "start", nullptr};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y#y#|O", (char **)kwlist, &text,
        &text_len, &pattern, &pattern_len, &start_arg))
        return nullptr;

    ll start = 0;
    if(start_arg){
        start = PyLong_AsLongLong(start_arg);
        if(PyErr_Occurred()) return nullptr;
    }

    ll result = kmp_search(text, (ll)text_len, pattern, (ll)pattern_len, start);
    if (result == ERR_STATE) return nullptr;
    return PyLong_FromLongLong(result);
}

// Python wrapper for find_str
static PyObject *find_str(PyObject *self, PyObject *args, PyObject *kwargs) {
    const wchar_t *text;
    const wchar_t *pattern;
    Py_ssize_t text_len;
    Py_ssize_t pattern_len;
    PyObject *start_arg = nullptr;

    static const char *kwlist[] = {"string", "sub", "start", nullptr};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "u#u#|O", (char **)kwlist, &text,
        &text_len, &pattern, &pattern_len, &start_arg))
        return nullptr;

    ll start = 0;
    if(start_arg){
        start = PyLong_AsLongLong(start_arg);
        if(PyErr_Occurred()) return nullptr;
    }

    ll result = kmp_search(text, (ll)text_len, pattern, (ll)pattern_len, start);
    if (result == ERR_STATE) return nullptr;
    return PyLong_FromLongLong(result);
}

static PyMethodDef KmpUtilMethods[] = {
    {"find_bytes", (PyCFunction)find_bytes, METH_VARARGS | METH_KEYWORDS,
        "find_bytes(byte,sub,start=0): Find a byte pattern in a bytes sequence using KMP algorithm."},
    {"find_str", (PyCFunction)find_str, METH_VARARGS | METH_KEYWORDS,
        "find_str(string,sub,start=0): Find a string pattern in a string using KMP algorithm."},
    {nullptr, nullptr, 0, nullptr} // Sentinel
};

static struct PyModuleDef kmp_util_module = {
    PyModuleDef_HEAD_INIT,
    "kmp_util", // Module name
    "A module providing KMP-based search for strings and bytes.",
    -1,
    KmpUtilMethods
};

PyMODINIT_FUNC PyInit_kmp_util(void) {
    return PyModule_Create(&kmp_util_module);
}