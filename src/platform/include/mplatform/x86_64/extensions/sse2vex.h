#ifndef MXC_PLATFORM_X86_64_SSE2VEX_H
#define MXC_PLATFORM_X86_64_SSE2VEX_H

//
// compiled Twice to generate both sse2 legacy encoded and avx vex encoded 128 bit operations
// 

// Required compiler flags:
// -msse -msse2 -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args -mno-sse2avx
#include "common_types.h"
#include <cstdint>

// SSE1, SSE2 are assumed by default to be supported in all x86_64 platforms, following msvc convention

// even though we are using runtime dispatch, we need to compile time check of availability of intrinsics because gcc/clang remove them if the 
// appropriate compiler option is turned off
namespace mxc::platform::x86_64::sse2vex
{

// float vector[4]
MXC_VECTOR_ABI auto load_f(float const * MXC_RESTRICT farrAligned16) -> v128f;
MXC_VECTOR_ABI auto store_f(v128f v, float * MXC_RESTRICT out_farrAligned16) -> void;
MXC_VECTOR_ABI auto add_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto sub_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto mul_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto div_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto sqrt_f(v128f v) -> v128f;
MXC_VECTOR_ABI auto rsqrt_f(v128f v) -> v128f;
MXC_VECTOR_ABI auto rcp_f(v128f v) -> v128f;
MXC_VECTOR_ABI auto max_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto min_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto cmpeq_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto cmpneq_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto cmpge_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto cmpgt_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto cmplt_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto cmple_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto or_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto xor_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto and_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto andnot_f(v128f v0, v128f v1) -> v128f;

// double vector[2]
MXC_VECTOR_ABI auto load_d(double const * MXC_RESTRICT darrAligned16) -> v128d;
MXC_VECTOR_ABI auto store_d(v128d v, double * MXC_RESTRICT out_darrAligned16) -> void;
MXC_VECTOR_ABI auto add_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto sub_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto mul_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto div_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto sqrt_d(v128d v) -> v128d;
MXC_VECTOR_ABI auto max_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto min_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto cmpeq_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto cmpneq_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto cmpge_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto cmpgt_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto cmplt_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto cmple_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto or_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto xor_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto and_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto andnot_d(v128d v0, v128d v1) -> v128d;

// int8_t vector[16]
MXC_VECTOR_ABI auto load_i8(int8_t const * MXC_RESTRICT i8arrAligned16) -> v128i8;
MXC_VECTOR_ABI auto store_i8(v128i8 v, int8_t * MXC_RESTRICT out_i8arrAligned16) -> void;
MXC_VECTOR_ABI auto add_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto sub_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto or_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto xor_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto and_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto andnot_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto avg_u8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto cmpeq_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto cmplt_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto cmpgt_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto min_u8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto max_u8(v128i8 v0, v128i8 v1) -> v128i8;

// int16_t vector[8]
MXC_VECTOR_ABI auto load_i16(int16_t const * MXC_RESTRICT i16arrAligned16) -> v128i16;
MXC_VECTOR_ABI auto store_i16(v128i16 v, int16_t * MXC_RESTRICT out_i16arrAligned16) -> void;
MXC_VECTOR_ABI auto add_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto sub_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto or_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto xor_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto and_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto andnot_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto avg_u16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto cmpeq_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto cmplt_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto cmpgt_i16(v128i16 v0, v128i16 v1) -> v128i16;
MXC_VECTOR_ABI auto maddadjacent_i16(v128i16 v0, v128i16 v1) -> v128i32;
MXC_VECTOR_ABI auto sll_i16(v128i16 v, v128i16 u64_low) -> v128i16;
MXC_VECTOR_ABI auto slli_i16(v128i16 v, int32_t shiftAmount) -> v128i16;
MXC_VECTOR_ABI auto srl_i16(v128i16 v, v128i16 u64_low) -> v128i16;
MXC_VECTOR_ABI auto srli_i16(v128i16 v, int32_t shiftAmount) -> v128i16;

// int32_t vector[4]
MXC_VECTOR_ABI auto load_i32(int32_t const * MXC_RESTRICT i32arrAligned16) -> v128i32;
MXC_VECTOR_ABI auto store_i32(v128i32 v, int32_t * MXC_RESTRICT out_i32arrAligned16) -> void;
MXC_VECTOR_ABI auto add_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto sub_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto or_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto xor_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto and_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto andnot_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto cmpeq_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto cmplt_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto cmpgt_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto sll_i32(v128i32 v, v128i32 u64_low) -> v128i32;
MXC_VECTOR_ABI auto slli_i32(v128i32 v, int32_t shiftAmount) -> v128i32;
MXC_VECTOR_ABI auto srl_i32(v128i32 v, v128i32 u64_low) -> v128i32;
MXC_VECTOR_ABI auto srli_i32(v128i32 v, int32_t shiftAmount) -> v128i32;

// int64_t vector[2]
MXC_VECTOR_ABI auto load_i64(int64_t const * MXC_RESTRICT i64arrAligned16) -> v128i64;
MXC_VECTOR_ABI auto store_i64(v128i64 v, int64_t * MXC_RESTRICT out_i64arrAligned16) -> void;
MXC_VECTOR_ABI auto add_i64(v128i64 v0, v128i64 v1) -> v128i64;
MXC_VECTOR_ABI auto sub_i64(v128i64 v0, v128i64 v1) -> v128i64;
MXC_VECTOR_ABI auto or_i64(v128i64 v0, v128i64 v1) -> v128i64;
MXC_VECTOR_ABI auto xor_i64(v128i64 v0, v128i64 v1) -> v128i64;
MXC_VECTOR_ABI auto and_i64(v128i64 v0, v128i64 v1) -> v128i64;
MXC_VECTOR_ABI auto andnot_i64(v128i64 v0, v128i64 v1) -> v128i64;
MXC_VECTOR_ABI auto sll_i64(v128i64 v, v128i64 u64_low) -> v128i64;
MXC_VECTOR_ABI auto slli_i64(v128i64 v, int32_t shiftAmount) -> v128i64;
MXC_VECTOR_ABI auto srl_i64(v128i64 v, v128i64 u64_low) -> v128i64;
MXC_VECTOR_ABI auto srli_i64(v128i64 v, int32_t shiftAmount) -> v128i64;

} // namespace mxc::platform::x86_64

#endif // MXC_PLATFORM_X86_64_SSE2VEX_H
