#include "Buffer.h"

#include <string.h>

Buffer::Buffer() : _used(false), _size(0), _buf(nullptr) {}

Buffer::Buffer(uint8_t* buf, uint16_t size) : _used(false), _size(size), _buf(buf) {}

Buffer::~Buffer() {}

uint16_t Buffer::size() const {
  return _size;
}

void Buffer::use() {
  if (_buf && _size > 0 && _used == false) _used = true;
}

bool Buffer::used() const { return _used; }

uint8_t* Buffer::buff() const { return _used ? _buf : nullptr; }

void Buffer::release(bool clear) {
  if (_used) _used = false;
  if (clear && _buf) memset(_buf, 0, _size);
}

uint8_t* Buffer::operator*() { return _used ? _buf : nullptr; }

uint8_t& Buffer::operator[](uint16_t index) {
  if (!_used || index >= _size) {
    static uint8_t dummy = 0;
    return dummy;  // Safe fallback
  }
  return _buf[index];
}

Buffer::operator uint8_t*() { return _used ? _buf : nullptr; }

Buffer::operator bool() const { return _used && _buf != nullptr; }

Buffer& Buffer::operator=(uint8_t value) {
  if (_used && _buf && _size > 0) {
    _buf[0] = value;
  }
  return *this;
}

Buffer& Buffer::operator()(uint16_t index, uint8_t value) {
  if (_used && _buf && index < _size) {
    _buf[index] = value;
  }
  return *this;
}

Buffer::operator uint8_t() const {
  if (_used && _buf && _size > 0) {
    return _buf[0];
  }
  return 0;
}
