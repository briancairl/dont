# dont

A collection of C++ template (metaprogramming) utilities that I often need, but don't want to have to re-implement for the 1000th time.

## requirements

- A C++ compiler that supports:
    + C++11 or greater
    + `#pragma once` because I refuse to accept that it's not standard
- [optional] [GTest](https://github.com/google/googletest) (for unit tests)

Note that the implementations included here *do not depend on the STL*.

## includes

- appending to a template parameter pack
- merging template parameter two packs
