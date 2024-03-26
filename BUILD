cc_library(
    name = "em_lib",
    srcs = ["src/allocator.cpp"],
    hdrs = ["include/em.hpp"],
    copts = [
        "-Wall",
        "-Wextra",
        # warnings as errors to be enabled for the first release
        # "-Werror",
        "-Wpedantic",
        "-std=c++14",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "em_test",
    size = "small",
    srcs = ["tests/allocator_tests.cpp"],
    copts = [
        "-Wall",
        "-Wextra",
        # warnings as errors to be enabled for the first release
        # "-Werror",
        "-Wpedantic",
        "-std=c++14",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":em_lib",
        "@googletest//:gtest_main",
    ],
)
