# lib_hashtable: C++17 hashtable for folks who don't wanna use std::unordered_map

## Usage

This is a header-only library, so just include `lib_hashtable` as a CMake module (if you're using CMake). You can also just copy the entire `lib_hashtable` directory and use it in your project directly.

## Testing

You'll need to have [googletest](https://github.com/google/googletest) and [google-benchmark](https://github.com/google/benchmark) in CMake's search path for tests to run. CMake's search paths are [here](https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure).

If you're on a macos system, running the following should install both:

```
brew install googletest
brew install google-benchmark
```

To actually run the tests, do this:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=DEBUG -DBUILD_TESTS=ON ..
make
ctest -V
```

## Run clang-tidy to clean up stuff while developing

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
# This will fix things in place
$(brew --prefix llvm)/share/clang/run-clang-tidy.py \
  -header-filter='.*' \
  -checks='-*,modernize*' \
  -fix
```

## Code Example

```
#include "hashtable.hpp"
#include <string>

auto
main(int argc, char** argv) -> int
{
  // Make a table
  auto table = lib_hashtable::HashTable<std::string, std::string, 10>();

  // Add something
  auto err = table.put("bunny", "foofoo");
  if (err != lib_hashtable::ERR_OK) {
    // panic
  }

  // Get it
  std::string value;
  err = table.get("bunny", value);
  if (err != lib_hashtable::ERR_OK) {
    // panic
  }

  // Kill it with fire
  err = table.remove("bunny");
  if (err != lib_hashtable::ERR_OK) {
    // panic
  }

  return 0;
}
```
