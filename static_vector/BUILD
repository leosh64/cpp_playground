cc_library(
    name = "static_vector_lib",
    hdrs = ["static_vector.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [":static_vector_lib"],
)

cc_test(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
        ":static_vector_lib",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
