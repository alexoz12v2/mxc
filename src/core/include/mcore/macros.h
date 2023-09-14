#ifndef MXC_CORE_MACROS_H
#define MXC_CORE_MACROS_H

// force function inlining https://gcc.gnu.org/onlinedocs/gcc/Inline.html
#if defined(_MSC_VER)
#define MMATH_FORCE_INLINE __forceinline
#define MXC_INLINE __forceinline
#define MXC_FORCEINLINE __forceinline
#define MXC_RESTRICT __declspec(restrict)
#elif defined(__GNUC__) || defined(__clang__)
#define MMATH_FORCE_INLINE __attribute__((always_inline))
#define MXC_INLINE __attribute__((always_inline))
#define MXC_FORCEINLINE __attribute__((always_inline))
#define MXC_RESTRICT __restrict
#else
#error "OS/compiler not supported"
#endif

#endif // MXC_CORE_MACROS_H
