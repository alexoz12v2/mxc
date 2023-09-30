#ifndef MXC_PLATFORM_X86_64_FMA3_H
#define MXC_PLATFORM_X86_64_FMA3_H
// fma3.cpp <- vex encoded <- requires and assumes at least avx.
//
// Required compiler flags:
// -mavx -mfma -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args
//

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::fma3
{

MXC_VECTOR_ABI auto fmadd_f(v128f a, v128f b, v128f c) -> v128f;
MXC_VECTOR_ABI auto fmadd_f(v256f a, v256f b, v256f c) -> v256f;
MXC_VECTOR_ABI auto fmadd_d(v128d a, v128d b, v128d c) -> v128d;
MXC_VECTOR_ABI auto fmadd_d(v256d a, v256d b, v256d c) -> v256d;

} // namespace mxc::platform::x86_64::fma3

#endif // MXC_PLATFORM_X86_64_FMA3_H
