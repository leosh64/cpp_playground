# cpp_playground

Playground for C++ projects and tests, bazel, Github Workflows (CI) and more.

## Usage

### Build, run, test

Use `bazel` to build, run and test targets in this repository:

```sh
bazel build //...
```

```sh
bazel run //compiletime:main
```

```sh
bazel test //...
```

### bazelisk

Using `bazelisk` allows to automatically download & execute the correct version of `bazel`, as pinned in the `.bazelversion` file. To install `bazelisk`, follow
the instructions on https://docs.bazel.build/versions/master/install-bazelisk.html.

### Test coverage report

Install necessary tools for test coverage analysis via the `lcov` package and then run:

```sh
# Analyze coverage for all test targets and store in coverage.dat file
bazel coverage  //...
# Generate HTML report and store in coverage directory
genhtml bazel-out/_coverage/_coverage_report.dat --output-directory coverage
```
