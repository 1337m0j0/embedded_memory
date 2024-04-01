#ifndef SRC_MEMORY_SLOT_HPP_
#define SRC_MEMORY_SLOT_HPP_

#include <array>
#include <cstddef>

template <std::size_t SIZE>
struct MemorySlot {
  /** @brief Tells whether this memory slot is currently in use. */
  bool is_reserved{false};

  /** @brief This is the actual memory that can be allocated and used. */
  std::array<char, SIZE> data{};
};

#endif  // SRC_MEMORY_SLOT_HPP_
