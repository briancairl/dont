# dont

A collection of C++ template (metaprogramming) utilities that I often need, but don't want to have to re-implement for the 1000th time.

## Requirements

- A C++ compiler that supports:
    + C++17 or greater
    + `#pragma once` because I refuse to accept that it's not standard
- [optional] CMake
- [optional] [GTest](https://github.com/google/googletest) (for unit tests)

Note that the `core` implementations included here *do not depend on the STL*.

## Includes

- appending to a template parameter pack
- merging two or more template parameter packs
- conditionally removing types from param packs
- "iterating" over tuple-like objects (loop-unrolling)

## Running tests

### Clean rebuild and test

```bash
rm -rf build; (mkdir build && cd build && cmake .. -DDONT_ENABLE_TESTING:bool=on && make && ctest -V)
```
