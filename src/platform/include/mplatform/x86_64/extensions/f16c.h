#ifndef MXC_PLATFORM_X86_64_F16C_H
#define MXC_PLATFORM_X86_64_F16C_H

#include "common_types.h"
#include <cstdint>

// Note: pre AVX-512 half floats are stored in integer vector types. This allows us to implement 
// in software half operations when platform doesn't support AVX-512
namespace mxc::platform::x86_64::f16c
{

// the lower lane contains the results and sources of float16s considered in conversion operations.
// The coercion one will follow MXCSR register rounding mode
MXC_VECTOR_ABI auto F32ToF16(v128f v) -> v128ix;    // _mm_cvtps_ph
MXC_VECTOR_ABI auto F32ToF16(v256f v) -> v128ix;    // _mm256_cvtps_ph
MXC_VECTOR_ABI auto F16ToF32(v128ix v) -> v128f;    // _mm_cvtph_ps
MXC_VECTOR_ABI auto F16ToF32_256(v128ix v) -> v256f;    // _mm256_cvtph_ps

} // namespace mxc::platform::x86_64::f16c

#endif // MXC_PLATFORM_X86_64_F16C_H
