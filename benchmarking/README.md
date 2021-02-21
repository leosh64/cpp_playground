# benchmarking

Compare different implementations of the same function/algorithm in a benchmark and use unit tests to ensure the output of each implementation is correct.

## Run

```sh
bazel run //multithreading:main
```

## Test

```sh
bazel run //multithreading:test
```

## Benchmark

Make sure to use `-c opt` to enable compiler optimizations when timing the results:

```sh
bazel run -c opt //multithreading:benchmark
```
