load("@rules_rust//rust:defs.bzl", "rust_library", "rust_test")

package(default_visibility = ["//visibility:public"])

rust_library(
    name = "rust_lib",
    srcs = glob(["src/*.rs"]),
)

rust_library(
    name="rust_test_lib",
    srcs = glob(["tests/*.rs"]),
    deps=[":rust_lib"]
)

rust_test(
    name="rust_test",
    crate=":rust_test_lib",
)
