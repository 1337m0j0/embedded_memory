#ifndef INCLUDE_ALLOCATOR_HPP_
#define INCLUDE_ALLOCATOR_HPP_

#include <cstddef>

#include "src/memory_pool.hpp"

namespace em {

class Allocator {
 public:
  /** @brief Allocates a memory region of at least the requested size.
   *
   * @param requested_size needed memory region size.
   * @param clear_region if true, causes the memory region to be initialized to 0.
   *
   * @returns If successful, returns a pointer to the allocated memory region.
   *          If unsuccessful, returns a null-pointer;
   */
  static void *Alloc(std::size_t requested_size, bool clear_region) noexcept;

  /** @brief Makes a previously allocated memory region available again. */
  static void Free(void *ptr) noexcept;

 private:
  /** @brief The list of memory pools available to the allocator. */
  static IMemoryPoolList *memory_pool_list_;  // NOLINT: The pointer and the data are not
                                              // const to enable linked-list iteration
                                              // in Alloc() and Free(). Both are protected
                                              // by the private scope limitation.
};

}  // namespace em

#endif  // INCLUDE_ALLOCATOR_HPP_
