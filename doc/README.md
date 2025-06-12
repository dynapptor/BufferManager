# BufferManager Library

A lightweight buffer pooling library designed for embedded systems such as Arduino.

## Features

- Preallocated memory blocks for deterministic usage
- Reusable buffers with state tracking
- Zero dynamic memory allocation during runtime
- Simple and intuitive API
- Suitable for microcontrollers with limited RAM

## File Structure

| File | Description |
|------|-------------|
| `Block.h/cpp` | Defines a memory block structure with size and count |
| `Buffer.h/cpp` | Encapsulates a raw buffer with safe access operators |
| `BufferManager.h/cpp/tpp` | Manages a pool of buffers with multiple block configurations |
| `keywords.txt` | Arduino IDE keyword highlighting |
| `examples/` | Example sketches showing how to use the library |

## Quick Start

```cpp
#include "BufferManager.h"

Block block(10, 32); // 10 buffers of 32 bytes
bufferManager.init(block);

Buffer* buf = bufferManager.get(32);
if (buf) {
  (*buf)[0] = 99;
  buf->release();
}
```

## Installation

1. Download or clone the repository
2. Copy it to your Arduino `libraries` folder
3. Open Arduino IDE and explore the examples

## License

This library is released under the MIT License.
