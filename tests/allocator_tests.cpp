#include <gtest/gtest.h>

#include <cstddef>

#include "include/allocator.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Globals
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Fixture
////////////////////////////////////////////////////////////////////////////////////////////////////

class AllocatorTest : public testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

// The allocator shall return a pointer to the available memory region for an allocation request
// that can be met.
TEST_F(AllocatorTest, AllocationTest) {
  const std::size_t requested_size{512};
  void* result = em::Allocator::Alloc(requested_size, false);
  ASSERT_NE(result, nullptr);
}

// The allocator shall free the allocated space when so instructed.
TEST_F(AllocatorTest, FreeTest) {
  constexpr std::uint32_t kNumSlotsLarge{1000};
  constexpr std::uint32_t kSizeSlotsLarge{65536};
  void* last_valid_pointer{nullptr};
  // reserve all blocks of the largest pool
  for (std::uint32_t i = 0; i < kNumSlotsLarge; i++) {
    last_valid_pointer = em::Allocator::Alloc(kSizeSlotsLarge, false);
  }
  // one further request must return a null pointer
  void* additional_request = em::Allocator::Alloc(kSizeSlotsLarge, false);
  ASSERT_EQ(additional_request, nullptr);
  // free the last returned pointer
  em::Allocator::Free(last_valid_pointer);
  // one more allocation request shall return the freed pointer
  additional_request = em::Allocator::Alloc(kSizeSlotsLarge, false);
  ASSERT_EQ(last_valid_pointer, additional_request);
}
