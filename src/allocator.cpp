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

const std::array<IMemoryPool *, 3> memory_pools{
    &mem_pool_small,
    &mem_pool_medium,
    &mem_pool_large,
};

}  // namespace

////////////////////////////////////////////////////////////////////////////////////////////////////
// Allocation and Deallocation Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void *em::alloc(const std::size_t size, const bool clear_region) {
  void *res{nullptr};
  for (auto const &memory_pool : memory_pools) {
    if (size <= memory_pool->GetSizeSlots()) {
      res = memory_pool->GetSlot(clear_region);
      if (nullptr != res) {
        return res;
      }
    }
  }
  return nullptr;
}
