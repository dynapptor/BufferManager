#pragma once

#include <stdint.h>

/**
 * @class Block
 * @brief Represents a memory block with a count and size attribute.
 *
 * This class is used internally by BufferManager to handle memory block information.
 */
class Block {
  friend class BufferManager;

 private:
  uint16_t count;  ///< Number of elements in the block
  uint16_t size;   ///< Size of each element in bytes

 public:
  /**
   * @brief Default constructor. Initializes count and size to 0.
   */
  Block();

  /**
   * @brief Parameterized constructor.
   * @param c Number of elements
   * @param s Size of each element
   */
  Block(uint16_t c, uint16_t s);

  /**
   * @brief Destructor.
   */
  ~Block();

  /**
   * @brief Sets the block parameters.
   * @param c Number of elements
   * @param s Size of each element
   */
  void set(uint16_t c, uint16_t s);
};
