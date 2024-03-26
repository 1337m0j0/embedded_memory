
#ifndef INCLUDE_EMBEDDED_MEMORY_HPP_
#define INCLUDE_EMBEDDED_MEMORY_HPP_

#include <cstddef>

/** @brief Allocates a memory region of the required size. */
void * EM_Alloc(const std::size_t size);

/** @brief Allocates and clears a memory region of the required size. */
void * EM_ClearedAlloc(const std::size_t size);

/** @brief Makes a previously allocated memory region available again. */
void   EM_Free(void *ptr);

#endif
