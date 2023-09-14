#ifndef MXC_PLATFORM_X86_64_SSE4_1VEX_H
#define MXC_PLATFORM_X86_64_SSE4_1VEX_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::sse4_1vex
{
// int8_t vector[16]
// variable version of choose_i16. Checks whether the mask's high bit is set (0x8000'0000)
MXC_VECTOR_ABI auto chooseVariable_i8(v128i8 v0, v128i8 v1, v128i8 mask) -> v128i8;

template <int32_t index>
    requires(index >= 0 && index < 16)
MXC_VECTOR_ABI auto extract_i8(v128i8 v) -> int8_t;

template <int32_t index>
    requires(index >= 0 && index < 16)
MXC_VECTOR_ABI auto insert_i8(v128i8 v, int8_t elem) -> v128i8;

MXC_VECTOR_ABI auto max_i8(v128i8 v0, v128i8 v1) -> v128i8;
MXC_VECTOR_ABI auto min_i8(v128i8 v0, v128i8 v1) -> v128i8;

// you select a quadruplet from the second vector with the lowest 2 bits
// you select 8 quadruplet from the first vector (imagine a 8 element-wide window) with the
// 		third bit (0 -> low ones, 1 -> high ones)
// then compute a 16-bit wide SAD (https://en.wikipedia.org/wiki/Sum_of_absolute_differences)
// 		for each resulting element
template <int32_t bits>
    requires((bits & 0x0000'0007) == 0)
MXC_VECTOR_ABI auto selectiveSAD_u8(v128u8 vSource, v128u8 vChoices) -> v128i16;

// int16_t vector[8]
// compose a new vector by choosing either the i-th element of v0 or i-th element of v1
// depending on the bit array (0 -> v0[i], 1 -> v1[i])
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_i16(v128i16 v0, v128i16 v1) -> v128i16;

MXC_VECTOR_ABI auto max_u16(v128u16 v0, v128u16 v1) -> v128u16;
MXC_VECTOR_ABI auto min_u16(v128u16 v0, v128u16 v1) -> v128u16;

// store in the first (last bits) element the horizontal minimum of the array, and store in
// the second element its index. the rest is zeroed out
MXC_VECTOR_ABI auto minpos_u16(v128u16 v0) -> v128u16;

// int32_t vector[4]
template <int32_t index>
    requires(index >= 0 && index < 4)
MXC_VECTOR_ABI auto extract_i32(v128i32 v) -> int32_t;

template <int32_t index>
    requires(index >= 0 && index < 4)
MXC_VECTOR_ABI auto insert_i32(v128i32 v, int32_t elem) -> v128i32;

MXC_VECTOR_ABI auto max_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto max_u32(v128u32 v0, v128u32 v1) -> v128u32;
MXC_VECTOR_ABI auto min_i32(v128i32 v0, v128i32 v1) -> v128i32;
MXC_VECTOR_ABI auto min_u32(v128u32 v0, v128u32 v1) -> v128u32;
MXC_VECTOR_ABI auto mulOdds_i32(v128i32 v0, v128i32 v1) -> v128i64;
MXC_VECTOR_ABI auto mul_i32(v128i32 v0, v128i32 v1) -> v128i32;

// int64_t vector[4]
// Note: if true, element is 0xffff'ffff'ffff'ffff
MXC_VECTOR_ABI auto cmpeq_i64(v128i64 v0, v128i64 v1) -> v128i64;

template <int32_t index>
    requires(index >= 0 && index < 2)
MXC_VECTOR_ABI auto insert_i64(v128i64 v, int64_t elem) -> v128i64;

template <int32_t index>
    requires(index >= 0 && index < 2)
MXC_VECTOR_ABI auto extract_i64(v128i64 v) -> int64_t;

// float vector[4]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_f(v128f v0, v128f v1) -> v128f;
MXC_VECTOR_ABI auto chooseVariable_f(v128f v0, v128f v1, v128f mask) -> v128f;
MXC_VECTOR_ABI auto ceil_f(v128f v) -> v128f;

// let bits8_low alias b <- xxxx'xxxx
// let sum <- b[4]*v0[0]*v1[0] + b[5]*v0[1]*v1[1] + b[6]*v0[2]*v1[2] + b[7]*v0[3]*v1[3]
// then res <- [ b[0]*sum, b[1]*sum, b[2]*sum, b[3]*sum ]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto conditionalDotProduct_f(v128f v0, v128f v1) -> v128f;

template <int32_t index>
    requires(index >= 0 && index < 4)
MXC_VECTOR_ABI auto extract_f(v128f v) -> float;

MXC_VECTOR_ABI auto floor_f(v128f v) -> v128f;

// let i = bits8_low & 0x0000'0030 as number
// let j = bits8_low & 0x0000'00c0 as number
// let b = bits8_low & 0x0000'000f as bit array
// let res = vSource; res[j] = vChoices[i]
// return [ b[0]*res[0], b[1]*res[1], b[2]*res[2], b[3]*res[3] ]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto chooseInsertMask_f(v128f vSource, v128f vChoices) -> v128f;

MXC_VECTOR_ABI auto round_f(v128f v) -> v128f;

// double vector[2]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_d(v128d v0, v128d v1) -> v128d;
MXC_VECTOR_ABI auto chooseVariable_d(v128d v0, v128d v1, v128d mask) -> v128d;
MXC_VECTOR_ABI auto ceil_d(v128d v) -> v128d;

template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto conditionalDotProduct_d(v128d v0, v128d v1) -> v128d;

MXC_VECTOR_ABI auto floor_d(v128d v) -> v128d;

MXC_VECTOR_ABI auto round_d(v128d v) -> v128d;

// integer conversion functions (take the max elements from lowest address that target
// type can store)
MXC_VECTOR_ABI auto i16Toi32(v128i16 v) -> v128i32;
MXC_VECTOR_ABI auto i16Toi64(v128i16 v) -> v128i64;
MXC_VECTOR_ABI auto i32Toi64(v128i32 v) -> v128i64;
MXC_VECTOR_ABI auto i8Toi16(v128i8 v) -> v128i16;
MXC_VECTOR_ABI auto i8Toi32(v128i8 v) -> v128i32;
MXC_VECTOR_ABI auto i8Toi64(v128i8 v) -> v128i64;
MXC_VECTOR_ABI auto u16Toi32(v128u16 v) -> v128i32;
MXC_VECTOR_ABI auto u16Toi64(v128u16 v) -> v128i64;
MXC_VECTOR_ABI auto u32Toi64(v128u32 v) -> v128i64;
MXC_VECTOR_ABI auto u8Toi16(v128u8 v) -> v128i16;
MXC_VECTOR_ABI auto u8Toi32(v128u8 v) -> v128i32;
MXC_VECTOR_ABI auto u8Toi64(v128u8 v) -> v128i64;
// result [ v0 v1 v2 v3 v0 v1 v2 v3 ] where vi is i-th clamped element from the parameter v
MXC_VECTOR_ABI auto i32Toi16clamp(v128i32 v0, v128i32 v1) -> v128i16;

// independent of integer type
MXC_VECTOR_ABI auto AndEqualsAllZero(v128ix v0, v128ix v1) -> bool;    // _mm_test_all_zeros
MXC_VECTOR_ABI auto notAndEqualsAllZero(v128ix v0, v128ix v1) -> bool; // _mm_testc_si128
} // namespace mxc::platform::x86_64::sse4_1vex

#endif // MXC_PLATFORM_X86_64_SSE4_1VEX_H
