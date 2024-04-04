#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstring>

#include "src/memory_pool.hpp"
#include "src/memory_pool_interfaces.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Globals
////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr std::size_t kTestPoolBlockSize{8};
constexpr std::size_t kTestPoolNumBlocks{10};
constexpr std::array<char, kTestPoolBlockSize> kClearedBlockData{};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Fixture
////////////////////////////////////////////////////////////////////////////////////////////////////

class MemoryPoolTest : public testing::Test {
 protected:
  MemoryPool<kTestPoolBlockSize, kTestPoolNumBlocks> memory_pool_instance_{};
  IMemoryPool &memory_pool_ = memory_pool_instance_;

  void SetUp() override {}
  void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Definitions
////////////////////////////////////////////////////////////////////////////////////////////////////

/* After initialization, all memory Blocks in the memory pool are available. */
TEST_F(MemoryPoolTest, AvailabilityAfterInitialization) {
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
}

/* GetSizeBlocks returns the size of memory Blocks managed by the memory pool. */
TEST_F(MemoryPoolTest, GetBlockSize) {
  ASSERT_EQ(memory_pool_.GetSizeBlocks(), kTestPoolBlockSize);
}

/* The memory pool will allow to reserve as many memory Blocks as it manages. For any additional
 * requests a nullptr is returned. */
TEST_F(MemoryPoolTest, MaximumAvailability) {
  for (std::size_t i = 0; i < kTestPoolNumBlocks; i++) {
    void *block = memory_pool_.GetBlock(false);
    ASSERT_NE(block, nullptr);
  }
  void *block = memory_pool_.GetBlock(false);
  ASSERT_EQ(block, nullptr);
}

/* When a previously reserved memory Block is released, its memory becomes available again. */
TEST_F(MemoryPoolTest, AvailableAfterRelease) {
  void *block = memory_pool_.GetBlock(false);
  memory_pool_.FreeBlock(block);
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
}

/* Trying to free an unknown memory block, i.e. where the given pointer doesn't correspond to any
 * memory block managed by the memory pool, the number of available memory blocks does not change.
 */
TEST_F(MemoryPoolTest, ReleaseUnknownBlock) {
  std::size_t const kLocalBlockSize{10};
  std::array<char, kLocalBlockSize> local_block{};
  memory_pool_.FreeBlock(local_block.data());
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
}

/* Requesting a cleared memory Block will cause it to be set to zero. */
TEST_F(MemoryPoolTest, RequestCleared) {
  // ensure all memory blocks have some non-zero data written to them
  std::array<void *, kTestPoolNumBlocks> all_memory_blocks{};
  for (std::size_t i = 0; i < kTestPoolNumBlocks; i++) {
    all_memory_blocks.at(i) = memory_pool_.GetBlock(false);
    std::memset(all_memory_blocks.at(i), 1, kTestPoolBlockSize);
  }

  // no more blocks are available
  void *block = memory_pool_.GetBlock(false);
  ASSERT_EQ(block, nullptr);
  // free all blocks
  for (void *block : all_memory_blocks) {
    memory_pool_.FreeBlock(block);
  }
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
  // request a cleared block
  block = memory_pool_.GetBlock(true);
  // the whole block shall be zeroed
  ASSERT_EQ(std::memcmp(kClearedBlockData.data(), block, kTestPoolBlockSize), 0);
}

/* Returned memory can be written to. */
TEST_F(MemoryPoolTest, WriteToMemory) {
  // expected data
  std::array<char, kTestPoolBlockSize> expected_data{};
  std::memset(expected_data.data(), 1, kTestPoolBlockSize);
  // write test data and check
  void *block = memory_pool_.GetBlock(true);
  std::memset(block, 1, kTestPoolBlockSize);
  ASSERT_EQ(std::memcmp(expected_data.data(), block, kTestPoolBlockSize), 0);
}

// A freshly-initialized memory pool shall not have buffer overflows.
TEST_F(MemoryPoolTest, NoBufferOverflowOnInitialization) {
  ASSERT_FALSE(memory_pool_.HasBufferOverflow());
}

// If a buffer overflow happens, it should be detected.
TEST_F(MemoryPoolTest, BufferOverflowDetection) {
  void *block = memory_pool_.GetBlock(true);
  std::memset(block, 1, kTestPoolBlockSize + 1);
  ASSERT_TRUE(memory_pool_.HasBufferOverflow());
}
