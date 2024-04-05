cc_library(
    name = "em_lib",
    srcs = [
        "src/allocator.cpp",
        "src/allocator_config.cpp",
        "src/memory_pool.hpp",
        "src/memory_pool_interfaces.hpp",
    ],
    hdrs = ["include/allocator.hpp"],
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

cc_test(
    name = "allocator_tests",
    size = "small",
    srcs = [
        # test definitions
        "tests/allocator_tests.cpp",
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
        # unit under test
        ":em_lib",
        "@googletest//:gtest_main",
    ],
)
