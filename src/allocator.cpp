#include "include/em.hpp"
#include "src/allocator_config.hpp"
#include "src/memory_pool.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Pools
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {

MemoryPool<em::config::kSizeSlotsSmall, em::config::kNumSlotsSmall> mem_pool_small;
MemoryPool<em::config::kSizeSlotsMedium, em::config::kNumSlotsMedium> mem_pool_medium;
MemoryPool<em::config::kSizeSlotsLarge, em::config::kNumSlotsLarge> mem_pool_large;

}  // namespace

////////////////////////////////////////////////////////////////////////////////////////////////////
// Allocation and Deallocation Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void *em::alloc(const std::size_t size, const bool clear_region) {
  void *res{nullptr};

  if (size <= em::config::kSizeSlotsSmall) {
    res = mem_pool_small.get_free_slot(clear_region);
    if (nullptr != res) {
      return res;
    }
  }

  if (size <= em::config::kSizeSlotsMedium) {
    res = mem_pool_medium.get_free_slot(clear_region);
    if (nullptr != res) {
      return res;
    }
  }

  if (size <= em::config::kSizeSlotsLarge) {
    res = mem_pool_large.get_free_slot(clear_region);
    if (nullptr != res) {
      return res;
    }
  }

  return nullptr;
}

void em::free(void *ptr) {}
