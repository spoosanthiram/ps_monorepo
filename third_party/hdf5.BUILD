load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "aec",
    srcs = ["lib/libaec.a"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "hdf5",
    srcs = [
        "lib/libhdf5.a",
        "lib/libszaec.a",
        "lib/libzlib-static.a",
    ],
    hdrs = glob(["include/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = [":aec"],
)

cc_library(
    name = "hdf5_cpp",
    srcs = ["lib/libhdf5_cpp.a"],
    hdrs = glob(["include/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = [":hdf5"],
)
