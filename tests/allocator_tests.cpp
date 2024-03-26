#include <gtest/gtest.h>
#include "include/em.hpp"

/* EM_Alloc test stub */
TEST(Allocator, Alloc) {
    void *result = EM_Alloc(0);
}

/* EM_ClearedAlloc test stub */
TEST(Allocator, ClearedAlloc) {
    void *result = EM_ClearedAlloc(0);
}

/* EM_Free test stub */
TEST(Deallocator, Free) {
    EM_Free(nullptr);
}
