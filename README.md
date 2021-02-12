# cpp_playground

Playground for C++ projects and tests, bazel, Github Workflows (CI) and more.

## Usage

Use `bazel` to build, run and test targets in this repository:

```sh
bazel build //...
```

```sh
bazel run //static_vector:main
```

```sh
bazel test //...
```

### bazelisk

Using `bazelisk` allows to automatically download & execute the correct version of `bazel`, as pinned in the `.bazelversion` file. To install `bazelisk`, follow
the instructions on https://docs.bazel.build/versions/master/install-bazelisk.html.
