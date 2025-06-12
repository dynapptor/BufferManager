#include "Block.h"

Block::Block() {}

Block::Block(uint16_t c, uint16_t s) {
  count = c;
  size = s;
}

Block::~Block() {}

void Block::set(uint16_t c, uint16_t s) {
  count = c;
  size = s;
}
