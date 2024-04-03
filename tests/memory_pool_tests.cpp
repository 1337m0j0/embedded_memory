#include <gtest/gtest.h>

#include "src/memory_pool.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Test Globals
////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr std::size_t kTestPoolBlockSize{4};
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
    void *Block = memory_pool_.GetBlock(false);
    ASSERT_NE(Block, nullptr);
  }
  void *Block = memory_pool_.GetBlock(false);
  ASSERT_EQ(Block, nullptr);
}

/* When a previously reserved memory Block is released, its memory becomes available again. */
TEST_F(MemoryPoolTest, AvailableAfterRelease) {
  void *Block = memory_pool_.GetBlock(false);
  memory_pool_.FreeBlock(Block);
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
}

/* Trying to free an unknown memory Block, i.e. where the given pointer doesn't correspond to any
 * memory Block managed by the memory pool, the number of available memory Blocks does not change.
 */
TEST_F(MemoryPoolTest, ReleaseUnknownBlock) {
  std::size_t const kLocalBlockSize{10};
  std::array<char, kLocalBlockSize> local_Block{};
  memory_pool_.FreeBlock(local_Block.data());
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
}

/* Requesting a cleared memory Block will cause it to be set to zero. */
TEST_F(MemoryPoolTest, RequestCleared) {
  // ensure all memory Blocks have some non-zero data written to them
  std::array<void *, kTestPoolNumBlocks> all_memory_Blocks{};
  for (std::size_t i = 0; i < kTestPoolNumBlocks; i++) {
    all_memory_Blocks.at(i) = memory_pool_.GetBlock(false);
    std::memset(all_memory_Blocks.at(i), 1, kTestPoolBlockSize);
  }

  // no more Blocks are available
  void *Block = memory_pool_.GetBlock(false);
  ASSERT_EQ(Block, nullptr);
  // free all Blocks
  for (void *Block : all_memory_Blocks) {
    memory_pool_.FreeBlock(Block);
  }
  ASSERT_EQ(memory_pool_.GetNumFreeBlocks(), kTestPoolNumBlocks);
  // request a cleared Block
  Block = memory_pool_.GetBlock(true);
  // the whole Block shall be zeroed
  ASSERT_EQ(std::memcmp(kClearedBlockData.data(), Block, kTestPoolBlockSize), 0);
}

/* Returned memory can be written to. */
TEST_F(MemoryPoolTest, WriteToMemory) {
  // expected data
  std::array<char, kTestPoolBlockSize> expected_data{};
  std::memset(expected_data.data(), 1, kTestPoolBlockSize);
  // write test data and check
  void *Block = memory_pool_.GetBlock(true);
  std::memset(Block, 1, kTestPoolBlockSize);
  ASSERT_EQ(std::memcmp(expected_data.data(), Block, kTestPoolBlockSize), 0);
}
