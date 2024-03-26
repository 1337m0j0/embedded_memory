#include <stdlib>

/** @brief Allocates a memory region of the required size. */
void * EM_Alloc(const std::size_t size);

/** @brief Allocates and clears a memory region of the required size. */
void * EM_ClearedAlloc(const std::size_t size);

/** @brief Makes a previously allocated memory region available again. */
void   EM_Free(void *ptr);
