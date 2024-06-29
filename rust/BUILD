load("@rules_rust//rust:defs.bzl", "rust_library", "rust_test")

package(default_visibility = ["//visibility:public"])

rust_library(
    name = "rust_lib",
    srcs = ["src/lib.rs"],
)

rust_test(
    name="rust_test",
    crate=":rust_lib"
)
