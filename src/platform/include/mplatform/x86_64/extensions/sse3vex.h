#ifndef MXC_PLATFORM_X86_64_SSE3VEX_H
#define MXC_PLATFORM_X86_64_SSE3VEX_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::sse3vex
{
// float vector[4]
MXC_VECTOR_ABI auto addsub_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto duplicateEven2Odd_f(v128f v) -> v128f;
MXC_VECTOR_ABI auto duplicateOdd2Even_f(v128f v) -> v128f;

// double vector[2]
MXC_VECTOR_ABI auto loadBoth_d(double const *MXC_RESTRICT dSingleAligned16) -> v128d;
MXC_VECTOR_ABI auto duplicateDouble_d(v128d v) -> v128d;
MXC_VECTOR_ABI auto addsub_d(v128d v0, v128d v1) -> v128d;
} // namespace mxc::platform::x86_64::sse3vex

#endif // MXC_PLATFORM_X86_64_SSE3VEX_H
