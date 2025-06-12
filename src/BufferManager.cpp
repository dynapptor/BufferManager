#include "BufferManager.h"

#include <Arduino.h>
#include <string.h>

BufferManager::BufferManager() {}

BufferManager::~BufferManager() {
  if (_pool) delete[] _pool;
  if (_buffers) delete[] _buffers;
}

bool BufferManager::initPool(const Block& item, uint16_t& offset, uint16_t& index) {
  for (uint16_t i = 0; i < item.count; i++) {
    _buffers[index] = Buffer(_pool + offset, item.size);
    offset += item.size;
    index++;
  }
  _initialized = true;
  return true;
}

bool BufferManager::init(const Block& item) {
  if (_initialized) return false;
  if (item.count == 0 || item.size == 0) return false;
  _bufferCount = item.count;
  _totalSize = item.count * item.size;
  _pool = new uint8_t[_totalSize];
  if (!_pool) return false;
  _buffers = new Buffer[_bufferCount];
  if (!_buffers) {
    delete[] _pool;
    _pool = nullptr;
    return false;
  }
  uint16_t offset = 0;
  uint16_t index = 0;
  return initPool(item, offset, index);
}

bool BufferManager::init(const Block* item, uint16_t count) {
  if (_initialized) return false;
  _bufferCount = 0;
  _totalSize = 0;
  for (uint16_t i = 0; i < count; i++) {
    if (item[i].count == 0 || item[i].size == 0) return false;
    _bufferCount += item[i].count;
    _totalSize += item[i].count * item[i].size;
  }
  _pool = new uint8_t[_totalSize];
  if (!_pool) return false;
  _buffers = new Buffer[_bufferCount];
  if (!_buffers) {
    delete[] _pool;  // Szabadítsd fel a _pool-t
    _pool = nullptr;
    return false;
  }
  uint16_t offset = 0;
  uint16_t index = 0;
  for (uint16_t i = 0; i < count; i++) {
    for (uint16_t j = 0; j < item[i].count; j++) {
      _buffers[index] = Buffer(_pool + offset, item[i].size);
      offset += item[i].size;
      index++;
    }
  }
  _initialized = true;
  return true;
}

Buffer* BufferManager::get(uint16_t size) {
  for (uint16_t i = 0; i < _bufferCount; i++) {
    if (!_buffers[i]._used && _buffers[i]._size >= size) {
      _buffers[i]._used = true;
      return &_buffers[i];
    }
  }
  return nullptr;
}

bool BufferManager::calculateTotalCount(uint16_t& count, const Block& item) {
  if (item.count == 0) return false;
  count += item.count;
  return true;
}

bool BufferManager::calculateTotalSize(uint32_t& size, const Block& item) {
  if (item.count == 0 || item.size == 0) return false;
  size += item.count * item.size;
  return true;
}

bool BufferManager::initialized() { return _initialized; }

BufferManager bufferManager;