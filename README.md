# kmp_util

`kmp_util` is a Python C extension module that provides efficient substring search functionality using the Knuth-Morris-Pratt (KMP) algorithm. It supports searching for patterns in both byte sequences and Unicode strings.

## Features

- **`find_bytes`**: Searches for a byte pattern in a byte sequence.
- **`find_str`**: Searches for a substring in a Unicode string. Fully supports UTF-8 and Unicode characters.

Both functions return the starting index of the first occurrence of the pattern in the text, or `-1` if the pattern is not found.

## Installation

To install the module, run the following commands:

```bash
python setup.py build
python setup.py install
```

## Example Usage

```python
import kmp_util

# Example 1: Using find_bytes to search in a byte sequence
result = kmp_util.find_bytes(b'111', b'2')
print(result)  # Output: -1 (pattern not found)

# Example 2: Using find_str to search in a Unicode string
result = kmp_util.find_str('abc中文', '文')
print(result)  # Output: 4 (pattern found at index 4)
```

### Functions

#### `find_bytes(text: bytes, pattern: bytes) -> int`

Searches for the first occurrence of the byte pattern in the byte sequence.

- **Parameters**:
  - `text` (bytes): The byte sequence to search in.
  - `pattern` (bytes): The byte pattern to search for.
- **Returns**:
  - The starting index of the first occurrence of the pattern in the text, or `-1` if the pattern is not found.

#### `find_str(text: str, pattern: str) -> int`

Searches for the first occurrence of the substring in the Unicode string.

- **Parameters**:
  - `text` (str): The Unicode string to search in.
  - `pattern` (str): The substring to search for.
- **Returns**:
  - The starting index of the first occurrence of the pattern in the text, or `-1` if the pattern is not found.

---

## Notes

- `find_bytes` operates on raw byte sequences (`bytes` in Python).
- `find_str` operates on Unicode strings (`str` in Python) and fully supports UTF-8 encoded characters.

## License

This module is open-source and available under the MIT License.
