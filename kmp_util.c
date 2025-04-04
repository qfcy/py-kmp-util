#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <wchar.h>
#include <stdlib.h>

// Helper function to compute the KMP "partial match" table for bytes
void compute_lps_bytes(const char *pattern, int pattern_len, int *lps) {
    int length = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;

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

// Helper function to compute the KMP "partial match" table for wide characters
void compute_lps_wchar(const wchar_t *pattern, int pattern_len, int *lps) {
    int length = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;

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
int kmp_search_bytes(const char *text, int text_len, const char *pattern, int pattern_len) {
    if (pattern_len == 0) return 0; // Empty pattern matches at index 0
    if (text_len < pattern_len) return -1;

    int *lps = (int *)malloc(pattern_len * sizeof(int));
    if (!lps) return -1; // Memory allocation failed

    compute_lps_bytes(pattern, pattern_len, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
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

// KMP algorithm for finding a substring in a wide character string
int kmp_search_wchar(const wchar_t *text, int text_len, const wchar_t *pattern, int pattern_len) {
    if (pattern_len == 0) return 0; // Empty pattern matches at index 0
    if (text_len < pattern_len) return -1;

    int *lps = (int *)malloc(pattern_len * sizeof(int));
    if (!lps) return -1; // Memory allocation failed

    compute_lps_wchar(pattern, pattern_len, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
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
static PyObject *find_bytes(PyObject *self, PyObject *args) {
    const char *text;
    const char *pattern;
    Py_ssize_t text_len;
    Py_ssize_t pattern_len;

    if (!PyArg_ParseTuple(args, "y#y#", &text, &text_len, &pattern, &pattern_len)) {
        return NULL;
    }

    int result = kmp_search_bytes(text, (int)text_len, pattern, (int)pattern_len);
    return PyLong_FromLong(result);
}

// Python wrapper for find_str
static PyObject *find_str(PyObject *self, PyObject *args) {
    const wchar_t *text;
    const wchar_t *pattern;
    Py_ssize_t text_len;
    Py_ssize_t pattern_len;

    if (!PyArg_ParseTuple(args, "u#u#", &text, &text_len, &pattern, &pattern_len)) {
        return NULL;
    }

    int result = kmp_search_wchar(text, (int)text_len, pattern, (int)pattern_len);
    return PyLong_FromLong(result);
}

// Method definitions
static PyMethodDef KmpUtilMethods[] = {
    {"find_bytes", find_bytes, METH_VARARGS, "find_bytes(byte,sub): Find a byte pattern in a byte sequence using KMP algorithm."},
    {"find_str", find_str, METH_VARARGS, "find_str(str,sub): Find a string pattern in a wide character string using KMP algorithm."},
    {NULL, NULL, 0, NULL} // Sentinel
};

// Module definition
static struct PyModuleDef kmp_util_module = {
    PyModuleDef_HEAD_INIT,
    "kmp_util", // Module name
    "A module that provides KMP-based search for bytes and wide character strings.",
    -1,
    KmpUtilMethods
};

// Module initialization
PyMODINIT_FUNC PyInit_kmp_util(void) {
    return PyModule_Create(&kmp_util_module);
}