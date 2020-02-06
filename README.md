# seri

A header-only, endian-aware integer serialization library for C++17.

## Introduction

`seri` defines several standard-layout integer-like types with a specified
representation and an alignment of 1. The types have names in the form
`(u|i)(16|32|64)_(le|be)_t`. Signedness is indicated by `u` or `i` prefix
for signed and unsigned, respectively. The suffixes `le` and `be` stand
for little-endian and big-endian.

For example, `u32_le_t` represents an unsigned 32-bit integer with
little-endian representation.

Each type is implicitly convertible to and from a corresponding type
from `<stdint.h>`, e.g. `u32_le_t` is convertible to and from `uint32_t`.
In most situations, you can use `seri` types like built-in integers.

You can form structures from `seri` integers to represent on-disk structures.

    struct my_file_header_t {
        /* 0x00 */ u32_le_t magic;
        /* 0x02 */ u16_le_t version;
        /* 0x06 */ u32_le_t length;
    };

Notice that `my_file_header_t::length` is misaligned.

## Getting Started

Add this repo as a subrepo of your project and add the `include` directory
into your include path.

If you're using CMake, you can also pull the library
via the FetchContent module.

    FetchContent_Declare(
        avakar_seri
        GIT_REPOSITORY https://github.com/avakar/seri.git
        GIT_TAG master
        )
    FetchContent_MakeAvailable(avakar_seri)

Then link against `avakar::seri` target and use namespace `avakar::seri`.
