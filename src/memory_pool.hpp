#ifndef SRC_MEMORY_POOL_HPP_
#define SRC_MEMORY_POOL_HPP_

#include <array>
#include <cstddef>
#include <cstring>

#include "src/memory_slot.hpp"

/** @brief MemoryPool profiling data container. */
struct MemoryPoolProfilingData {
  std::uint64_t num_get_slot_total{0};
  std::uint64_t num_get_slot_successful{0};
  std::uint64_t num_free_total{0};
  std::uint64_t num_free_unknown_pointer{0};
};

template <std::size_t SIZE_SLOTS, std::size_t NUM_SLOTS>
class MemoryPool {
 public:
  /** @brief Searches and returns a free slot. */
  void *GetSlot(bool clear_memory) {
    profiling_data_.num_get_slot_total++;
    for (auto &slot : memory_slots_) {
      if (!slot.is_reserved) {
        profiling_data_.num_get_slot_successful++;
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
    profiling_data_.num_free_total++;
    for (auto &slot : memory_slots_) {
      if (ptr == slot.data.data()) {
        slot.is_reserved = false;
        return;
      }
    }
    profiling_data_.num_free_unknown_pointer++;
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

  /** @brief Gets the profiling data. */
  struct MemoryPoolProfilingData GetProfilingData() { return profiling_data_; }

  /** @brief Resets the profiling data. */
  void ResetProfiling() {
    profiling_data_.num_get_slot_total = 0;
    profiling_data_.num_get_slot_successful = 0;
    profiling_data_.num_free_total = 0;
    profiling_data_.num_free_unknown_pointer = 0;
  }

 private:
  /** @brief This array holds the data slots managed by this memory pool. */
  std::array<MemorySlot<SIZE_SLOTS>, NUM_SLOTS> memory_slots_{};

  /** @brief Profiling counters */
  struct MemoryPoolProfilingData profiling_data_ {};
};

#endif  // SRC_MEMORY_POOL_HPP_
