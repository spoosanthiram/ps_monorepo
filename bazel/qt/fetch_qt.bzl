"""qt library fetch"""

load("@bazel_tools//tools/build_defs/repo:local.bzl", "new_local_repository")

def fetch_qt6():
    """function which fetch remote prebuild qt libraries or use local qt(in macos)
    """

    new_local_repository(
        name = "qt_linux_x86_64",
        path = "/usr/local/qt",
        build_file = "@rules_qt//:qt_linux_x86_64.BUILD",
    )
