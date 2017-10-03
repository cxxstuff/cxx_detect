CC_DETECT
---------

C++ compiler and features detection:

  * C/C++ compiler vendor and version.
  * C/C++ compiler features.
  * Target architecture.
  * Target operating system.

Compiler-neutral macros:

  * API visibility control (visibility, import, export).
  * C/C++ calling convention.
  * Likely / unlikely.
  * Assumptions about code and alignment.
  * Function decorators (inline, no-inline, no-return).
  * C/C++ language features like fallthrough.
  * C/C++ support for typical concepts like length of a static array[], offset-of, etc.

This project is dual licensed under **PUBLIC DOMAIN** and **ZLIB** licenses. ZLIB is provided for those that cannot use PUBLIC DOMAIN. Contributing to this project means that you agree with the licensing and that you make the contribution available under BOTH licenses mentioned.

Disclaimer
----------

**CC_DETECT project just started, if you found anything wrong (especially macro names) it would be good to report it now as there is still a chance to fix it without breaking others code. Future versions will remain stable.**

Design
------

Core design:

  * The whole functionality is implemented in a single header `cc_detect.h` and all macros start with **CC_** prefix.
  * The header is versioned and will automatically update all macros if older `cc_detect.h` was included previously, allowing coexistence of multiple projects having various versions of CC_DETECT embedded with them, each include of `cc_detect.h` performs a version check.

The header defines a set of preprocessor macros that can be divided into the following categories:

  * Constant - in most cases a boolean value that contains 0 (feature not-present) or 1 (feature present), sometimes having larger value to clarify the feature or compiler version
  * Macro - implements common concept in a vendor-specific way, like **CC_LIKELY**, **CC_EXPORT**, etc...

The library mostly targets C++ projects that require extensible detection of C++ features, but was designed to work with C projects as well. It just defines macros, nothing else, so it's perfectly safe for any kind of C/C++ project.

Motivation
----------

This header started as an experiment to unify needs of various projects. When a project starts it's usually small and clean and everybody wants to keep it that way, but when it gets features, when it's ported to other architectures and supposed to be compiled by more C/C++ compilers, the amount of compiler-specific stuff grows and sometimes is challenging to get it right from the beginning. For example there isn't a way to 'force-inline' function without vendor-specific keywords (and there buggy MINGW's always_inline that leads to internal compiler error, etc), there is no cross-platform visibility concept (visibility on non-Windows platforms and dllimport/dllexport on Windows), and there is no easy C++ features detection outside of clang.

In general most projects try to solve this problem either locally or by relying on other library/framework that solves that problem for them, like boost or Qt. Projects that solve this locally have to provide and maintain a lot `#ifdef`ed code that grows and that is sometimes hard to follow and understand as it tries to be as small as possible.

The first phase of this project was to write a tool that generates all of this with `SOMEPROJECT_` prefix to solve the compiler detection and features locally, making all of the macros available per-project basis. That works well but clutters the project with project-specific macros which no other project(s) should use (they are usually not documented, they are not part of the API). Based on past experience the `cc_detect.h` header was written to address such issues and to document what each macro means and how it should be used.

Contributing
------------

If you like `cc_detect.h` and would like to contribute please open an issue, and/or provide an implementation of your problem/solution. Pull requests are welcome if they solve a general problem (C/C++ features detection, C/C++ language support, etc).

The most appreciated contributions:

  * Supporting other C/C++ compilers (please don't support outdated compilers).
  * Supporting more C/C++ language features not currently provided.
  * Fixing wrongly detected features.
  * Fixing and improving documentation (fixing terms and incorrectness, possibly providing links to each feature specification, etc).

C/C++ Compiler Vendor and Version
---------------------------------

Each compiler-vendor constant contains either 0, which means the compiler was not detected, or non-zero value, which represents a normalized compiler version.

  * `CC_CLANG` - Clang C/C++ compiler
  * `CC_GNU`   - GNU C/C++ compiler
  * `CC_INTEL` - Intel C/C++ compiler (ICC)
  * `CC_MSC`   - Microsoft C/C++ compiler (MSC)

Additionally the following constants are provided:

  * `CC_MINGW` - 0 if not MINGW, 32 if `__MINGW32__` is defined, or 64 if `__MINGW64__` is defined
  * `CC_INTEL_COMPAT_MODE` - Intel compiler is in GNU/Clang compatibility mode (1) or not (0).

The compilers are checked the following way:

```c++
#if CC_MSC
// Microsoft compiler
#elif CC_GNU || CC_CLANG
// GNU or Clang
#else
// other
#endif
```

If you need a compiler version you can use arithmetic operators and `CC_MAKE_VER(MAJOR, MINOR, PATCH)` macro:

```c++
#if CC_GNU >= CC_MAKE_VER(4, 8, 2)
// GNU compiler >= 4.8.2
#elif CC_MSC >= CC_MAKE_VER(19, 0, 0)
// MSC compiler >= 19.0.0
#else
// Other compiler
#endif
```

C/C++ Language Version
----------------------

  * **CC_CPLUSPLUS** - C++ version, 0 if not C++ (C mode only), or a number that mostly corresponds to `__cplusplus` if set properly (otherwise it's changed to contain either **199711L** or **201103L** depending on the compiler features available).

C/C++ Compiler Features
-----------------------

Vendor Specific:

  * `CC_HAS_ASSUME`                  - `__assume` keyword.
  * `CC_HAS_ASSUME_ALIGNED`          - `__assume_aligned` keyword.
  * `CC_HAS_ATTRIBUTE`               - `__attribute__` in general.
  * `CC_HAS_ATTRIBUTE_ALIGNED`       - `__attribute__(__aligned__)`.
  * `CC_HAS_ATTRIBUTE_ALWAYS_INLINE` - `__attribute__(__always_inline__)`.
  * `CC_HAS_ATTRIBUTE_NOINLINE`      - `__attribute__(__aligned__)`.
  * `CC_HAS_ATTRIBUTE_NORETURN`      - `__attribute__(__noreturn__)`.
  * `CC_HAS_ATTRIBUTE_OPTIMIZE`      - `__attribute__(__optimize__)`.
  * `CC_HAS_BUILTIN_ASSUME`          - `__builtin_assume()`.
  * `CC_HAS_BUILTIN_ASSUME_ALIGNED`  - `__builtin_assume_aligned()`.
  * `CC_HAS_BUILTIN_EXPECT`          - `__builtin_expect()`.
  * `CC_HAS_BUILTIN_UNREACHABLE`     - `__builtin_unreachable()`.
  * `CC_HAS_DECLSPEC_ALIGN`          - `__declspec(align)`.
  * `CC_HAS_DECLSPEC_NOINLINE`       - `__declspec(noinline)`.
  * `CC_HAS_DECLSPEC_NORETURN`       - `__declspec(noreturn)`.
  * `CC_HAS_FORCEINLINE`             - `__forceinline` keyword.

Standardized:

  * `CC_HAS_AGGREGATE_NSDMI`         - Default initializers for aggregates (NSDMI) (C++14).
  * `CC_HAS_ALIGNAS`                 - `alignas` keyword  (C++11).
  * `CC_HAS_ALIGNOF`                 - `alignof` keyword  (C++11).
  * `CC_HAS_AUTO_TYPE`               - `auto` type  (C++11).
  * `CC_HAS_BINARY_LITERALS`         - Binary literals (C++14).
  * `CC_HAS_CONSTEXPR`               - `constexpr` keyword (C++11).
  * `CC_HAS_CONTEXTUAL_CONVERSIONS`  - Contextual conversions (C++14).
  * `CC_HAS_DECLTYPE`                - `decltype` keyword  (C++11).
  * `CC_HAS_DECLTYPE_AUTO`           - `decltype(auto)` support  (C++14).
  * `CC_HAS_DEFAULTED_FUNCTIONS`     - Defaulted functions  (C++11).
  * `CC_HAS_DELEGATING_CONSTRUCTORS` - Delegating constructors  (C++11).
  * `CC_HAS_DELETED_FUNCTIONS`       - Deleted functions  (C++11).
  * `CC_HAS_FINAL`                   - `final` keyword  (C++11).
  * `CC_HAS_GENERIC_LAMBDAS`         - Generic lambdas (C++14).
  * `CC_HAS_INIT_CAPTURES`           - Generalized lambda capture (init-capture) (C++14)
  * `CC_HAS_INITIALIZER_LISTS`       - Initializer lists  (C++11).
  * `CC_HAS_INLINE_NAMESPACES`       - Inline namespaces  (C++11).
  * `CC_HAS_LAMBDAS`                 - Lambda functions  (C++11).
  * `CC_HAS_NATIVE_CHAR`             - Native `char` type (`char`, `signed char`, and `unsigned char` are different types in such case).
  * `CC_HAS_NATIVE_WCHAR_T`          - Native `wchar_t` type.
  * `CC_HAS_NATIVE_CHAR16_T`         - Native `char16_t` type  (C++11).
  * `CC_HAS_NATIVE_CHAR32_T`         - Native `char32_t` type  (C++11).
  * `CC_HAS_NOEXCEPT`                - `noexcept` keyword  (C++11).
  * `CC_HAS_NULLPTR`                 - `nullptr` keyword  (C++11).
  * `CC_HAS_OVERRIDE`                - `override` keyword  (C++11).
  * `CC_HAS_RANGE_FOR`               - Range-based for-loop (C++11).
  * `CC_HAS_RELAXED_CONSTEXPR`       - Relaxed `constexpr` (C++14).
  * `CC_HAS_RVALUE_REFERENCES`       - RValue references & move semantics  (C++11).
  * `CC_HAS_STATIC_ASSERT`           - `static_assert` keyword  (C++11).
  * `CC_HAS_STRONG_ENUMS`            - Strongly typed enums  (C++11).
  * `CC_HAS_THREAD_LOCAL`            - `thread_local` keyword  (C++11).
  * `CC_HAS_UNRESTRICTED_UNIONS`     - Unrestricted unions  (C++11).
  * `CC_HAS_VARIABLE_TEMPLATES`      - Variable templates  (C++14).
  * `CC_HAS_VARIADIC_TEMPLATES`      - Variadic templates  (C++11).

Since all macros are defined, just their constants differ, features can be checked the following way:

```c++
#if !CC_HAS_STRONG_ENUMS       || \
    !CC_HAS_VARIADIC_TEMPLATES || \
    !CC_HAS_CONSTEXPR
#error "Project X cannot be compiled as your compiler doesn't support some C++ features it requires"
#endif
```

Another example:

```c++
class SomeClass {
  SomeClass() {}

  #if CC_HAS_RVALUE
  SomeClass(SomeClass&& other) { ...} // Move semantics
  #endif
}
```

Target Architecture
-------------------

  * `CC_ARCH_X86`                    - Target architecture is 32-bit x86 (X86|IA32).
  * `CC_ARCH_X64`                    - Target architecture is 64-bit x86_64 (X64|AMD64).
  * `CC_ARCH_ARM32`                  - Target architecture is 32-bit ARM or AArch32.
  * `CC_ARCH_ARM64`                  - Target architecture is 64-bit AArch64.

Additionally the following constants are provided:

  * `CC_ARCH_BITS`                   - 32 or 64 depending on the architecture.
  * `CC_ARCH_LE`                     - 1 if the target architecture is LITTLE ENDIAN, otherwise 0.
  * `CC_ARCH_BE`                     - 1 if the target architecture is BIG ENDIAN, otherwise 0.

Architectures can be checked the following way:

```c++
#if CC_ARCH_X86 || CC_ARCH_X64
// X86 32-bit or 64-bit code path.
#endif

#if CC_ARCH_BITS == 32
// 32-bit arch code-path.
#else
// 64-bit arch code-path.
#endif
```

Target Operating System
-----------------------

  * `CC_OS_BSD`                      - BSD, including MacOS, OpenBSD, FreeBSD, etc.
  * `CC_OS_MAC`                      - MacOS.
  * `CC_OS_LINUX`                    - Linux, including Android.
  * `CC_OS_WINDOWS`                  - Windows.

Additionally the following constants are provided:

  * `CC_OS_IOS`                      - iOS.
  * `CC_OS_ANDROID`                  - Android.
  * `CC_OS_NETBSD`                   - NetBSD.
  * `CC_OS_FREEBSD`                  - FreeBSD.
  * `CC_OS_OPENBSD`                  - OpenBSD.
  * `CC_OS_DRAGONFLYBSD`             - DragonFlyBSD.
  * `CC_OS_QNX`                      - QNX.
  * `CC_OS_SOLARIS`                  - Solaris.
  * `CC_OS_CYGWIN`                   - Cygwin.

Visibility (Import | Export)
----------------------------

  * `CC_IMPORT`                      - Mark API to be imported.
  * `CC_EXPORT`                      - Mark API to be exported.

Example:

```c++
#if SOMELIB_EXPORTS
# define SOMELIB_API CC_EXPORT
#else
# define SOMELIB_API CC_IMPORT
#endif

SOMELIB_API void SomeFunction(int x, int y);

class SomeClass {
  SOMELIB_API SomeClass();
  SOMELIB_API ~SomeClass();

  // etc...
}
```

Function Attributes & Calling Conventions
-----------------------------------------

Calling Conventions:

  * `CC_CDECL`                      - CDECL calling convention.
  * `CC_STDCALL`                    - STDCALL calling convention.
  * `CC_FASTCALL`                   - FASTCALL calling convention.
  * `CC_REGPARM(N)`                 - REGPARM(N) calling convention (GCC and Clang).

Function Attributes:

  * `CC_FORCEINLINE`                - Force to always inline a certain function.
  * `CC_NOINLINE`                   - Force to never inline a certain function.
  * `CC_NORETURN`                   - Function never returns.

Example:

```c++
// Will always use CDECL calling convention, even if the compiler defaults to a different one.
typedef void (CC_CDECL* SomeFunc)(int, int);

void CC_CDECL SomeFuncImpl(int x, int y) {}

// Will use __attribute__((regparm(3))) if available, nothing otherwise.
int CC_REGPARM(3) ExplicitRegParm3Func(int x, int y, int z) { return x + y + z; }

// Enforced to be always inlined.
CC_FORCEINLINE uint32_t PerformanceCriticalFunction(uint32_t x, uint32_t y) {}

// Enforced to be never inlined.
CC_NOINLINE uint32_t FunctionThatShouldNeverBeInlined(uint32_t x, uint32_t y) {}

// Never returns.
CC_NORETURN void Crash() { ::abort(); }

uint32_t SomeFunc(void *p) {
  if (CC_LIKELY(p)) {
    // Expected code-path.
    return 0;
  }
  else {
    // Runtime error. Since Crash() is decorated by CC_NORETURN the
    // compiler knows it will never return and will not emit warning
    // about a missing `return`.
    Crash();
  }
}

```

Likely / Unlikely
-----------------

  * `CC_LIKELY`                     - Expression is likely to be true.
  * `CC_UNLIKELY`                   - Expression is unlikely to be true.

Used to tell compiler which code-paths are likely, improves error-handling performance:

```c++
void SomeFunc(uint8_t* array, size_t size) {
  if (CC_UNLIKELY(!array))
    return;

  if (CC_LIKELY(size < 16)) {
    // Likely code-path.
  }
  else {
    // Unlikely code-path.
  }
}
```

Assumptions
-----------

  * `CC_ASSUME(EXP)`                - Assume certain expression must always be true.
  * `CC_ASSUME_ALIGNED(PTR, N)`     - Assume the `PTR` is aligned to at least `N` bytes. NOTE that `N` must be equal or greater than the natural alignment of `PTR`.

Example:

```c++
uint32_t SomeFunc(uint8_t* array, size_t size) {
  CC_ASSUME(size > 0);

  // Compiler should omit the first `i < size` check
  // as it assumes size is always greater than zero.
  uint32_t result = 0;
  for (size_t i = 0; i < size; i++)
    result += array[i];
  return result;
}

uint32_t SomeFunc(const uint8_t* array, size_t size) {
  // Autovectorizer knows this array is aligned to 16 bytes.
  CC_ASSUME_ALIGNED(array, 16);

  uint32_t result = 0;
  for (size_t i = 0; i < size; i++)
    result += array[i];
  return result;
}
```

Annotations
-----------

  * `CC_UNUSED(X)`                  - Mark a variable or function argument as possibly unused.
  * `CC_FALLTHROUGH`                - Tell the compiler that it's a fallthrough from one switch case to another. Required by new compilers otherwise they would warn about it.

Example:

```c++
uint32_t FuncWithUnusedArgument(uint32_t x, uint32_t y) {
  CC_UNUSED(x);
  return y;
}

void FuncWithExplicitFallThrough(uint32_t x) {
  switch (x) {
    case 0:
      DoSomething();
      // Modern compiler would warn you without explicit `CC_FALLTHROUGH`.
      CC_FALLTHROUGH;
    case 1:
      DoSomethingElse();
      break;
  }
}
```

Other General Purpose Macros
----------------------------

  * `CC_ARRAY_SIZE(X)`              - Get number of elements of an array at a compile time.
  * `CC_OFFSET_OF(STRUCT, MEMBER)`  - Get an offset of `MEMBER` in `STRUCT`.

Example:

```c++
struct Point {
  double x, y;
};

void FuncThatUsesOffsetOf() {
  printf("Offset of 'Point.x' %u\n", unsigned(CC_OFFSET_OF(Point, x)));
  printf("Offset of 'Point.y' %u\n", unsigned(CC_OFFSET_OF(Point, y)));
}

void FuncThatUsesArraySize() {
  uint32_t array[32];
  for (size_t i = 0; i < CC_ARRAY_SIZE(array); i++)
    array[i] = uint32_t(i);
}
```
