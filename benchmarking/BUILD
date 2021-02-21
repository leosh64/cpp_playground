cc_library(
    name = "lib",
    hdrs = ["max_element.h"],
    linkopts = ["-pthread"],  # required for std::async with gcc on linux, adjust for other platforms!
)

cc_library(
    name = "utils",
    hdrs = ["data_generator.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":lib",
        ":utils",
    ],
)

cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [
        ":lib",
        ":utils",
        "@googlebenchmark//:benchmark_main",
    ],
)

cc_test(
    name = "test",
    srcs = ["test.cpp"],
    deps = [
        ":lib",
        ":utils",
        "@gtest//:gtest_main",
    ],
)
