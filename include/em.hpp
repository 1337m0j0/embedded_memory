
#ifndef INCLUDE_EMBEDDED_MEMORY_HPP_
#define INCLUDE_EMBEDDED_MEMORY_HPP_

#include <cstddef>

/** @brief Allocates a memory region of the required size.
 *
 * Sets the complete memory region to 0 when `clear_region` is `true`.
 */
void *EM_Alloc(const std::size_t size, const bool clear_region);

/** @brief Makes a previously allocated memory region available again. */
void EM_Free(void *ptr);

#endif
