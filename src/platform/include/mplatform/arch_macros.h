#ifndef MXC_PLATFORM_ARCH_MACROS_H
#define MXC_PLATFORM_ARCH_MACROS_H

#include "mcore/macros.h"

// defined as 1 if compiling for x86_64
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) ||           \
    defined(_M_AMD64)
#if !defined(_M_ARM64EC) // <- arm64, when compiled with /arm64ec, can emulate a subset of x64
#define MXC_ARCH_X86_64 1
#endif
#endif

//-----------------------------------------------------------------------------

namespace mxc::simd
{
// types to collect features
enum class SIMDSupport : unsigned
{
#if defined(MXC_ARCH_X86_64)
    // each of these flags are cumulative...
    sse2    = 0, // sse2 assumed
    sse3    = 0x0000'0001,
    ssse3   = 0x0000'0003,
    sse4_1  = 0x0000'0007,
    sse4_2  = 0x0000'000f,
    avx1    = 0x0000'001f,
    avx2    = 0x0000'003f, // avx doesn't include fma, so fma.cpp has to be compiled with -mavx -mfma
    avx512f = 0x0000'007f,

    // ...these are independent
    avx512bw = 0x0000'007f | 0x0000'0080,
    avx512cd = 0x0000'007f | 0x0000'0100,
    avx512dq = 0x0000'007f | 0x0000'0200,
    avx512vl = 0x0000'007f | 0x0000'0400,

    bmi1   = 0x8000'0000,
    f16c   = 0x4000'0000 | 0x0000'001f,
    fma3   = 0x2000'0000 | 0x0000'001f,
    popcnt = 0x1000'0000,
#endif // defined(MXC_ARCH_X86_64)

    invalid = 0xffff'ffff
};

extern SIMDSupport const g_SIMDSupport;

constexpr auto operator|(SIMDSupport a, SIMDSupport b) -> SIMDSupport
{
    return static_cast<SIMDSupport>(static_cast<unsigned>(a) |
                                    static_cast<unsigned>(b));
}

constexpr auto operator|=(SIMDSupport &out, SIMDSupport b) -> SIMDSupport &
{
    return (out = out | b);
}

constexpr auto operator&(SIMDSupport a, SIMDSupport b) -> SIMDSupport
{
    return static_cast<SIMDSupport>(static_cast<unsigned>(a) &
                                    static_cast<unsigned>(b));
}

constexpr auto nonZero(SIMDSupport a) -> bool
{
    return (static_cast<unsigned>(a) != 0);
}

constexpr auto checkSupport(SIMDSupport feature) -> bool
{
    return nonZero(feature & g_SIMDSupport);
}
} // namespace mxc::simd

//-----------------------------------------------------------------------------
// macros related to simd functions dispatch
#if defined(__GNUC__) || defined(__clang__)
#define MXC_SIMD_DISPATCHER_ATTRIB(dispatcher) __attribute__((ifunc(#dispatcher), hot))
#define MXC_SIMD_DISPATCH(function, ...) function(__VA_ARGS__)
#define MXC_SIMD_DISPATCHER_INIT() __builtin_cpu_init()
#define MXC_SIMD_SUPPORT(feature) __builtin_cpu_supports(#feature)
#else // Assumes MSVC
#define MXC_SIMD_DISPATCHER_ATTRIB(dispatcher)
#define MXC_SIMD_DISPATCH(function, ...) g_##function_func(__VA_ARGS__)
#define MXC_SIMD_DISPATCHER_INIT()
#define MXC_SIMD_SUPPORT(feature) ::mxc::simd::checkSupport(feature)
#endif // defined(__GNUC__) || defined(__clang__)

// macro defining the best calling convention available for the platform, with the given compiler, to handle SIMD
// registers
#if defined(MXC_ARCH_X86_64)
#if defined(_MSC_VER) || defined(__clang__)
#define MXC_VECTOR_ABI __vectorcall
#elif defined(__GNUC__) // there is a bug report for gcc not supporting vectorcall on x64
                        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=89485
#define MXC_VECTOR_ABI
#endif // mxc::core already emits an error if the compiler is not supported
#endif

#endif // MXC_PLATFORM_ARCH_MACROS_H
