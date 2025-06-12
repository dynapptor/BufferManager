#pragma once
#include <stdint.h>

#include "Block.h"
#include "Buffer.h"

/**
 * @class BufferManager
 * @brief Manages memory pools of buffers based on predefined block sizes.
 *
 * Allows allocation and reuse of memory blocks, improving performance and reducing fragmentation.
 */
class BufferManager {
 private:
  uint16_t _bufferCount = 0;   ///< Total number of buffers
  uint32_t _totalSize = 0;     ///< Total memory size allocated
  uint8_t* _pool = nullptr;    ///< Pointer to memory pool
  Buffer* _buffers = nullptr;  ///< Array of buffer objects
  bool _initialized = false;   ///< Initialization status

  // --- Internal helper functions ---

  /**
   * @brief Initializes a pool segment for a given block.
   */
  bool initPool(const Block& item, uint16_t& offset, uint16_t& index);

  /**
   * @brief Recursively initializes pools for multiple blocks.
   */
  template <typename... Args>
  bool initPool(uint16_t& offset, uint16_t& index, const Block& item, const Args&... args);

  inline bool initPool(uint16_t& offset, uint16_t& index) { return true; }

  bool calculateTotalCount(uint16_t& count, const Block& item);

  template <typename... Args>
  bool calculateTotalCount(uint16_t& count, const Block& item, const Args&... args);

  bool calculateTotalSize(uint32_t& size, const Block& item);

  template <typename... Args>
  bool calculateTotalSize(uint32_t& size, const Block& item, const Args&... args);

 public:
  /**
   * @brief Constructor.
   */
  BufferManager();

  /**
   * @brief Destructor. Frees all allocated memory.
   */
  ~BufferManager();

  /**
   * @brief Initializes the buffer manager with a single block definition.
   * @param item Block configuration
   * @return true if successful
   */
  bool init(const Block& item);

  /**
   * @brief Initializes with multiple block definitions.
   */
  template <typename... Args>
  bool init(const Block& item, const Args&... args);

  /**
   * @brief Initializes from an array of blocks.
   * @param item Array of blocks
   * @param count Number of items
   */
  bool init(const Block* item, uint16_t count);

  /**
   * @brief Checks whether the buffer manager is initialized.
   * @return true if initialized
   */
  bool initialized();

  /**
   * @brief Retrieves a buffer of the requested size.
   * @param size Desired buffer size
   * @return Pointer to buffer or nullptr if unavailable
   */
  Buffer* get(uint16_t size);
};

#include "BufferManager.tpp"

/// Global buffer manager instance
extern BufferManager bufferManager;
