# 🔢 Binary Barts

A C++ translation pipeline that reads a binary file and decodes it into human-readable text through a three-stage transformation: **binary → ASCII → Morse code → letters**.

## Pipeline

```
Binary file
    ↓
Binary_translator  →  char block (ASCII)
    ↓
Morse_translator   →  bars & dashes (Morse sequences)
    ↓
Morse              →  decoded letters → text output
```
## Classes
| Class | Responsibility |
|-------|---------------|
| `Binary_translator` | Reads binary file, converts bit sequences to ASCII char block |
| `Morse_translator` | Converts ASCII chars to Morse code sequences (· and −) |
| `Morse` | Decodes Morse sequences back to readable letters |

## Key Concepts
- Multi-stage data transformation pipeline
- Binary and ASCII encoding/decoding
- Morse code mapping and lookup
- File I/O and bit manipulation in C++
- Single-responsibility class design

## Build
```
bash
g++ -std=c++11 -o binary_barts *.cpp
./binary_barts <input_binary_file>
```


