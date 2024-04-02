#ifndef SRC_MEMORY_POOL_HPP_
#define SRC_MEMORY_POOL_HPP_

#include <array>
#include <cstddef>
#include <cstring>

#include "src/memory_slot.hpp"

/** @brief General interface to interact with MemoryPool objects. */
class IMemoryPool {
 public:
  // interface functions
  virtual void *GetSlot(bool clear_memory) = 0;
  virtual void FreeSlot(void *ptr) = 0;
  virtual std::size_t GetNumFreeSlots() = 0;
  virtual std::size_t GetSizeSlots() const = 0;
  // constructors and destructors
  virtual ~IMemoryPool() = default;
};

/** @brief Linked-list to manage lists of memory pools. */
struct IMemoryPoolList {
  IMemoryPool *current{nullptr};
  IMemoryPoolList *next{nullptr};
};

/** @brief A MemoryPool manages a fixed number of memory slots of immutable equal size. */
template <std::size_t SIZE_SLOTS, std::size_t NUM_SLOTS>
class MemoryPool : public IMemoryPool {
 public:
  /** @brief Searches and returns a free slot. */
  void *GetSlot(bool clear_memory) override {
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
  void FreeSlot(void *ptr) override {
    for (auto &slot : memory_slots_) {
      if (ptr == slot.data.data()) {
        slot.is_reserved = false;
        return;
      }
    }
  }

  /** @brief Returns the amount of free memory slots. */
  std::size_t GetNumFreeSlots() override {
    std::size_t num_free_slots{0};
    for (auto const &slot : memory_slots_) {
      if (!slot.is_reserved) {
        num_free_slots++;
      }
    }
    return num_free_slots;
  }

  std::size_t GetSizeSlots() const override { return SIZE_SLOTS; }

 private:
  /** @brief This array holds the data slots managed by this memory pool. */
  std::array<MemorySlot<SIZE_SLOTS>, NUM_SLOTS> memory_slots_{};
};

#endif  // SRC_MEMORY_POOL_HPP_
