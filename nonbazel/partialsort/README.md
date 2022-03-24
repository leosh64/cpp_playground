# Comparing Partial Sort

This is a small C++ project to compare the performance of partial sorting of data using STL algorithms. Imagine the requirement to get the top `x` percent of elements in a collection `v` in sorted order. There are a few ways to do so:

Set
```
begin = begin(v)
end = end(v)
partition = begin + x * v.size()
```

1. sort the entire container with `sort(begin, end)` and then use elements from `begin` to `partition`
2. partially sort the container with ``partial_sort(begin, partition, end)`
3. partition the container with `nth_element(begin, partition, end)` and then `sort(begin, partition)`

Which one is fastest? The answer might not be so obvious.

## Requirements

The following software components are required to run this project:
```
g++     # (or any other C++ compiler)
make
tee
gnuplot
```

It has been tested on Ubuntu 20.04.

## Running

Just run `make` to compile, run the benchmark and generate a plot comparing the runtime.

## Results

TODO.
