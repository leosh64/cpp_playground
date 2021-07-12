# cc_library(
#     name = "circular_buffer",
#     hdrs = ["circular_buffer.h"],
#     deps = [
#         ":circular_index"
#     ]
# )

# cc_test(
#     name = "circular_buffer_test",
#     srcs = ["circular_buffer_test.cpp"],
#     deps = [
#         ":circular_buffer",
#         "@gtest",
#         "@gtest//:gtest_main",
#     ],
# )

cc_library(
    name = "circular_index",
    hdrs = ["circular_index.h"],
)

cc_test(
    name = "circular_index_test",
    srcs = ["circular_index_test.cpp"],
    deps = [
        ":circular_index",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "static_vector",
    hdrs = ["static_vector.h"],
)

cc_test(
    name = "static_vector_test",
    srcs = ["static_vector_test.cpp"],
    deps = [
        ":static_vector",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
