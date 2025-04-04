# kmp_util

`kmp_util` is a Python C extension module that provides efficient substring search functionality using the Knuth-Morris-Pratt (KMP) algorithm. It supports almost all Python 3 versions from 3.5 to 3.14.

## Installation

```bash
pip install kmp-util
```

## Example Usage

The `kmp_util` module supports searching for patterns in both byte sequences and Unicode strings.

```python
import kmp_util

result = kmp_util.find_bytes(b'111', b'2', 1)
print(result)  # Output: -1 (pattern not found)

result = kmp_util.find_str('abc中文', '文')
print(result)  # Output: 4 (pattern found at index 4)
```

### Functions

#### `find_bytes(text: bytes, pattern: bytes, start: int = 0) -> int`

Searches for the first occurrence of the byte pattern in the byte sequence.

- **Parameters**:
  - `text` (bytes): The byte sequence to search in.
  - `pattern` (bytes): The byte pattern to search for.
  - `start` (int): The index to start the search from. Defaults to 0 if not provided.
- **Returns**:
  - The starting index of the first occurrence of the pattern in the text, or `-1` if the pattern is not found.

#### `find_str(text: str, pattern: str, start: int = 0) -> int`

Searches for the first occurrence of the substring in the Unicode string.

- **Parameters**:
  - `text` (str): The Unicode string to search in.
  - `pattern` (str): The substring to search for.
  - `start` (int): The index to start the search from. Defaults to 0 if not provided.
- **Returns**:
  - The starting index of the first occurrence of the pattern in the text, or `-1` if the pattern is not found.

## License

This module is open-source and available under the MIT License.
