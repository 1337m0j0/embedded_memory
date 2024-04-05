#include "include/allocator.hpp"

#include <cstddef>

#include "src/memory_pool_interfaces.hpp"

void *em::Allocator::Alloc(const std::size_t requested_size, const bool clear_region) noexcept {
  void *res{nullptr};
  for (IMemoryPoolList *list = em::Allocator::memory_pool_list_; list != nullptr;
       list = list->next) {
    IMemoryPool *const memory_pool = list->current;
    if (memory_pool != nullptr && requested_size <= memory_pool->GetSizeBlocks()) {
      res = memory_pool->GetBlock(clear_region);
      if (nullptr != res) {
        return res;
      }
    }
  }
  return nullptr;
}

void em::Allocator::Free(void *ptr) noexcept {
  for (IMemoryPoolList *list = em::Allocator::memory_pool_list_; list != nullptr;
       list = list->next) {
    IMemoryPool *const memory_pool = list->current;
    if (memory_pool->PointerBelongsToMemoryPool(ptr)) {
      memory_pool->FreeBlock(ptr);
    }
  }
}
