#ifndef SRC_MEMORY_POOL_HPP_
#define SRC_MEMORY_POOL_HPP_

#include <array>
#include <cstddef>

#include "src/memory_slot.hpp"

template <std::size_t SIZE_SLOTS, std::size_t NUM_SLOTS>
class MemoryPool {
 public:
  void *get_free_slot(bool clear_memory) {
    for (auto const &slot : data_) {
      if (!slot.is_reserved) {
        slot.is_reserved = true;
        if (clear_memory) {
          std::memset(&slot.data, 0, SIZE_SLOTS);
        }
        return static_cast<void *>(&slot);
      }
    }
    return nullptr;
  };

 private:
  std::array<MemorySlot<SIZE_SLOTS>, NUM_SLOTS> data_{};
};

#endif  // SRC_MEMORY_POOL_HPP_
