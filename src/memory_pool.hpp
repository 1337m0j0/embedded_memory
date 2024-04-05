#ifndef SRC_MEMORY_POOL_HPP_
#define SRC_MEMORY_POOL_HPP_

#include <array>
#include <cstddef>
#include <cstdint>

#include "src/memory_pool_interfaces.hpp"

/// @brief A MemoryPool manages a fixed number of memory blocks of immutable equal size.
template <std::size_t SIZE_BLOCKS, std::size_t NUM_BLOCKS>
class MemoryPool : public IMemoryPool {
 public:
  /// @brief Searches and returns a free block.
  void *GetBlock(bool clear_memory) override {
    Initialize();
    // proceeding with allocation
    void *result{nullptr};
    if (free_blocks_ != nullptr) {
      // get and clear result pointer
      result = static_cast<void *>(free_blocks_->data.data());
      if (clear_memory) {
        std::memset(result, 0, SIZE_BLOCKS);
      }
      // relink free list
      auto new_head_free = free_blocks_->next;
      if (new_head_free != nullptr) {
        new_head_free->previous = nullptr;
      }
      // relink reserved list
      auto new_head_reserved = free_blocks_;
      new_head_reserved->next = reserved_blocks_;
      if (reserved_blocks_ != nullptr) {
        reserved_blocks_->previous = new_head_reserved;
      }
      // update list heads
      free_blocks_ = new_head_free;
      reserved_blocks_ = new_head_reserved;
    }
    return result;
  };

  /// @brief Releases the memory block under the given pointer.
  void FreeBlock(void *ptr) override {
    if (!PointerBelongsToMemoryPool(ptr)) {
      return;
    }
    Initialize();
    for (auto current_block = reserved_blocks_; current_block != nullptr;
         current_block = current_block->next) {
      if (static_cast<void *>(current_block->data.data()) == ptr) {
        // remove from reserved list
        auto reserved_prev = current_block->previous;
        auto reserved_next = current_block->next;
        if (reserved_prev != nullptr) {
          reserved_prev->next = reserved_next;
        }
        if (reserved_next != nullptr) {
          reserved_next->previous = reserved_prev;
        }
        if (current_block == reserved_blocks_) {
          reserved_blocks_ = reserved_next;
        }
        // add to free list
        current_block->next = free_blocks_;
        if (free_blocks_ != nullptr) {
          free_blocks_->previous = current_block;
        }
        free_blocks_ = current_block;
        // done
        break;
      }
    }
  }

  /// @brief Returns the amount of free memory blocks.
  std::size_t GetNumFreeBlocks() override {
    Initialize();
    std::size_t num_free_blocks{0};
    auto current_block = free_blocks_;
    while (current_block != nullptr) {
      num_free_blocks++;
      current_block = current_block->next;
    }
    return num_free_blocks;
  }

  /// @brief Returns the block size available in this pool.
  std::size_t GetSizeBlocks() const override { return SIZE_BLOCKS; }

  /// @brief Detects whether a buffer overflow has occurred in any memory block.
  bool HasBufferOverflow() const override {
    for (auto const &block : memory_blocks_) {
      if (block.guard_bytes != 0) {
        return true;
      }
    }
    return false;
  }

  /// @brief Tells whether pointer is within the managed range.
  bool PointerBelongsToMemoryPool(void *ptr) override {
    return ptr >= static_cast<void *>(memory_blocks_.at(0).data.data()) &&
           ptr <= static_cast<void *>(memory_blocks_.at(NUM_BLOCKS - 1).data.data());
  }

 private:
  // Represents individual memory blocks. Can be managed in linked lists.
  template <std::size_t SIZE>
  struct MemoryBlock {
    MemoryBlock<SIZE> *previous{nullptr};
    MemoryBlock<SIZE> *next{nullptr};
    std::array<char, SIZE> data{};
    std::uint64_t guard_bytes{};
  };

  // Flag to ensure initialization of the allocator.
  bool is_initialized_{false};

  // List of available memory blocks.
  MemoryBlock<SIZE_BLOCKS> *free_blocks_{nullptr};

  // List of reserved memory blocks.
  MemoryBlock<SIZE_BLOCKS> *reserved_blocks_{nullptr};

  // This array holds the data blocks managed by this memory pool.
  std::array<MemoryBlock<SIZE_BLOCKS>, NUM_BLOCKS> memory_blocks_{};

  // Initializes the allocator if not done already. This is to avoid potentially-throwing code
  // during static initialization of a MemoryPool object.
  void Initialize() {
    if (!is_initialized_) {
      for (std::size_t i = 0; i < memory_blocks_.size() - 1; i++) {
        auto block_current = &memory_blocks_.at(i);
        auto block_next = &memory_blocks_.at(i + 1);
        block_current->next = block_next;
        block_next->previous = block_current;
      }
      free_blocks_ = &memory_blocks_.at(0);
      is_initialized_ = true;
    }
  }
};

#endif  // SRC_MEMORY_POOL_HPP_
