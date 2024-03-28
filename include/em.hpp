#ifndef INCLUDE_EM_HPP_
#define INCLUDE_EM_HPP_

#include <cstddef>

namespace em {

/** @brief Allocates a memory region of the required size.
 *
 * Sets the complete memory region to 0 when `clear_region` is `true`.
 */
void *alloc(const std::size_t size, const bool clear_region);

/** @brief Makes a previously allocated memory region available again. */
void free(void *ptr);

}  // namespace em

#endif  // INCLUDE_EM_HPP_
