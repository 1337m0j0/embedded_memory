cc_library(
    name = "em_lib",
    srcs = ["src/allocator.cpp"],
    hdrs = ["include/em.hpp"],
)

cc_test(
    name = "em_test",
    size = "small",
    srcs = ["tests/allocator_tests.cpp"],
    deps = [
        ":em_lib",
        "@com_google_googletest//:gtest_main",
    ],
)
