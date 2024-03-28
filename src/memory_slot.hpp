#ifndef SRC_MEMORY_SLOT_HPP_
#define SRC_MEMORY_SLOT_HPP_

#include <cstddef>
#include <cstring>

template <std::size_t SIZE>
struct MemorySlot {
  bool is_reserved{false};
  char data[SIZE]{};
};

#endif  // SRC_MEMORY_SLOT_HPP_
