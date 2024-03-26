#include <gtest/gtest.h>

#include "include/em.hpp"

/* EM_Alloc test stub */
TEST(Allocator, Alloc) { void *result = EM_Alloc(0, false); }

/* EM_ClearedAlloc test stub */
TEST(Allocator, ClearedAlloc) { void *result = EM_Alloc(0, true); }

/* EM_Free test stub */
TEST(Deallocator, Free) { EM_Free(nullptr); }
