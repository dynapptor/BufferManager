#pragma once
#include <stdint.h>

/**
 * @class Buffer
 * @brief Represents a memory buffer with utility operations and state tracking.
 *
 * Used for managing and manipulating raw byte buffers in a safe and convenient manner.
 */
class Buffer {
  friend class BufferManager;

 private:
  bool _used = false;  ///< Indicates whether the buffer is currently in use
  uint16_t _size;      ///< Size of the buffer in bytes
  uint8_t* _buf;       ///< Pointer to the actual buffer data

 public:
  /**
   * @brief Default constructor. Initializes an empty buffer.
   */
  Buffer();

  /**
   * @brief Parameterized constructor.
   * @param buf Pointer to preallocated buffer
   * @param size Size of the buffer
   */
  Buffer(uint8_t* buf, uint16_t size);

  /**
   * @brief Destructor. Frees resources if needed.
   */
  ~Buffer();

  /**
   * @brief Returns the size of the buffer.
   * @return Size in bytes
   */
  uint16_t size() const;

  /**
   * @brief Marks the buffer as used.
   */
  void use();

  /**
   * @brief Checks if the buffer is in use.
   * @return true if used, false otherwise
   */
  bool used() const;

  /**
   * @brief Returns the raw buffer pointer.
   * @return Pointer to buffer data
   */
  uint8_t* buff() const;

  /**
   * @brief Releases the buffer.
   * @param clear If true, clears the buffer contents
   */
  void release(bool clear = false);

  /**
   * @brief Dereference operator. Access raw pointer.
   */
  uint8_t* operator*();

  /**
   * @brief Index operator. Access element by index with bounds check.
   * @param index Index to access
   * @return Reference to the element at index
   */
  uint8_t& operator[](uint16_t index);

  /**
   * @brief Implicit conversion to uint8_t*.
   */
  operator uint8_t*();

  /**
   * @brief Boolean operator. Checks if the buffer is valid.
   */
  explicit operator bool() const;

  /**
   * @brief Assigns a value to all elements in the buffer.
   * @param value Value to assign
   * @return Reference to this buffer
   */
  Buffer& operator=(uint8_t value);

  /**
   * @brief Sets a specific byte in the buffer.
   * @param index Index of the byte
   * @param value Value to set
   * @return Reference to this buffer
   */
  Buffer& operator()(uint16_t index, uint8_t value);

  /**
   * @brief Converts to uint8_t by returning the first byte.
   * @return First byte of the buffer
   */
  operator uint8_t() const;
};
