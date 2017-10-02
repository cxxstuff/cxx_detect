// [CC_DETECT]
// C++ compiler and features detection.
//
// [License]
// Dual licensed under Public Domain and Zlib.
//   (choose the one that you prefer and is valid in your country)

// ----------------------------------------------------------------------------
// [License - Public Domain]
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// [License - Zlib]
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// ----------------------------------------------------------------------------

// ============================================================================
// [Guard]
// ============================================================================

#if !defined(CC_DETECT_H) || CC_DETECT_H < 20171010

#if defined(CC_DETECT_H)
# undef CC_DETECT_H
# define CC_DETECT_H_CLEANUP
#endif
#define CC_DETECT_H 20171010

// ============================================================================
// [Cleanup]
// ============================================================================

#if defined(CC_DETECT_H_CLEANUP)
# undef CC_DETECT_H_CLEANUP

// C/C++ Compiler vendor and vendor details
# undef CC_CLANG
# undef CC_GNU
# undef CC_INTEL
# undef CC_INTEL_COMPAT_MODE
# undef CC_MSC
# undef CC_MINGW
# undef CC_MAKE_VER

// C++ language version.
# undef CC_CPLUSPLUS

// C/C++ compiler features.
# undef CC_HAS_ALIGNAS
# undef CC_HAS_ALIGNOF
# undef CC_HAS_ATTRIBUTE
# undef CC_HAS_ATTRIBUTE_ALIGNED
# undef CC_HAS_ATTRIBUTE_ALWAYS_INLINE
# undef CC_HAS_ATTRIBUTE_NOINLINE
# undef CC_HAS_ATTRIBUTE_NORETURN
# undef CC_HAS_ATTRIBUTE_OPTIMIZE
# undef CC_HAS_BUILTIN_ASSUME
# undef CC_HAS_BUILTIN_ASSUME_ALIGNED
# undef CC_HAS_BUILTIN_EXPECT
# undef CC_HAS_BUILTIN_UNREACHABLE
# undef CC_HAS_CONSTEXPR
# undef CC_HAS_DECLSPEC_ALIGN
# undef CC_HAS_DECLSPEC_NOINLINE
# undef CC_HAS_DECLSPEC_NORETURN
# undef CC_HAS_DECLTYPE
# undef CC_HAS_DEFAULTED_FUNCTIONS
# undef CC_HAS_DELETED_FUNCTIONS
# undef CC_HAS_FORCEINLINE
# undef CC_HAS_FINAL
# undef CC_HAS_INITIALIZER_LIST
# undef CC_HAS_LAMBDAS
# undef CC_HAS_NATIVE_CHAR
# undef CC_HAS_NATIVE_WCHAR_T
# undef CC_HAS_NATIVE_CHAR16_T
# undef CC_HAS_NATIVE_CHAR32_T
# undef CC_HAS_NOEXCEPT
# undef CC_HAS_NULLPTR
# undef CC_HAS_OVERRIDE
# undef CC_HAS_RVALUE_REFERENCES
# undef CC_HAS_STATIC_ASSERT
# undef CC_HAS_STRONG_ENUMS
# undef CC_HAS_VARIADIC_TEMPLATES

// Target architecture.
# undef CC_ARCH_X86
# undef CC_ARCH_X64
# undef CC_ARCH_ARM32
# undef CC_ARCH_ARM64
# undef CC_ARCH_BITS
# undef CC_ARCH_LE
# undef CC_ARCH_BE

// Target operating system.
# undef CC_OS_WINDOWS
# undef CC_OS_MAC
# undef CC_OS_IOS
# undef CC_OS_ANDROID
# undef CC_OS_LINUX
# undef CC_OS_NETBSD
# undef CC_OS_FREEBSD
# undef CC_OS_OPENBSD
# undef CC_OS_DRAGONFLYBSD
# undef CC_OS_QNX
# undef CC_OS_SOLARIS
# undef CC_OS_CYGWIN
# undef CC_OS_BSD

// Visibility.
# undef CC_EXPORT
# undef CC_IMPORT

// Calling convention.
# undef CC_CDECL
# undef CC_STDCALL
# undef CC_FASTCALL
# undef CC_REGPARM

// Likely / unlikely.
# undef CC_LIKELY
# undef CC_UNLIKELY

// Assumptions.
# undef CC_ASSUME
# undef CC_ASSUME_ALIGNED

// Other macros.
# undef CC_ALIGN_DECL
# undef CC_ALIGN_TYPE
# undef CC_FALLTHROUGH
# undef CC_FORCEINLINE
# undef CC_NOINLINE
# undef CC_NORETURN
# undef CC_UNUSED

# undef CC_ARRAY_SIZE
# undef CC_OFFSET_OF(STRUCT, MEMBER) ((size_t)((const char*)&((const STRUCT*)0x1)->MEMBER) - 1)

#endif

// ----------------------------------------------------------------------------
// [C++ Compiler Vendor]
// ----------------------------------------------------------------------------

#define CC_MAKE_VER(MAJOR, MINOR, PATCH) ((MAJOR) * 10000000 + (MINOR) * 100000 + (PATCH))

#define CC_CLANG    0
#define CC_GNU      0
#define CC_INTEL    0
#define CC_MSC      0

// Intel masquerades as GNU, so check it first.
#if defined(__INTEL_COMPILER)
# undef  CC_INTEL
# define CC_INTEL CC_MAKE_VER((__INTEL_COMPILER) / 100, __INTEL_COMPILER % 100, 0)
#elif defined(_MSC_VER) && defined(_MSC_FULL_VER)
# undef  CC_MSC
# if _MSC_VER == _MSC_FULL_VER / 10000
#  define CC_MSC CC_MAKE_VER(_MSC_VER / 100, _MSC_VER % 100, _MSC_FULL_VER % 10000)
# else
#  define CC_MSC CC_MAKE_VER(_MSC_VER / 100, (_MSC_FULL_VER / 100000) % 100, _MSC_FULL_VER % 100000)
# endif
#elif defined(__clang__) && defined(__clang_minor__)
# undef  CC_CLANG
# define CC_CLANG CC_MAKE_VER(__clang_major__, __clang_minor__, __clang_patchlevel__)
#elif defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
# undef  CC_GNU
# define CC_GNU CC_MAKE_VER(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# error "[cc-detect] Unable to detect C/C++ compiler."
#endif

// CC_MINGW - MINGW - 0 (no MINGW), 32 (MINGW32), 64 (MINGW64).
#if defined(__MINGW64__)
# define CC_MINGW 64
#elif defined(__MINGW32__)
# define CC_MINGW 32
#else
# define CC_MINGW 0
#endif

// CC_INTEL_COMPAT_MODE - C++ compiler is INTEL in GNU/Clang compatibility mode.
#if CC_INTEL && (defined(__GNUC__) || defined(__clang__))
# define CC_INTEL_COMPAT_MODE 1
#else
# define CC_INTEL_COMPAT_MODE 0
#endif

// ----------------------------------------------------------------------------
// [C++ Version]
// ----------------------------------------------------------------------------

#if defined(__cplusplus)
# if __cplusplus >= 201103L
#  define CC_CPLUSPLUS __cplusplus
# elif defined(__GXX_EXPERIMENTAL_CXX0X__) || CC_MSC >= CC_MAKE_VER(18, 0, 0) || CC_INTEL >= CC_MAKE_VER(14, 0, 0)
#  define CC_CPLUSPLUS 201103L
# else
#  define CC_CPLUSPLUS 199711L
# endif
#endif

#if !defined(CC_CPLUSPLUS)
# define CC_CPLUSPLUS 0
#endif

// ----------------------------------------------------------------------------
// [C++ Compiler Features]
// ----------------------------------------------------------------------------

#if CC_CLANG
# define CC_HAS_ALIGNAS                 (__has_extension(__cxx_alignas__))
# define CC_HAS_ALIGNOF                 (__has_extension(__cxx_alignof__))
# define CC_HAS_ASSUME                  (0)
# define CC_HAS_ASSUME_ALIGNED          (0)
# define CC_HAS_ATTRIBUTE               (1)
# define CC_HAS_ATTRIBUTE_ALIGNED       (__has_attribute(__aligned__))
# define CC_HAS_ATTRIBUTE_ALWAYS_INLINE (__has_attribute(__always_inline__))
# define CC_HAS_ATTRIBUTE_NOINLINE      (__has_attribute(__noinline__))
# define CC_HAS_ATTRIBUTE_NORETURN      (__has_attribute(__noreturn__))
# define CC_HAS_ATTRIBUTE_OPTIMIZE      (__has_attribute(__optimize__))
# define CC_HAS_BUILTIN_ASSUME          (__has_builtin(__builtin_assume))
# define CC_HAS_BUILTIN_ASSUME_ALIGNED  (__has_builtin(__builtin_assume_aligned))
# define CC_HAS_BUILTIN_EXPECT          (__has_builtin(__builtin_expect))
# define CC_HAS_BUILTIN_UNREACHABLE     (__has_builtin(__builtin_unreachable))
# define CC_HAS_CONSTEXPR               (__has_extension(__cxx_constexpr__))
# define CC_HAS_DECLSPEC_ALIGN          (0)
# define CC_HAS_DECLSPEC_NOINLINE       (0)
# define CC_HAS_DECLSPEC_NORETURN       (0)
# define CC_HAS_DECLTYPE                (__has_extension(__cxx_decltype__))
# define CC_HAS_DEFAULTED_FUNCTIONS     (__has_extension(__cxx_defaulted_functions__))
# define CC_HAS_DELETED_FUNCTIONS       (__has_extension(__cxx_deleted_functions__))
# define CC_HAS_FORCEINLINE             (0)
# define CC_HAS_FINAL                   (__has_extension(__cxx_override_control__))
# define CC_HAS_INITIALIZER_LIST        (__has_extension(__cxx_generalized_initializers__))
# define CC_HAS_LAMBDAS                 (__has_extension(__cxx_lambdas__))
# define CC_HAS_NATIVE_CHAR             (1)
# define CC_HAS_NATIVE_CHAR16_T         (__has_extension(__cxx_unicode_literals__))
# define CC_HAS_NATIVE_CHAR32_T         (__has_extension(__cxx_unicode_literals__))
# define CC_HAS_NATIVE_WCHAR_T          (1)
# define CC_HAS_NOEXCEPT                (__has_extension(__cxx_noexcept__))
# define CC_HAS_NULLPTR                 (__has_extension(__cxx_nullptr__))
# define CC_HAS_OVERRIDE                (__has_extension(__cxx_override_control__))
# define CC_HAS_RVALUE_REFERENCES       (__has_extension(__cxx_rvalue_references__))
# define CC_HAS_STATIC_ASSERT           (__has_extension(__cxx_static_assert__))
# define CC_HAS_STRONG_ENUMS            (__has_extension(__cxx_strong_enums__))
# define CC_HAS_VARIADIC_TEMPLATES      (__has_extension(__cxx_variadic_templates__))
#endif

#if CC_GNU
# define CC_HAS_ALIGNAS                 (CC_GNU >= CC_MAKE_VER(4, 8, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_ALIGNOF                 (CC_GNU >= CC_MAKE_VER(4, 8, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_ASSUME                  (0)
# define CC_HAS_ASSUME_ALIGNED          (0)
# define CC_HAS_ATTRIBUTE               (1)
# define CC_HAS_ATTRIBUTE_ALIGNED       (CC_GNU >= CC_MAKE_VER(2, 7, 0))
# define CC_HAS_ATTRIBUTE_ALWAYS_INLINE (CC_GNU >= CC_MAKE_VER(4, 4, 0) && !CC_MINGW)
# define CC_HAS_ATTRIBUTE_NOINLINE      (CC_GNU >= CC_MAKE_VER(3, 4, 0) && !CC_MINGW)
# define CC_HAS_ATTRIBUTE_NORETURN      (CC_GNU >= CC_MAKE_VER(2, 5, 0))
# define CC_HAS_ATTRIBUTE_OPTIMIZE      (CC_GNU >= CC_MAKE_VER(4, 4, 0))
# define CC_HAS_BUILTIN_ASSUME          (0)
# define CC_HAS_BUILTIN_ASSUME_ALIGNED  (CC_GNU >= CC_MAKE_VER(4, 7, 0))
# define CC_HAS_BUILTIN_EXPECT          (1)
# define CC_HAS_BUILTIN_UNREACHABLE     (CC_GNU >= CC_MAKE_VER(4, 5, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_CONSTEXPR               (CC_GNU >= CC_MAKE_VER(4, 6, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_DECLSPEC_ALIGN          (0)
# define CC_HAS_DECLSPEC_NOINLINE       (0)
# define CC_HAS_DECLSPEC_NORETURN       (0)
# define CC_HAS_DECLTYPE                (CC_GNU >= CC_MAKE_VER(4, 3, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_DEFAULTED_FUNCTIONS     (CC_GNU >= CC_MAKE_VER(4, 4, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_DELETED_FUNCTIONS       (CC_GNU >= CC_MAKE_VER(4, 4, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_FORCEINLINE             (0)
# define CC_HAS_FINAL                   (CC_GNU >= CC_MAKE_VER(4, 7, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_INITIALIZER_LIST        (CC_GNU >= CC_MAKE_VER(4, 4, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_LAMBDAS                 (CC_GNU >= CC_MAKE_VER(4, 5, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_NATIVE_CHAR             (1)
# define CC_HAS_NATIVE_CHAR16_T         (CC_GNU >= CC_MAKE_VER(4, 5, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_NATIVE_CHAR32_T         (CC_GNU >= CC_MAKE_VER(4, 5, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_NATIVE_WCHAR_T          (1)
# define CC_HAS_NOEXCEPT                (CC_GNU >= CC_MAKE_VER(4, 6, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_NULLPTR                 (CC_GNU >= CC_MAKE_VER(4, 6, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_OVERRIDE                (CC_GNU >= CC_MAKE_VER(4, 7, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_RVALUE_REFERENCES       (CC_GNU >= CC_MAKE_VER(4, 3, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_STATIC_ASSERT           (CC_GNU >= CC_MAKE_VER(4, 3, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_STRONG_ENUMS            (CC_GNU >= CC_MAKE_VER(4, 4, 0) && CC_CPLUSPLUS >= 201103L)
# define CC_HAS_VARIADIC_TEMPLATES      (CC_GNU >= CC_MAKE_VER(4, 3, 0) && CC_CPLUSPLUS >= 201103L)
#endif

#if CC_INTEL
# define CC_HAS_ALIGNAS                 (CC_INTEL >= CC_MAKE_VER(15, 0, 0)
# define CC_HAS_ALIGNOF                 (CC_INTEL >= CC_MAKE_VER(15, 0, 0))
# define CC_HAS_ASSUME                  (1)
# define CC_HAS_ASSUME_ALIGNED          (1)
# define CC_HAS_ATTRIBUTE               (CC_INTEL_COMPAT_MODE)
# define CC_HAS_ATTRIBUTE_ALIGNED       (CC_INTEL_COMPAT_MODE)
# define CC_HAS_ATTRIBUTE_ALWAYS_INLINE (CC_INTEL_COMPAT_MODE)
# define CC_HAS_ATTRIBUTE_NOINLINE      (CC_INTEL_COMPAT_MODE)
# define CC_HAS_ATTRIBUTE_NORETURN      (CC_INTEL_COMPAT_MODE)
# define CC_HAS_ATTRIBUTE_OPTIMIZE      (CC_INTEL_COMPAT_MODE)
# define CC_HAS_BUILTIN_ASSUME          (0)
# define CC_HAS_BUILTIN_ASSUME_ALIGNED  (0)
# define CC_HAS_BUILTIN_EXPECT          (CC_INTEL_COMPAT_MODE)
# define CC_HAS_BUILTIN_UNREACHABLE     (0)
# define CC_HAS_CONSTEXPR               (CC_INTEL >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_DECLSPEC_ALIGN          (CC_INTEL_COMPAT_MODE == 0)
# define CC_HAS_DECLSPEC_NOINLINE       (CC_INTEL_COMPAT_MODE == 0)
# define CC_HAS_DECLSPEC_NORETURN       (CC_INTEL_COMPAT_MODE == 0)
# define CC_HAS_DECLTYPE                (CC_INTEL >= CC_MAKE_VER(12, 0, 0))
# define CC_HAS_DEFAULTED_FUNCTIONS     (CC_INTEL >= CC_MAKE_VER(12, 0, 0))
# define CC_HAS_DELETED_FUNCTIONS       (CC_INTEL >= CC_MAKE_VER(12, 0, 0))
# define CC_HAS_FORCEINLINE             (CC_INTEL_COMPAT_MODE == 0)
# define CC_HAS_FINAL                   (CC_INTEL >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_INITIALIZER_LIST        (CC_INTEL >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_LAMBDAS                 (CC_INTEL >= CC_MAKE_VER(12, 0, 0))
# define CC_HAS_NATIVE_CHAR             (1)
# define CC_HAS_NATIVE_CHAR16_T         (CC_INTEL >= CC_MAKE_VER(14, 0, 0) || (CC_INTEL_COMPAT_MODE > 0 && CC_INTEL >= CC_MAKE_VER(12, 6, 0)))
# define CC_HAS_NATIVE_CHAR32_T         (CC_INTEL >= CC_MAKE_VER(14, 0, 0) || (CC_INTEL_COMPAT_MODE > 0 && CC_INTEL >= CC_MAKE_VER(12, 6, 0)))
# define CC_HAS_NATIVE_WCHAR_T          (1)
# define CC_HAS_NOEXCEPT                (CC_INTEL >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_NULLPTR                 (CC_INTEL >= CC_MAKE_VER(12, 6, 0))
# define CC_HAS_OVERRIDE                (CC_INTEL >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_RVALUE_REFERENCES       (CC_INTEL >= CC_MAKE_VER(11,10, 0))
# define CC_HAS_STATIC_ASSERT           (CC_INTEL >= CC_MAKE_VER(11,10, 0))
# define CC_HAS_STRONG_ENUMS            (CC_INTEL >= CC_MAKE_VER(13, 0, 0))
# define CC_HAS_VARIADIC_TEMPLATES      (CC_INTEL >= CC_MAKE_VER(12, 6, 0))
#endif

#if CC_MSC
# define CC_HAS_ALIGNAS                 (CC_MSC >= CC_MAKE_VER(19, 0, 0))
# define CC_HAS_ALIGNOF                 (CC_MSC >= CC_MAKE_VER(19, 0, 0))
# define CC_HAS_ASSUME                  (1)
# define CC_HAS_ASSUME_ALIGNED          (0)
# define CC_HAS_ATTRIBUTE               (0)
# define CC_HAS_ATTRIBUTE_ALIGNED       (0)
# define CC_HAS_ATTRIBUTE_ALWAYS_INLINE (0)
# define CC_HAS_ATTRIBUTE_NOINLINE      (0)
# define CC_HAS_ATTRIBUTE_NORETURN      (0)
# define CC_HAS_ATTRIBUTE_OPTIMIZE      (0)
# define CC_HAS_BUILTIN_ASSUME          (0)
# define CC_HAS_BUILTIN_ASSUME_ALIGNED  (0)
# define CC_HAS_BUILTIN_EXPECT          (0)
# define CC_HAS_BUILTIN_UNREACHABLE     (0)
# define CC_HAS_CONSTEXPR               (CC_MSC >= CC_MAKE_VER(19, 0, 0))
# define CC_HAS_DECLSPEC_ALIGN          (1)
# define CC_HAS_DECLSPEC_NOINLINE       (1)
# define CC_HAS_DECLSPEC_NORETURN       (1)
# define CC_HAS_DECLTYPE                (CC_MSC >= CC_MAKE_VER(16, 0, 0))
# define CC_HAS_DEFAULTED_FUNCTIONS     (CC_MSC >= CC_MAKE_VER(18, 0, 0))
# define CC_HAS_DELETED_FUNCTIONS       (CC_MSC >= CC_MAKE_VER(18, 0, 0))
# define CC_HAS_FORCEINLINE             (1)
# define CC_HAS_FINAL                   (CC_MSC >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_INITIALIZER_LIST        (CC_MSC >= CC_MAKE_VER(18, 0, 0))
# define CC_HAS_LAMBDAS                 (CC_MSC >= CC_MAKE_VER(16, 0, 0))
# define CC_HAS_NATIVE_CHAR             (1)
# define CC_HAS_NATIVE_CHAR16_T         (CC_MSC >= CC_MAKE_VER(19, 0, 0))
# define CC_HAS_NATIVE_CHAR32_T         (CC_MSC >= CC_MAKE_VER(19, 0, 0))
# if defined(_NATIVE_WCHAR_T_DEFINED)
#  define CC_HAS_NATIVE_WCHAR_T         (1)
# else
#  define CC_HAS_NATIVE_WCHAR_T         (0)
# endif
# define CC_HAS_NOEXCEPT                (CC_MSC >= CC_MAKE_VER(19, 0, 0))
# define CC_HAS_NULLPTR                 (CC_MSC >= CC_MAKE_VER(16, 0, 0))
# define CC_HAS_OVERRIDE                (CC_MSC >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_RVALUE_REFERENCES       (CC_MSC >= CC_MAKE_VER(16, 0, 0))
# define CC_HAS_STATIC_ASSERT           (CC_MSC >= CC_MAKE_VER(16, 0, 0))
# define CC_HAS_STRONG_ENUMS            (CC_MSC >= CC_MAKE_VER(14, 0, 0))
# define CC_HAS_VARIADIC_TEMPLATES      (CC_MSC >= CC_MAKE_VER(18, 0, 0))
#endif

// ----------------------------------------------------------------------------
// [Target CPU Architecture]
// ----------------------------------------------------------------------------

#if (defined(_M_X64  ) || defined(__x86_64) || defined(__x86_64__) || \
     defined(_M_AMD64) || defined(__amd64 ) || defined(__amd64__ ))
# define CC_ARCH_X64        (1)
#else
# define CC_ARCH_X64        (0)
#endif

#if (defined(_M_IX86 ) || defined(__X86__ ) || defined(__i386  ) || \
     defined(__IA32__) || defined(__I86__ ) || defined(__i386__) || \
     defined(__i486__) || defined(__i586__) || defined(__i686__))
# define CC_ARCH_X86        (!CC_ARCH_X64)
#else
# define CC_ARCH_X86        (0)
#endif

#if defined(__aarch64__)
# define CC_ARCH_ARM64      (1)
#else
# define CC_ARCH_ARM64      (0)
#endif

#if (defined(_M_ARM  ) || defined(__arm    ) || defined(__thumb__ ) || \
     defined(_M_ARMT ) || defined(__arm__  ) || defined(__thumb2__))
# define CC_ARCH_ARM32      (!CC_ARCH_ARM64)
#else
# define CC_ARCH_ARM32      (0)
#endif

#if CC_ARCH_X64 || CC_ARCH_ARM64
# define CC_ARCH_BITS       (64)
#else
# define CC_ARCH_BITS       (32)
#endif

#define CC_ARCH_LE          (CC_ARCH_X86 || CC_ARCH_X64 || CC_ARCH_ARM32 || CC_ARCH_ARM64)
#define CC_ARCH_BE          (!(CC_ARCH_LE))

// ----------------------------------------------------------------------------
// [Target Operating System]
// ----------------------------------------------------------------------------

#if defined(_WIN32) || defined(_WINDOWS)
# define CC_OS_WINDOWS      (1)
#else
# define CC_OS_WINDOWS      (0)
#endif

#if defined(__APPLE__)
# include <TargetConditionals.h>
# define CC_OS_MAC          (TARGET_OS_MAC)
# define CC_OS_IOS          (TARGET_OS_IPHONE)
#else
# define CC_OS_MAC          (0)
# define CC_OS_IOS          (0)
#endif

#if defined(__ANDROID__)
# define CC_OS_ANDROID      (1)
#else
# define CC_OS_ANDROID      (0)
#endif

#if defined(__linux__) || defined(__ANDROID__)
# define CC_OS_LINUX        (1)
#else
# define CC_OS_LINUX        (0)
#endif

#if defined(__NetBSD__)
# define CC_OS_NETBSD       (1)
#else
# define CC_OS_NETBSD       (0)
#endif

#if defined(__FreeBSD__)
# define CC_OS_FREEBSD      (1)
#else
# define CC_OS_FREEBSD      (0)
#endif

#if defined(__OpenBSD__)
# define CC_OS_OPENBSD      (1)
#else
# define CC_OS_OPENBSD      (0)
#endif

#if defined(__DragonFly__)
# define CC_OS_DRAGONFLYBSD (1)
#else
# define CC_OS_DRAGONFLYBSD (0)
#endif

#if defined(__QNXNTO__)
# define CC_OS_QNX          (1)
#else
# define CC_OS_QNX          (0)
#endif

#if defined(__sun)
# define CC_OS_SOLARIS      (1)
#else
# define CC_OS_SOLARIS      (0)
#endif

#if defined(__CYGWIN__)
# define CC_OS_CYGWIN       (1)
#else
# define CC_OS_CYGWIN       (0)
#endif

#define CC_OS_BSD           (CC_OS_FREEBSD || CC_OS_DRAGONFLYBSD  || CC_OS_NETBSD || CC_OS_OPENBSD || CC_OS_MAC)

// ----------------------------------------------------------------------------
// [Visibility - Export|Import]
// ----------------------------------------------------------------------------

#if CC_OS_WINDOWS
# if (CC_GNU || CC_CLANG) && !CC_MINGW
#  define CC_EXPORT __attribute__((__dllexport__))
#  define CC_IMPORT __attribute__((__dllimport__))
# else
#  define CC_EXPORT __declspec(dllexport)
#  define CC_IMPORT __declspec(dllimport)
# endif
#else
# if CC_CLANG || CC_GNU >= CC_MAKE_VER(4, 0, 0) || CC_INTEL_COMPAT_MODE
#  define CC_EXPORT __attribute__((__visibility__("default")))
#  define CC_IMPORT
# else
#  define CC_EXPORT
#  define CC_IMPORT
# endif
#endif

// ----------------------------------------------------------------------------
// [Function Attributes & Calling Conventions]
// ----------------------------------------------------------------------------

#if CC_ARCH_X86
# if CC_HAS_ATTRIBUTE
#  define CC_CDECL      __attribute__((__cdecl__))
#  define CC_STDCALL    __attribute__((__stdcall__))
#  define CC_FASTCALL   __attribute__((__fastcall__))
#  define CC_REGPARM(N) __attribute__((__regparm__(N)))
# else
#  define CC_CDECL      __cdecl
#  define CC_STDCALL    __stdcall
#  define CC_FASTCALL   __fastcall
#  define CC_REGPARM(N)
# endif
#else
# define CC_CDECL
# define CC_STDCALL
# define CC_FASTCALL
# define CC_REGPARM(N)
#endif

#if CC_HAS_ATTRIBUTE_ALWAYS_INLINE
# define CC_FORCEINLINE inline __attribute__((__always_inline__))
#elif CC_HAS_FORCEINLINE
# define CC_FORCEINLINE __forceinline
#else
# define CC_FORCEINLINE inline
#endif

#if CC_HAS_ATTRIBUTE_NOINLINE
# define CC_NOINLINE __attribute__((__noinline__))
#elif CC_HAS_DECLSPEC_NOINLINE
# define CC_NOINLINE __declspec(noinline)
#else
# define CC_NOINLINE
#endif

#if CC_HAS_ATTRIBUTE_NORETURN
# define CC_NORETURN __attribute__((__noreturn__))
#elif CC_HAS_DECLSPEC_NORETURN
# define CC_NORETURN __declspec(noreturn)
#else
# define CC_NORETURN
#endif


// ----------------------------------------------------------------------------
// [Likely | Unlikely]
// ----------------------------------------------------------------------------

#if CC_HAS_BUILTIN_EXPECT
# define CC_LIKELY(EXP) __builtin_expect(!!(EXP), 1)
# define CC_UNLIKELY(EXP) __builtin_expect(!!(EXP), 0)
#else
# define CC_LIKELY(EXP) (EXP)
# define CC_UNLIKELY(EXP) (EXP)
#endif

// ----------------------------------------------------------------------------
// [CC_ALIGN]
// ----------------------------------------------------------------------------

#if CC_HAS_DECLSPEC_ALIGN
# define CC_ALIGN_TYPE(TYPE, N_ALIGN) __declspec(align(N_ALIGN)) TYPE
# define CC_ALIGN_DECL(TYPE, VARIABLE, N_ALIGN) __declspec(align(N_ALIGN)) TYPE VARIABLE
#elif CC_HAS_ATTRIBUTE_ALIGNED
# define CC_ALIGN_TYPE(TYPE, N_ALIGN) __attribute__((__aligned__(N_ALIGN))) TYPE
# define CC_ALIGN_DECL(TYPE, VARIABLE, N_ALIGN) TYPE __attribute__((__aligned__(N_ALIGN))) VARIABLE
#else
# define CC_ALIGN_TYPE(TYPE, N_ALIGN) TYPE
# define CC_ALIGN_DECL(TYPE, VARIABLE, N_ALIGN) TYPE VARIABLE
#endif

// ----------------------------------------------------------------------------
// [Assumptions]
// ----------------------------------------------------------------------------

#if CC_HAS_ASSUME
# define CC_ASSUME(EXP) __assume(EXP)
#elif CC_HAS_BUILTIN_ASSUME
# define CC_ASSUME(EXP) __builtin_assume(EXP)
#elif CC_HAS_BUILTIN_UNREACHABLE
# define CC_ASSUME(EXP) do { if (!(EXP)) __builtin_unreachable(); } while (0)
#else
# define CC_ASSUME(EXP) ((void)0)
#endif

#if CC_HAS_ASSUME_ALIGNED
# define CC_ASSUME_ALIGNED(PTR, N_ALIGN) __assume_aligned(PTR, N_ALIGN)
#elif CC_HAS_BUILTIN_ASSUME_ALIGNED
# define CC_ASSUME_ALIGNED(PTR, N_ALIGN) PTR = __builtin_assume_aligned(PTR, N_ALIGN)
#else
# define CC_ASSUME_ALIGNED(PTR, N_ALIGN) ((void)0)
#endif

// ----------------------------------------------------------------------------
// [Annotations]
// ----------------------------------------------------------------------------

#define CC_UNUSED(X) (void)(X)

#if CC_CLANG && CC_CPLUSPLUS >= 201103L
# define CC_FALLTHROUGH [[clang::fallthrough]]
#elif CC_GNU >= CC_MAKE_VER(7, 0, 0)
# define CC_FALLTHROUGH __attribute__((__fallthrough__))
#else
# define CC_FALLTHROUGH (void)0 /* fallthrough */
#endif

// ----------------------------------------------------------------------------
// [Other General Purpose Macros]
// ----------------------------------------------------------------------------

#define CC_ARRAY_SIZE(X) (sizeof(X) / sizeof((X)[0]))
#define CC_OFFSET_OF(STRUCT, MEMBER) ((size_t)((const char*)&((const STRUCT*)0x1)->MEMBER) - 1)

// ============================================================================
// [Guard]
// ============================================================================

#endif
