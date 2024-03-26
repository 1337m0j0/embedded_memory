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

## Quickstart

* build library: `bazel build //:em_lib`
* run all tests: `bazel test //...`
* build compile commands: `bazel run @hedron_compile_commands//:refresh_all`

## Roadmap

### Version 0.1.0

* basic implementation of all interfaces
* region management using linked-lists
* no support for multi-threading
* basic unit tests

## Project Details

### Compliance

* C++14
* Misra C++23
* POSIX

### Detailed Design

* interfaces defined in header
* allocation algorithms described in markdown files
* requirements for all functional and non-functional properties
* all requirements are traceable to unit tests

### Static tests

* static analysis

### Dynamic tests

* unit tests with MC/DC coverage
* performance stress tests
* fault injection tests
* fuzz tests

### Profiling

* extended profiling available to tune configuration

### Tooling

* build system: bazel
* tests: googletest
* static analysis: clang-tidy
* formatting: clang-format