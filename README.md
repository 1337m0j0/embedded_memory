# Embedded Memory

A memory allocator for safety-critical embedded devices. Example integration
and usage available in tests folder.

Main features:

* static pool-based memory manager
* configured at compile-time
* fully predictable execution time
* thread-safety
* safety-mechanisms
* can be used to replace libc and libcxx memory allocators

## Development Quickstart

Bazel is used as a build system. Some important commands:

* build library: `bazel build //:em_lib`
* run all tests: `bazel test //...`
* build compile commands: `bazel run @hedron_compile_commands//:refresh_all`

## Upcoming Features

* multithreading support
* profiling to understand memory needs of users
* profiling to assess performance

## Various Project Information

### Standards

* C++14
* Misra C++23

### Static tests

* static analysis with clang-tidy
* autoformatting with clang-format

### Dynamic tests

* unit testing via googletest framework

planned for 1.0:

* MC/DC coverage
* performance tests
* fault injection tests
* fuzz tests
