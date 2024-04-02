#include <cstdint>

#include "include/allocator.hpp"
#include "src/memory_pool.hpp"

/** This file shall contain only the definition of em::Allocator::memory_pool_list_
 *  and the associated private resources. Different versions of this file can be
 *  maintained for various deployment scenarios. A selection of one of these files
 *  by the corresponding build target shall be used to configure the allocator.
 *
 * Note on the NOLINT hints in this file: The corresponding lines define resources
 * that are not const but have protected visibility. They are intended to be used only
 * by the public functions of the Allocator class.
 */

namespace {

// SMALL memory pool
constexpr std::uint32_t kSizeSlotsSmall{1024};
constexpr std::uint32_t kNumSlotsSmall{1000};
MemoryPool<kSizeSlotsSmall, kNumSlotsSmall> mem_pool_small;  // NOLINT

// MEDIUM memory pool
constexpr std::uint32_t kSizeSlotsMedium{8192};
constexpr std::uint32_t kNumSlotsMedium{1000};
MemoryPool<kSizeSlotsMedium, kNumSlotsMedium> mem_pool_medium;  // NOLINT

// LARGE memory pool
constexpr std::uint32_t kSizeSlotsLarge{65536};
constexpr std::uint32_t kNumSlotsLarge{1000};
MemoryPool<kSizeSlotsLarge, kNumSlotsLarge> mem_pool_large;  // NOLINT

static_assert(kSizeSlotsSmall < kSizeSlotsMedium && kSizeSlotsMedium < kSizeSlotsLarge,
              "The small/medium/large memory pool slot sizes are invalid.");

IMemoryPoolList list_large{static_cast<IMemoryPool *>(&mem_pool_large), nullptr};        // NOLINT
IMemoryPoolList list_medium{static_cast<IMemoryPool *>(&mem_pool_medium), &list_large};  // NOLINT
IMemoryPoolList list_small{static_cast<IMemoryPool *>(&mem_pool_small), &list_medium};   // NOLINT

}  // namespace

IMemoryPoolList *em::Allocator::memory_pool_list_{&list_small};  // NOLINT
