cc_library(
    name = "em_lib",
    srcs = [
        "src/allocator.cpp",
        "src/allocator_config.hpp",
        "src/memory_pool.hpp",
        "src/memory_slot.hpp",
    ],
    hdrs = ["include/em.hpp"],
    copts = [
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wpedantic",
        "-std=c++14",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "memory_pool_tests",
    size = "small",
    srcs = [
        # headers and sources
        "src/memory_slot.hpp",
        # test definitions
        "tests/memory_pool_tests.cpp",
        # unit under test
        "src/memory_pool.hpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wpedantic",
        "-std=c++14",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":em_lib",
        "@googletest//:gtest_main",
    ],
)
