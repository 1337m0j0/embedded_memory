
#ifndef SRC_ALLOCATOR_CONFIG_HPP_
#define SRC_ALLOCATOR_CONFIG_HPP_

#include <cstdint>

namespace em {
namespace config {

// configuration for SMALL memory pool
constexpr std::uint32_t kSizeSlotsSmall{1024};
constexpr std::uint32_t kNumSlotsSmall{1000};

// configuration for MEDIUM memory pool
constexpr std::uint32_t kSizeSlotsMedium{8192};
constexpr std::uint32_t kNumSlotsMedium{1000};

// configuration for LARGE memory pool
constexpr std::uint32_t kSizeSlotsLarge{65536};
constexpr std::uint32_t kNumSlotsLarge{1000};

}  // namespace config
}  // namespace em

#endif  // SRC_ALLOCATOR_CONFIG_HPP_
