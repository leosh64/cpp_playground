cc_library(
    name = "timeit",
    hdrs = ["timeit.h"],
)

cc_test(
    name = "timeit_test",
    srcs = ["timeit_test.cpp"],
    deps = [
        ":timeit",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
