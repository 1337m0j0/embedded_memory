#ifndef SRC_MEMORY_POOL_HPP_
#define SRC_MEMORY_POOL_HPP_

#include <array>
#include <cstddef>
#include <cstring>

#include "src/memory_slot.hpp"

template <std::size_t SIZE_SLOTS, std::size_t NUM_SLOTS>
class MemoryPool {
 public:
  /** @brief Searches and returns a free slot. */
  void *GetSlot(bool clear_memory) {
    for (auto &slot : memory_slots_) {
      if (!slot.is_reserved) {
        slot.is_reserved = true;
        if (clear_memory) {
          std::memset(slot.data.data(), 0, SIZE_SLOTS);
        }
        return static_cast<void *>(slot.data.data());
      }
    }
    return nullptr;
  };

  /** @brief Releases the memory slot under the given pointer. */
  void FreeSlot(void *ptr) {
    for (auto &slot : memory_slots_) {
      if (ptr == slot.data.data()) {
        slot.is_reserved = false;
        break;
      }
    }
  }

  /** @brief Returns the amount of free memory slots. */
  std::size_t GetNumFreeSlots() {
    std::size_t num_free_slots{0};
    for (auto const &slot : memory_slots_) {
      if (!slot.is_reserved) {
        num_free_slots++;
      }
    }
    return num_free_slots;
  }

 private:
  std::array<MemorySlot<SIZE_SLOTS>, NUM_SLOTS> memory_slots_{};
};

#endif  // SRC_MEMORY_POOL_HPP_
