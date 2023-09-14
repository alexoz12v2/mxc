#ifndef MXC_PLATFORM_X86_64_SSSE3VEX_H
#define MXC_PLATFORM_X86_64_SSSE3VEX_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::ssse3vex
{
// int8_t vector[16]
MXC_VECTOR_ABI auto abs_i8(v128i8 v) -> v128i8;

template <int32_t shift8_low>
    requires(shift8_low >= 0 && shift8_low < 256)
MXC_VECTOR_ABI auto concatAndShift_i8(v128i8 high, v128i8 low) -> v128i8;

// multiply 2 arrays of respectively uint8_t and int8_t in odd positions  -> A0 :: int16_t
// multiply 2 arrays of respectively uint8_t and int8_t in even positions -> A1 :: int16_t
// return A0 + A1 (horizontal addition)
MXC_VECTOR_ABI auto fma4EvenOdd_i8(v128i8 v0, v128i8 v1) -> v128i16; // ASSERT v0 >= 0

// if the high bit of the i-th element in v1 is set, then zero out the i-th result, otherwise
// set the i-th element to the j-th input element. Therefore the allowed numbers for v1 are
// 0x0000'0000 to 0x0000'000f, 0x8000'0000 to 0x8000'000f
MXC_VECTOR_ABI auto shuffle_i8(v128i8 v0, v128i8 v1) -> v128i8;

// takes 2 vectors vals and signs, and
// vals[i] == 0 -> 0
// vals[i] > 0  -> vals[i]
// vals[i] < 0  -> -vals[i]
MXC_VECTOR_ABI auto condNegate_i8(v128i8 vals, v128i8 signs) -> v128i8;

// int16_t vector[8]
MXC_VECTOR_ABI auto abs_i16(v128i16 v) -> v128i16;
MXC_VECTOR_ABI auto condNegate_i16(v128i16 vals, v128i16 signs) -> v128i16;

// (basically multiply, add 1, divide by 2.)
// (on x64) multiply int16_t producing int32_ts, truncate them to "int18"s, add 1, divide by 2
// TODO: find a better name
MXC_VECTOR_ABI auto mulDiv2_i16(v128i16 v0, v128i16 v1) -> v128i16;

// int32_t vector[4]
MXC_VECTOR_ABI auto abs_i32(v128i32 v) -> v128i32;
MXC_VECTOR_ABI auto condNegate_i32(v128i32 vals, v128i32 signs) -> v128i32;
} // namespace mxc::platform::x86_64::ssse3vex

#endif // MXC_PLATFORM_X86_64_SSSE3VEX_H
