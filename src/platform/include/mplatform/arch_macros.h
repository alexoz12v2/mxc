#ifndef MXC_PLATFORM_ARCH_MACROS_H
#define MXC_PLATFORM_ARCH_MACROS_H

#include "mcore/macros.h"

// defined as 1 if compiling for x86_64
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#  if !defined(_M_ARM64EC) // <- arm64, when compiled with /arm64ec, can emulate a subset of x64
#     define MXC_ARCH_X86_64 1
#  endif
#endif

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
#define MXC_SIMD_SUPPORT(feature) (nonZero(g_SIMDSupport & SIMDSupport::##feature))
#endif // defined(__GNUC__) || defined(__clang__)

// macro defining the best calling convention available for the platform, with the given compiler, to handle SIMD registers
#if defined(MXC_ARCH_X86_64)
	#if defined(_MSC_VER) || defined(__clang__)
	#define MXC_VECTOR_ABI __vectorcall
	#elif defined(__GNUC__) // there is a bug report for gcc not supporting vectorcall on x64 https://gcc.gnu.org/bugzilla/show_bug.cgi?id=89485
	#define MXC_VECTOR_ABI
	#endif // mxc::core already emits an error if the compiler is not supported
#endif

#endif // MXC_PLATFORM_ARCH_MACROS_H
