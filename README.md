# Saravanan's monorepo

To build the repository, you will need the following
- [Git LFS](https://git-lfs.com/) is needed to pull some data/model files.
- C++ compiler with C++20 support
- [Bazel](https://bazel.build/) version 9.1.0


### Build and Test

Run the following Bazel command to build everything
```
bazel build //...
```

This repository depends on bunch of libraries and toolkits. Bazel will pull them as part of building the repository.
So, for first time, building will take sometime. Since Bazel caches artifacts, subsequent build will be breeze.

To run the all unit tests that are small & moderate, run the following Bazel test command
```
bazel test --test_size_filters="small,medium" --test_timeout_filters="short,moderate" //...
```

### OpenGL Viewer
Please make sure that graphics driver is installed.

Run the Bazel run command to launch the OpenGL viewer
```
bazel run //viz/ui:viewer
```
