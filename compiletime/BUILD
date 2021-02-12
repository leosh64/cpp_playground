cc_library(
    name = "lib",
    hdrs = ["polynomial.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [":lib"],
)

cc_test(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
        ":lib",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
