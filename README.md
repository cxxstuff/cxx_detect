cxx_detect.h
------------

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

The project just started and still forms itself, however, it reached a certain stability already. Let us know if you think some macros should be renamed or added.

Design
------

  * If you never needed something like this you are lucky! However, if you found yourself having broken builds on CI because of wrongly written auto-detection, try `cxx_detect.h` or take it as an inspiration for your own solution.
  * It shouldn't be used as a dependency, distribute `cxx_detect.h` with your project / product and update it from time to time to ensure compatibility with new compilers and C++ features.
  * The whole functionality is implemented in a single header `cxx_detect.h` and all macros provided start with **CXX_** prefix. The intention is that multiple projects can use the same macros instead of defining their own like `SOMEPROJECT_HAS_RVALUE_REFERENCES` or `SOMEPROJECT_INLINE`.
  * The header is versioned and will automatically update all macros if older `cxx_detect.h` was included previously, allowing coexistence of multiple projects having various versions of the header embedded with them. Each inclusion of `cxx_detect.h` performs a version check and updates itself when necessary.

The header defines a set of preprocessor macros that can be divided into the following categories:

  * Values - in most cases used to store a boolean value that contains 0 (feature not-present) or 1 (feature present). Alternatively, non-boolean values can contain arbitrary constant clarifying some feature or compiler version.
  * Macros - used to implement common concepts in a compiler agnostic way like **CXX_LIKELY**, **CXX_EXPORT**, etc... which would expand to a vendor-specific code.

The library mostly targets C++ projects that require extensible detection of C++ features, but it does no harm to C - it just defines macros, nothing else, so it's perfectly safe for any kind of C/C++/ObjC project.

Motivation
----------

This header started as an experiment to unify needs of various projects. When a project starts it's usually small and clean and everybody wants to keep it that way, but when it gets features, when it's ported to other architectures and supposed to be compiled by more C/C++ compilers, the amount of compiler-specific stuff grows and sometimes it gets challenging to get it right from the beginning. For example there isn't a way to 'force-inline' function without knowing vendor-specific keywords, there is no cross-platform API (export / import) concept, and there is in general no easy C++ features detection outside of clang.

It's not just about the C++ standardized features. Today's compilers support a lot of extensions that make our lives easier - sanitizers, code deprecation, annotatations to get rid of diagnostic warnings, etc... In general most projects try to solve this problem either locally or by relying on other library/framework that solves that problem for them, like boost or Qt. Projects that solve this locally have to provide and maintain a lot of `#ifdef`ed code that grows and that is sometimes hard to follow and understand as it tries to be as small as possible.

The first phase of this project was to write a tool that generates all of this with `SOMEPROJECT_` prefix to solve the compiler detection and features locally, making all of the macros available per-project basis. That works well but clutters the project with project-specific macros which no other project(s) should use (they are usually not documented, they are not part of the API). Based on past experience the `cxx_detect.h` header was written to address such issues and to document what each macro means and how it should be used.

Contributing
------------

If you like `cxx_detect.h` and would like to contribute please open an issue, and/or provide an implementation of your problem/solution. Pull requests are welcome if they solve a general problem (C/C++ features detection, C/C++ language support, etc...).

The most appreciated contributions:

  * Supporting other C/C++ compilers (not outdated ones).
  * Supporting more C/C++ language features not currently provided.
  * Fixing wrongly detected features and macro names (if not too late).
  * Fixing and improving documentation (fixing terms and incorrectness, possibly providing links to each feature specification, etc).

C/C++ Compiler Vendor and Version
---------------------------------

Each compiler-vendor constant contains either 0, which means the compiler was not detected, or non-zero value, which represents a normalized compiler version.

  * `CXX_CLANG` - Clang C/C++ compiler.
  * `CXX_GNU`   - GNU C/C++ compiler.
  * `CXX_INTEL` - Intel C/C++ compiler (ICC).
  * `CXX_MSC`   - Microsoft C/C++ compiler (MSC).

Additionally the following constants are provided:

  * `CXX_GNU_COMPAT` - GNU compatibility mode, contains GNU version the compiler pretents to be (or is, in case of GNU compiler). Please note that the version is not reliable, for example Clang 4.0.1 with C++11 enabled pretends to be GCC 4.2.1, which doesn't even officially support C++11.
  * `CXX_MINGW` - 0 if not MINGW, 32 if `__MINGW32__` is defined, or 64 if `__MINGW64__` is defined

The compilers are checked the following way:

```c++
#if CXX_MSC
// Microsoft compiler
#elif CXX_GNU || CXX_CLANG
// GNU or Clang
#else
// other
#endif
```

If you need a compiler version you can use arithmetic operators and `CXX_MAKE_VER(MAJOR, MINOR, PATCH)` macro:

```c++
#if CXX_GNU >= CXX_MAKE_VER(4, 8, 2)
// GNU compiler >= 4.8.2
#elif CXX_MSC >= CXX_MAKE_VER(19, 0, 0)
// MSC compiler >= 19.0.0
#elif CXX_INTEL >= CXX_MAKE_VER(14, 1, 0)
// Intel compiler >= 14.1.0
#else
// Other compiler
#endif
```

Some compilers pretend to be GNU, you can check for `CXX_GNU_COMPAT` if you rely on GNU/Clang `__attribute__` or anything else:

```c++
// You can also use `CXX_GNU_COMPAT >= CXX_MAKE_VER(X, Y, Z)`, but it isn't reliable.
#if CXX_GNU_COMPAT
// Use GNU-compiler specifics.
#endif
```

Please note that if the compiler is not GNU the `CXX_GNU` will always be 0 even if the compiler defines `__GNUC__`. So checking `__GNUC__` is not the same as checking `CXX_GNU`. Use `CXX_GNU_COMPAT` in such case, which will be set always accordingly to the GNU compatibilty level (or the same as `CXX_GNU` if the compiler actually is GNU).

C/C++ Language Version
----------------------

  * **CXX_CPLUSPLUS** - C++ version, 0 if not C++ (C mode only), or a number that mostly corresponds to `__cplusplus` if set properly (otherwise it's changed to contain either **199711L** or **201103L** depending on the compiler features available).

C/C++ Compiler Features
-----------------------

All macro names that describe a language feature should correspond to the name of the feature as used insinde clang's `__has_feature()` and `__has_extension` macros.

Vendor Specific (all prefixed by `_X` to avoid collission with possible C++ ``[[attributes]]`):

  * `CXX_HAS_X_ASSUME`                       - `__assume` keyword.
  * `CXX_HAS_X_ASSUME_ALIGNED`               - `__assume_aligned` keyword.
  * `CXX_HAS_X_ATTRIBUTE`                    - `__attribute__` in general.
  * `CXX_HAS_X_ATTRIBUTE_ALIGNED`            - `__attribute__(__aligned__)`.
  * `CXX_HAS_X_ATTRIBUTE_ALWAYS_INLINE`      - `__attribute__(__always_inline__)`.
  * `CXX_HAS_X_ATTRIBUTE_DEPRECATED`         - `__attribute__(__deprecated__)`.
  * `CXX_HAS_X_ATTRIBUTE_NOINLINE`           - `__attribute__(__noinline__)`.
  * `CXX_HAS_X_ATTRIBUTE_NORETURN`           - `__attribute__(__noreturn__)`.
  * `CXX_HAS_X_ATTRIBUTE_OPTIMIZE`           - `__attribute__(__optimize__)`.
  * `CXX_HAS_X_BUILTIN_ASSUME`               - `__builtin_assume()`.
  * `CXX_HAS_X_BUILTIN_ASSUME_ALIGNED`       - `__builtin_assume_aligned()`.
  * `CXX_HAS_X_BUILTIN_EXPECT`               - `__builtin_expect()`.
  * `CXX_HAS_X_BUILTIN_UNREACHABLE`          - `__builtin_unreachable()`.
  * `CXX_HAS_X_DECLSPEC_ALIGN`               - `__declspec(align)`.
  * `CXX_HAS_X_DECLSPEC_DEPRECATED`          - `__declspec(deprecated)` and __declspec(deprecated("msg")).
  * `CXX_HAS_X_DECLSPEC_NOINLINE`            - `__declspec(noinline)`.
  * `CXX_HAS_X_DECLSPEC_NORETURN`            - `__declspec(noreturn)`.
  * `CXX_HAS_X_FORCEINLINE`                  - `__forceinline` keyword.

Standardized (C++11):

  * `CXX_HAS_ALIAS_TEMPLATES`                - Alias templates.
  * `CXX_HAS_ALIGNAS`                        - `alignas` keyword.
  * `CXX_HAS_ALIGNOF`                        - `alignof` keyword.
  * `CXX_HAS_ATTRIBUTES`                     - `[[attributes]]` support.
  * `CXX_HAS_AUTO_TYPE`                      - `auto` type.
  * `CXX_HAS_CONSTEXPR`                      - `constexpr` keyword.
  * `CXX_HAS_DECLTYPE`                       - `decltype` keyword.
  * `CXX_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGS` - Default template arguments in function templates.
  * `CXX_HAS_DEFAULTED_FUNCTIONS`            - Defaulted functions.
  * `CXX_HAS_DELEGATING_CONSTRUCTORS`        - Delegating constructors.
  * `CXX_HAS_DELETED_FUNCTIONS`              - Deleted functions.
  * `CXX_HAS_EXPLICIT_CONVERSIONS`           - Explicit conversions.
  * `CXX_HAS_FINAL`                          - `final` keyword.
  * `CXX_HAS_INHERITING_CONSTRUCTORS`        - Inheriting constructors.
  * `CXX_HAS_INITIALIZER_LISTS`              - Initializer lists.
  * `CXX_HAS_INLINE_NAMESPACES`              - Inline namespaces.
  * `CXX_HAS_LAMBDAS`                        - Lambda functions.
  * `CXX_HAS_LOCAL_TYPE_TEMPLATE_ARGS`       - Local and unnamed types as template arguments.
  * `CXX_HAS_NOEXCEPT`                       - `noexcept` keyword.
  * `CXX_HAS_NONSTATIC_MEMBER_INIT`          - In-class non-static data member initialization.
  * `CXX_HAS_NULLPTR`                        - `nullptr` keyword.
  * `CXX_HAS_OVERRIDE`                       - `override` keyword.
  * `CXX_HAS_RANGE_FOR`                      - Range-based for-loop.
  * `CXX_HAS_RAW_STRING_LITERALS`            - Raw string literals `R"..."`.
  * `CXX_HAS_REFERENCE_QUALIFIED_FUNCTIONS`  - Reference-qualified functions.
  * `CXX_HAS_RVALUE_REFERENCES`              - RValue references & move semantics.
  * `CXX_HAS_STATIC_ASSERT`                  - `static_assert` keyword.
  * `CXX_HAS_STRONG_ENUMS`                   - Strongly typed enums.
  * `CXX_HAS_THREAD_LOCAL`                   - `thread_local` keyword.
  * `CXX_HAS_UNICODE_LITERALS`               - Unicode literals.
  * `CXX_HAS_UNRESTRICTED_UNIONS`            - Unrestricted unions.
  * `CXX_HAS_VARIADIC_TEMPLATES`             - Variadic templates.

Standardized (C++14):

  * `CXX_HAS_AGGREGATE_NSDMI`                - Default initializers for aggregates (NSDMI).
  * `CXX_HAS_BINARY_LITERALS`                - Binary literals.
  * `CXX_HAS_CONTEXTUAL_CONVERSIONS`         - Contextual conversions.
  * `CXX_HAS_DECLTYPE_AUTO`                  - `decltype(auto)` support.
  * `CXX_HAS_GENERIC_LAMBDAS`                - Generic lambdas.
  * `CXX_HAS_INIT_CAPTURES`                  - Generalized lambda capture (init-capture).
  * `CXX_HAS_RELAXED_CONSTEXPR`              - Relaxed `constexpr`.
  * `CXX_HAS_VARIABLE_TEMPLATES`             - Variable templates.

Standardized (C++17):

  * (TODO)

Type System:

  * `CXX_HAS_NATIVE_CHAR`                    - Native `char` type.
  * `CXX_HAS_NATIVE_CHAR16_T`                - Native `char16_t` type (C++11), always matches `CXX_HAS_UNICODE_LITERALS`.
  * `CXX_HAS_NATIVE_CHAR32_T`                - Native `char32_t` type (C++11), always matches `CXX_HAS_UNICODE_LITERALS`.
  * `CXX_HAS_NATIVE_WCHAR_T`                 - Native `wchar_t` type.

Since all macros are always defined features can be checked by the following way:

```c++
#if !CXX_HAS_STRONG_ENUMS       || \
    !CXX_HAS_VARIADIC_TEMPLATES || \
    !CXX_HAS_CONSTEXPR
#error "Project X cannot be compiled as your compiler doesn't support some C++ features it requires"
#endif
```

Another example:

```c++
class SomeClass {
public:
  SomeClass() {}

  // Provide move semantics only if supported.
  #if CXX_HAS_RVALUE_REFERENCES
  SomeClass(SomeClass&& other) { ... }
  #endif
}
```

Target Architecture
-------------------

  * `CXX_ARCH_X86`                    - Target architecture is 32-bit x86 (X86|IA32).
  * `CXX_ARCH_X86_64`                 - Target architecture is 64-bit x86 (X64|X86_64|AMD64).
  * `CXX_ARCH_ARM32`                  - Target architecture is 32-bit ARM or AArch32.
  * `CXX_ARCH_ARM64`                  - Target architecture is 64-bit AArch64.

Additionally the following constants are provided:

  * `CXX_ARCH_BITS`                   - 32 or 64 depending on the architecture.
  * `CXX_ARCH_LE`                     - 1 if the target architecture is LITTLE ENDIAN, otherwise 0.
  * `CXX_ARCH_BE`                     - 1 if the target architecture is BIG ENDIAN, otherwise 0.

Architectures can be checked the following way:

```c++
#if CXX_ARCH_X86 || CXX_ARCH_X86_64
// X86 32-bit or 64-bit code path.
#endif

#if CXX_ARCH_BITS == 32
// 32-bit arch code-path.
#else
// 64-bit arch code-path.
#endif
```

Target Operating System
-----------------------

  * `CXX_OS_BSD`                      - BSD, including MacOS, OpenBSD, FreeBSD, etc.
  * `CXX_OS_MAC`                      - MacOS.
  * `CXX_OS_LINUX`                    - Linux, including Android.
  * `CXX_OS_WINDOWS`                  - Windows.

Additionally the following constants are provided:

  * `CXX_OS_IOS`                      - iOS.
  * `CXX_OS_ANDROID`                  - Android.
  * `CXX_OS_NETBSD`                   - NetBSD.
  * `CXX_OS_FREEBSD`                  - FreeBSD.
  * `CXX_OS_OPENBSD`                  - OpenBSD.
  * `CXX_OS_DRAGONFLYBSD`             - DragonFlyBSD.
  * `CXX_OS_QNX`                      - QNX.
  * `CXX_OS_SOLARIS`                  - Solaris.
  * `CXX_OS_CYGWIN`                   - Cygwin.

Export & Import
---------------

  * `CXX_EXPORT`                      - Mark API to be exported.
  * `CXX_IMPORT`                      - Mark API to be imported.

Example:

```c++
#if SOMELIB_EXPORTS
# define SOMELIB_API CXX_EXPORT
#else
# define SOMELIB_API CXX_IMPORT
#endif

SOMELIB_API void SomeFunction(int x, int y);

class SomeClass {
public:
  SOMELIB_API SomeClass();
  SOMELIB_API ~SomeClass();

  // etc...
}
```

Function Attributes & Calling Conventions
-----------------------------------------

Calling Conventions:

  * `CXX_CDECL`                      - CDECL calling convention.
  * `CXX_STDCALL`                    - STDCALL calling convention (32-bit X86).
  * `CXX_FASTCALL`                   - FASTCALL calling convention (32-bit X86).
  * `CXX_REGPARM(N)`                 - REGPARM(N) calling convention (GNU and Clang).

Function Attributes:

  * `CXX_FORCEINLINE`                - Function should be always inlined.
  * `CXX_NOINLINE`                   - Function should be never inlined.
  * `CXX_NORETURN`                   - Function doesn't return (abort, etc).

Example:

```c++
// Will always use CDECL calling convention, even if the compiler defaults to a different one.
typedef void (CXX_CDECL* SomeFunc)(int, int);

void CXX_CDECL SomeFuncImpl(int x, int y) {}

// Will use __attribute__((regparm(3))) if available, nothing otherwise.
int CXX_REGPARM(3) ExplicitRegParm3Func(int x, int y, int z) { return x + y + z; }

// Enforced to be always inlined.
CXX_FORCEINLINE uint32_t PerformanceCriticalFunction(uint32_t x, uint32_t y) {}

// Enforced to be never inlined.
CXX_NOINLINE uint32_t FunctionThatShouldNeverBeInlined(uint32_t x, uint32_t y) {}

// Never returns.
CXX_NORETURN void Terminate() { ::abort(); }

uint32_t SomeFunc(void *p) {
  if (p) {
    // Expected code-path.
    return 0;
  }
  else {
    // Runtime error. Since Terminate() has CXX_NORETURN attribute
    // the compiler will not emit a warning about a missing return.
    Terminate();
  }
}
```

Likely / Unlikely
-----------------

  * `CXX_LIKELY`                     - Expression is likely to be true.
  * `CXX_UNLIKELY`                   - Expression is unlikely to be true.

Used to tell compiler which code-paths are likely, improves error-handling performance:

```c++
void SomeFunc(uint8_t* array, size_t size) {
  if (CXX_UNLIKELY(!array))
    return;

  if (CXX_LIKELY(size < 16)) {
    // Likely code-path.
  }
  else {
    // Unlikely code-path.
  }
}
```

Assumptions
-----------

  * `CXX_ASSUME(EXP)`                - Assume certain expression must always be true.
  * `CXX_ASSUME_ALIGNED(PTR, N)`     - Assume the `PTR` is aligned to at least `N` bytes. NOTE that `N` must be equal or greater than the natural alignment of `PTR`.

Example:

```c++
uint32_t SomeFunc(uint8_t* array, size_t size) {
  CXX_ASSUME(size > 0);

  // Compiler should omit the first `i < size` check
  // as it assumes size is always greater than zero.
  uint32_t result = 0;
  for (size_t i = 0; i < size; i++)
    result += array[i];
  return result;
}

uint32_t SomeFunc(const uint8_t* array, size_t size) {
  // Autovectorizer knows this array is aligned to 16 bytes.
  CXX_ASSUME_ALIGNED(array, 16);

  uint32_t result = 0;
  for (size_t i = 0; i < size; i++)
    result += array[i];
  return result;
}
```

Annotations
-----------

  * `CXX_UNUSED(X)`                  - Mark a variable or function argument as possibly unused.
  * `CXX_FALLTHROUGH`                - Tell the compiler that it's a fallthrough from one switch case to another. Required by new compilers otherwise they would warn about it.

Example:

```c++
uint32_t FuncWithUnusedArgument(uint32_t x, uint32_t y) {
  CXX_UNUSED(x);
  return y;
}

void FuncWithExplicitFallThrough(uint32_t x) {
  switch (x) {
    case 0:
      DoSomething();
      // Modern compiler would warn you without explicit `CXX_FALLTHROUGH`.
      CXX_FALLTHROUGH;
    case 1:
      DoSomethingElse();
      break;
  }
}
```

Other General Purpose Macros
----------------------------

  * `CXX_ARRAY_SIZE(X)`              - Get number of elements of an array at a compile time.
  * `CXX_OFFSET_OF(STRUCT, MEMBER)`  - Get an offset of `MEMBER` in `STRUCT`.

Example:

```c++
struct Point {
  double x, y;
};

void FuncThatUsesOffsetOf() {
  printf("Offset of 'Point.x' %u\n", unsigned(CXX_OFFSET_OF(Point, x)));
  printf("Offset of 'Point.y' %u\n", unsigned(CXX_OFFSET_OF(Point, y)));
}

void FuncThatUsesArraySize() {
  uint32_t array[32];
  for (size_t i = 0; i < CXX_ARRAY_SIZE(array); i++)
    array[i] = uint32_t(i);
}
```

TODOs & Unsable Macros
----------------------

These macros will most probably change their names in the future and are thus unstable:

  * `CXX_ARCH_ARM32` - Not sure about the name.
  * `CXX_ARCH_ARM64` - Not sure about the name.
  * `CXX_ALIGN_TYPE` - Allows to align type, addition to C++ `alignas` (used in situations not allowed by `alignas`).
  * `CXX_ALIGN_DECL` - Allows to align variable, addition to C++ `alignas` (used in situations not allowed by `alignas`).
