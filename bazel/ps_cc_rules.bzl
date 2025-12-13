PS_CXXOPTS = [
    "-Werror",
    "-Wpedantic",
    "-Wextra",
    "-Wformat-security",
    "-Wswitch-enum",
    "-Wuninitialized",
    "-Wshadow",
    "-Wcast-align",
]

def ps_cc_library(**kwargs):
    native.cc_library(
        copts = PS_CXXOPTS + kwargs.get("copts", []),
        **kwargs
    )
