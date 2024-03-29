#include <gtest/gtest.h>

#include "src/memory_pool.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Globals
////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr std::size_t kTestPoolSlotSize{4};
constexpr std::size_t kTestPoolNumSlots{10};
constexpr std::array<char, kTestPoolSlotSize> kClearedSlotData{};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Fixture
////////////////////////////////////////////////////////////////////////////////////////////////////

class MemoryPoolTest : public testing::Test {
 protected:
  MemoryPool<kTestPoolSlotSize, kTestPoolNumSlots> memory_pool_{};

  void SetUp() override {}
  void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

/* After initialization, all memory slots in the memory pool are available. */
TEST_F(MemoryPoolTest, AvailabilityAfterInitialization) {
  ASSERT_EQ(memory_pool_.GetNumFreeSlots(), kTestPoolNumSlots);
}

/* The memory pool will allow to reserve as many memory slots as it manages. For any additional
 * requests a nullptr is returned. */
TEST_F(MemoryPoolTest, MaximumAvailability) {
  for (std::size_t i = 0; i < kTestPoolNumSlots; i++) {
    void *slot = memory_pool_.GetSlot(false);
    ASSERT_NE(slot, nullptr);
  }
  void *slot = memory_pool_.GetSlot(false);
  ASSERT_EQ(slot, nullptr);
}

/* When a previously reserved memory slot is released, its memory becomes available again. */
TEST_F(MemoryPoolTest, AvailableAfterRelease) {
  void *slot = memory_pool_.GetSlot(false);
  memory_pool_.FreeSlot(slot);
  ASSERT_EQ(memory_pool_.GetNumFreeSlots(), kTestPoolNumSlots);
}

/* Trying to free an unknown memory slot, i.e. where the given pointer doesn't correspond to any
 * memory slot managed by the memory pool, the number of available memory slots does not change. */
TEST_F(MemoryPoolTest, ReleaseUnknownSlot) {
  std::size_t const kLocalSlotSize{10};
  std::array<char, kLocalSlotSize> local_slot{};
  memory_pool_.FreeSlot(local_slot.data());
  ASSERT_EQ(memory_pool_.GetNumFreeSlots(), kTestPoolNumSlots);
}

/* Requesting a cleared memory slot will cause it to be set to zero. */
TEST_F(MemoryPoolTest, RequestCleared) {
  // ensure all memory slots have some non-zero data written to them
  std::array<void *, kTestPoolNumSlots> all_memory_slots{};
  for (std::size_t i = 0; i < kTestPoolNumSlots; i++) {
    all_memory_slots.at(i) = memory_pool_.GetSlot(false);
    std::memset(all_memory_slots.at(i), 1, kTestPoolSlotSize);
  }
  // no more slots are available
  void *slot = memory_pool_.GetSlot(false);
  ASSERT_EQ(slot, nullptr);
  // free all slots
  for (void *slot : all_memory_slots) {
    memory_pool_.FreeSlot(slot);
  }
  ASSERT_EQ(memory_pool_.GetNumFreeSlots(), kTestPoolNumSlots);
  // request a cleared slot
  slot = memory_pool_.GetSlot(true);
  // the whole slot shall be zeroed
  ASSERT_EQ(std::memcmp(kClearedSlotData.data(), slot, kTestPoolSlotSize), 0);
}
