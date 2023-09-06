#ifndef MXC_PLATFORM_X86_64_AVX_H
#define MXC_PLATFORM_X86_64_AVX_H

//
// In this file AVX operations with 256 bit operands are declared. 128 AVX operations are obtained by compiling sse2.cpp with VEX encoding options
//
//
//Instructions like square root and division don't benefit from AVX. On the other hand, additions, multiplications, etc., do.

// Required compiler flags:
// -mavx -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args -msse2avx
#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::avx
{

// float vector[8]
MXC_VECTOR_ABI auto load_f(float const * MXC_RESTRICT farrAligned32) -> v256f;
MXC_VECTOR_ABI auto store_f(v256f v, float * MXC_RESTRICT out_farrAligned32) -> void;
MXC_VECTOR_ABI auto add_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto sub_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto mul_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto div_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto sqrt_f(v256f v) -> v256f;
MXC_VECTOR_ABI auto rsqrt_f(v256f v) -> v256f;
MXC_VECTOR_ABI auto rcp_f(v256f v) -> v256f;
MXC_VECTOR_ABI auto max_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto min_f(v256f v0, v256f v1) -> v256f;
template <uint32_t opiu_low> 
MXC_VECTOR_ABI auto cmp_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto or_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto xor_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto and_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto andnot_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto round_f(v256f v0) -> v256f; // rounding mode set to nearest
MXC_VECTOR_ABI auto ceil_f(v256f v0) -> v256f;
MXC_VECTOR_ABI auto floor_f(v256f v0) -> v256f;
template <uint32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_f(v256f v) -> v256f;

// float vector[4]
template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto cmp_f(v128f v0, v128f v1) -> v128f;
template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_f(v128f v) -> v128f;
template <int32_t binaryFlag>
MXC_VECTOR_ABI auto extractf128_f(v256f v) -> v128f;

// double vector[4]
MXC_VECTOR_ABI auto load_d(double const * MXC_RESTRICT darrAligned32) -> v256d;
MXC_VECTOR_ABI auto store_d(v256d v, double * MXC_RESTRICT out_darrAligned32) -> void;
MXC_VECTOR_ABI auto add_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto sub_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto mul_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto div_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto sqrt_d(v256d v) -> v256d;
MXC_VECTOR_ABI auto max_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto min_d(v256d v0, v256d v1) -> v256d;
template <int32_t opi8_low>
MXC_VECTOR_ABI auto cmp_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto or_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto xor_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto and_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto andnot_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto round_d(v256d v0) -> v256d; // rounding mode set to nearest
MXC_VECTOR_ABI auto ceil_d(v256d v0) -> v256d;
MXC_VECTOR_ABI auto floor_d(v256d v0) -> v256d;
template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_d(v256d v) -> v256d;

// double vector[2]
template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto cmp_d(v128d v0, v128d v1) -> v128d;
template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_d(v128d v) -> v128d;
template <int32_t binaryFlag>
MXC_VECTOR_ABI auto extractf128_d(v256d v) -> v128d;

// int8_t vector[32]
MXC_VECTOR_ABI auto load_i8(int8_t const * MXC_RESTRICT i8arrAligned32) -> v256i8;
MXC_VECTOR_ABI auto store_i8(v256i8 v, int8_t * MXC_RESTRICT out_i8arrAligned32) -> void;

// int16_t vector[16]
MXC_VECTOR_ABI auto load_i16(int16_t const * MXC_RESTRICT i16arrAligned32) -> v256i16;
MXC_VECTOR_ABI auto store_i16(v256i16 v, int8_t * MXC_RESTRICT out_i16arrAligned32) -> void;

// int32_t vector[8]
MXC_VECTOR_ABI auto load_i32(int32_t const * MXC_RESTRICT i32arrAligned32) -> v256i32;
MXC_VECTOR_ABI auto store_i32(v256i32 v, int32_t * MXC_RESTRICT out_i32arrAligned32) -> void;

// int64_t vector[4]
MXC_VECTOR_ABI auto load_i64(int64_t const * MXC_RESTRICT i64arrAligned32) -> v256i64;
MXC_VECTOR_ABI auto store_i64(v256i64 v, int8_t * MXC_RESTRICT out_i64arrAligned32) -> void;

} // namespace mxc::platform::x86_64

#endif // MXC_PLATFORM_X86_64_AVX_H
