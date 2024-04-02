#include "include/allocator.hpp"
#include "src/memory_pool.hpp"

namespace {

// SMALL memory pool
constexpr std::uint32_t kSizeSlotsSmall{1024};
constexpr std::uint32_t kNumSlotsSmall{1000};
MemoryPool<kSizeSlotsSmall, kNumSlotsSmall> mem_pool_small;

// MEDIUM memory pool
constexpr std::uint32_t kSizeSlotsMedium{8192};
constexpr std::uint32_t kNumSlotsMedium{1000};
MemoryPool<kSizeSlotsMedium, kNumSlotsMedium> mem_pool_medium;

// LARGE memory pool
constexpr std::uint32_t kSizeSlotsLarge{65536};
constexpr std::uint32_t kNumSlotsLarge{1000};
MemoryPool<kSizeSlotsLarge, kNumSlotsLarge> mem_pool_large;

static_assert(kSizeSlotsSmall < kSizeSlotsMedium && kSizeSlotsMedium < kSizeSlotsLarge,
              "The small/medium/large memory pool slot sizes are invalid.");

IMemoryPoolList list_large{static_cast<IMemoryPool *>(&mem_pool_large), nullptr};
IMemoryPoolList list_medium{static_cast<IMemoryPool *>(&mem_pool_medium), &list_large};
IMemoryPoolList list_small{static_cast<IMemoryPool *>(&mem_pool_small), &list_medium};

}  // namespace

IMemoryPoolList *em::Allocator::memory_pool_list_{&list_small};  // NOLINT (see declaration)
