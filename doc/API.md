# BufferManager Library - API Reference

## Overview

This library provides lightweight, reusable buffer handling for embedded systems.
It includes three main classes:

- `Block`: Defines how many buffers of what size to preallocate.
- `Buffer`: Represents a memory region you can read/write to.
- `BufferManager`: Manages a pool of memory buffers and handles allocation.

---

## Class: Block

### Constructors
```cpp
Block();
Block(uint16_t count, uint16_t size);
```

### Methods
```cpp
void set(uint16_t count, uint16_t size);
```

**Description:**  
Defines a block of memory with `count` number of buffers, each `size` bytes.

---

## Class: Buffer

### Constructors
```cpp
Buffer();
Buffer(uint8_t* buf, uint16_t size);
```

### Methods
```cpp
uint16_t size() const;
void use();
bool used() const;
uint8_t* buff() const;
void release(bool clear = false);
```

### Operators
```cpp
uint8_t* operator*();
uint8_t& operator[](uint16_t index);
operator uint8_t*();
explicit operator bool() const;
Buffer& operator=(uint8_t value);
Buffer& operator()(uint16_t index, uint8_t value);
operator uint8_t() const;
```

**Description:**  
- `use()`: Marks buffer as used.
- `release(clear)`: Releases buffer, optionally clears content.
- `operator bool()`: Checks if buffer is valid.
- `operator=`, `operator[]`, etc.: Makes using the buffer intuitive like a native array.

---

## Class: BufferManager

### Constructors
```cpp
BufferManager();
~BufferManager();
```

### Methods
```cpp
bool init(const Block& item);
template <typename... Args> bool init(const Block& item, const Args&... args);
bool init(const Block* item, uint16_t count);
bool initialized();
Buffer* get(uint16_t size);
```

**Description:**  
- `init(...)`: Initializes memory pool with one or more `Block` definitions.
- `get(size)`: Returns a pointer to a `Buffer` of the requested size.
- `initialized()`: Returns whether pool was successfully initialized.

---

## Global Object

```cpp
extern BufferManager bufferManager;
```

**Description:**  
A convenient global instance so you don’t need to create one manually.

---

## Example

```cpp
#include "BufferManager.h"

void setup() {
  Serial.begin(9600);

  Block block(5, 32); // 5 buffers, each 32 bytes
  bufferManager.init(block);

  Buffer* buf = bufferManager.get(32);
  if (buf) {
    (*buf)[0] = 123;
    Serial.println((*buf)[0]);
    buf->release();
  }
}
```

---

## Notes

- No dynamic memory is used at runtime after initialization.
- Safe and deterministic for microcontroller use.
