#ifndef SRC_MEMORY_POOL_INTERFACES_HPP_
#define SRC_MEMORY_POOL_INTERFACES_HPP_

#include <cstddef>

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

#endif  // SRC_MEMORY_POOL_INTERFACES_HPP_
