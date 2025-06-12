#pragma once

#include "BufferManager.h"

template <typename... Args>
bool BufferManager::initPool(uint16_t& offset, uint16_t& index, const Block& item, const Args&... args) {
  if (!initPool(item, offset, index)) return false;
  if (!initPool(offset, index, args...)) return false;
  return true;
}

template <typename... Args>
bool BufferManager::init(const Block& item, const Args&... args) {
  if (_initialized) return false;
  if (!calculateTotalCount(_bufferCount, item, args...)) return false;
  if (!calculateTotalSize(_totalSize, item, args...)) return false;
  _pool = new uint8_t[_totalSize]{};
  if (!_pool) return false;
  _buffers = new Buffer[_bufferCount]{};
  if (!_buffers) {
    delete[] _pool;
    _pool = nullptr;
    return false;
  }
  uint16_t offset = 0;
  uint16_t index = 0;
  return initPool(offset, index, item, args...);
}

template <typename... Args>
bool BufferManager::calculateTotalCount(uint16_t& count, const Block& item, const Args&... args) {
  if (item.count == 0) return false;
  count += item.count;
  return calculateTotalCount(count, args...);
}

template <typename... Args>
bool BufferManager::calculateTotalSize(uint32_t& size, const Block& item, const Args&... args) {
  if (item.count == 0 || item.size == 0) return false;
  size += item.count * item.size;
  return calculateTotalSize(size, args...);
}