#ifndef MXC_PLATFORM_X86_64_AVX_H
#define MXC_PLATFORM_X86_64_AVX_H

//
// In this file AVX operations with 256 bit operands are declared. 128 AVX operations
// are obtained by compiling sse2.cpp with VEX encoding options
//
// Instructions like square root and division don't benefit from AVX. On the other hand, 
// additions, multiplications, etc., do.
//
// Required compiler flags:
// -mavx -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args -msse2avx
//
#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::avx
{

MXC_VECTOR_ABI auto add_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto add_d(v256d v0, v256d v1) -> v256d;

MXC_VECTOR_ABI auto addsub_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto addsub_d(v256d v0, v256d v1) -> v256d;

MXC_VECTOR_ABI auto and_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto and_d(v256d v0, v256d v1) -> v256d;

MXC_VECTOR_ABI auto andnot_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto andnot_d(v256d v0, v256d v1) -> v256d;

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0) 
MXC_VECTOR_ABI auto choose_f(v256f v0, v256f v1) -> v256f;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0) 
MXC_VECTOR_ABI auto choose_d(v256f v0, v256f v1) -> v256f;

MXC_VECTOR_ABI auto chooseVariable_f(v256f v0, v256f v1, v256f mask) -> v256f;
MXC_VECTOR_ABI auto chooseVariable_d(v256d v0, v256d v1, v256d mask) -> v256d;

MXC_VECTOR_ABI auto loadfrom4_f(v128f const * MXC_RESTRICT farr4) -> v256f; // broadcast_ps
MXC_VECTOR_ABI auto loadfrom4_d(v128d const * MXC_RESTRICT darr4) -> v256d; // broadcast_pd

MXC_VECTOR_ABI auto toBits_f(v256f v) -> v256ix;        // _mm256_castps_si256
MXC_VECTOR_ABI auto toBits_d(v256d v) -> v256ix;        // _mm256_castpd_si256
MXC_VECTOR_ABI auto fromBits_f(v256f v) -> v256ix;      // _mm256_castsi256_ps
MXC_VECTOR_ABI auto fromBits_d(v256d v) -> v256ix;      // _mm256_castsi256_pd

MXC_VECTOR_ABI auto ceil_f(v256f v0) -> v256f;
MXC_VECTOR_ABI auto ceil_d(v256d v0) -> v256d;

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0) 
MXC_VECTOR_ABI auto cmp_f(v256f v0, v256f v1) -> v256f;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0) 
MXC_VECTOR_ABI auto cmp_f(v128f v0, v128f v1) -> v128f;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto cmp_d(v256d v0, v256d v1) -> v256d;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto cmp_d(v128d v0, v128d v1) -> v128d;

MXC_VECTOR_ABI auto div_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto div_d(v256d v0, v256d v1) -> v256d;

template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto extractf128_f(v256f v) -> v128f;
template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto extractf128_d(v256d v) -> v128d;
template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto extractf128_ix(v256ix v0) -> v128ix;

MXC_VECTOR_ABI auto load_f(float const *MXC_RESTRICT farrAligned32) -> v256f;
MXC_VECTOR_ABI auto load_d(double const *MXC_RESTRICT darrAligned32) -> v256d;
MXC_VECTOR_ABI auto load_i8(int8_t const *MXC_RESTRICT i8arrAligned32) -> v256i8;
MXC_VECTOR_ABI auto load_i16(int16_t const *MXC_RESTRICT i16arrAligned32) -> v256i16;
MXC_VECTOR_ABI auto load_i32(int32_t const *MXC_RESTRICT i32arrAligned32) -> v256i32;
MXC_VECTOR_ABI auto load_i64(int64_t const *MXC_RESTRICT i64arrAligned32) -> v256i64;

MXC_VECTOR_ABI auto maskload_f(float const *MXC_RESTRICT farrAligned16, v128ix vMask) -> v128f;
MXC_VECTOR_ABI auto maskload256_f(float const *MXC_RESTRICT farrAligned32, v256ix vMask) -> v256f; MXC_VECTOR_ABI auto maskload_d(double const *MXC_RESTRICT darrAligned16, v128ix vMask) -> v128d;
MXC_VECTOR_ABI auto maskload256_d(double const *MXC_RESTRICT darrAligned32, v256ix vMask) -> v256d;
MXC_VECTOR_ABI auto maskstore_f(v128f v, float *MXC_RESTRICT farrAligned16, v128ix mask) -> void;
MXC_VECTOR_ABI auto maskstore256_f(v256f v, float *MXC_RESTRICT arrAligned32, v256ix mask) -> void;
MXC_VECTOR_ABI auto maskstore_d(v128d v, float *MXC_RESTRICT darrAligned16, v128ix mask) -> void; 
MXC_VECTOR_ABI auto maskstore256_d(v256d v, double *MXC_RESTRICT arAligned32, v256ix mask) -> void;

MXC_VECTOR_ABI auto max_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto max_d(v256d v0, v256d v1) -> v256d;
MXC_VECTOR_ABI auto min_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto min_d(v256d v0, v256d v1) -> v256d;

// let ctrl alias b <- xxxx'xxxx
// let sum <- b[4]*v0[0]*v1[0] + b[5]*v0[1]*v1[1] + b[6]*v0[2]*v1[2] + b[7]*v0[3]*v1[3]
// then res <- [ b[0]*sum, b[1]*sum, b[2]*sum, b[3]*sum ]
// notice that ctrl controls the behaviour of a sigle lane of 4, not the whole 8-element vector
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto conditionalDotProduct_f(v256f v0, v256f v1) -> v256f;

MXC_VECTOR_ABI auto floor_f(v256f v0) -> v256f;
MXC_VECTOR_ABI auto floor_d(v256d v0) -> v256d;

template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto insertv128_f(v256f vSource, v128f vOperand) -> v256f; // _mm256_insertf128_ps
template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto insertv128_d(v256d vSource, v128d vOperand) -> v256d; // _mm256_insertf128_ps
template <int32_t lane> requires (lane == 0 || lane == 1)
                                                                       // _mm256_insertf128_si256
MXC_VECTOR_ABI auto insertv128_ix(v256ix vSource, v128ix vOperand) -> v256ix;

MXC_VECTOR_ABI auto copyEvens_d(v256d vSrc) -> v256d;     // _mm256_movedup_pd
MXC_VECTOR_ABI auto copyEvens_f(v256f vSrc) -> v256f;     // _mm256_moveldup_ps
MXC_VECTOR_ABI auto copyOdds_f(v256f vSrc) -> v256f;      // _mm256_movehdup_ps

// returns a 32-bit integer, whose bits are set in the positions mapped to indices of negative 
// values, therefore vmovmskp[sd] returns
//      - double: a 4-bit mask
//      - float:  a 8-bit mask
MXC_VECTOR_ABI auto negatives_d(v256d v) -> int32_t;     // _mm256_movemask_pd
MXC_VECTOR_ABI auto negatives_f(v256f v) -> int32_t;     // _mm256_movemask_ps

MXC_VECTOR_ABI auto mul_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto mul_d(v256d v0, v256d v1) -> v256d;

MXC_VECTOR_ABI auto or_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto or_d(v256d v0, v256d v1) -> v256d;

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto permute_f(v128f v) -> v128f;                // _mm_permute_ps
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto permute_f(v256f v) -> v256f;                // _mm256_permute_ps
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto permute_d(v128d v) -> v128d;                // _mm_permute_pd
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto permute_d(v256d v) -> v256d;                // _mm256_permute_pd

// Note: the "granularity" of control within each lane doesn't change in both double and float
// versions. You manipulate 128-bits lanes with each 2 bits of the control, selecting one of the 
// two lanes of one of the two vectors
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)    // _mm256_permute2f128_ps
MXC_VECTOR_ABI auto permutelanes_f(v256f v0, v256f v1) -> v256f;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)    // _mm256_permute2f128_pd
MXC_VECTOR_ABI auto permutelanes_d(v256d v0, v256d v1) -> v256d;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)    // _mm256_permute2f128_si256
MXC_VECTOR_ABI auto permutelanes_ix(v256ix v0, v256ix v1) -> v256ix;

// https://www.officedaytime.com/simd512e/simdimg/si.php?f=vpermilpd
// permute each of the first vector based on the second lowest bit of each element 
// (qword if double, ie bit 1, 65, ...; dword if float, ie bit 1, 33, ...)
MXC_VECTOR_ABI auto permilvar_f(v128f v, v128ix mask) -> v128f;
MXC_VECTOR_ABI auto permilvar_f(v256f v, v256ix mask) -> v256f;
MXC_VECTOR_ABI auto permilvar_d(v128d v, v128ix mask) -> v128d;
MXC_VECTOR_ABI auto permilvar_d(v256d v, v256ix mask) -> v256d;

MXC_VECTOR_ABI auto rcp_f(v256f v) -> v256f;

MXC_VECTOR_ABI auto round_f(v256f v0) -> v256f; // rounding mode set to nearest
MXC_VECTOR_ABI auto round_d(v256d v0) -> v256d; // rounding mode set to nearest

MXC_VECTOR_ABI auto rsqrt_f(v256f v) -> v256f;

MXC_VECTOR_ABI auto sub_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto sub_d(v256d v0, v256d v1) -> v256d;

// choose 2 elements from the i-th lane of v0, 2 elements from the i-th lane of v1, 
// and put them in the resulting lane of vRes: 
// (0) |  v1.lanei[bits76]  |  v1.lanei[bits54]  |  v0.lanei[bits32]  |  v0.lanei[bits10]  |
// (1) |              v1.lane0[bit1]             |               v0.lane0[bit0]            |
// (2) |              v1.lane1[bit3]             |               v0.lane1[bit2]            |
// shown respectively: 
//      - a lane obtained executing vshufps (the other has the same format) (line 0)
//      - both lanes obtained executing vshufpd (lines 1,2)
//  similiar to vpermilp[sd], which takes all its elements for a lane from a lane of a single input
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_f(v256f v0, v256f v1) -> v256f;
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_d(v256d v0, v256d v1) -> v256d;

MXC_VECTOR_ABI auto sqrt_f(v256f v) -> v256f;
MXC_VECTOR_ABI auto sqrt_d(v256d v) -> v256d;

MXC_VECTOR_ABI auto store_f(v256f v, float *MXC_RESTRICT out_farrAligned32) -> void;
MXC_VECTOR_ABI auto store_d(v256d v, double *MXC_RESTRICT out_darrAligned32) -> void;
MXC_VECTOR_ABI auto store_i8(v256i8 v, int8_t *MXC_RESTRICT out_i8arrAligned32) -> void;
MXC_VECTOR_ABI auto store_i16(v256i16 v, int8_t *MXC_RESTRICT out_i16arrAligned32) -> void;
MXC_VECTOR_ABI auto store_i32(v256i32 v, int32_t *MXC_RESTRICT out_i32arrAligned32) -> void;
MXC_VECTOR_ABI auto store_i64(v256i64 v, int8_t *MXC_RESTRICT out_i64arrAligned32) -> void;

// from x86 docs
// "TESTPS performs a bitwise comparison of all the sign bits of the packed single-precision 
// elements in the first source operation and corresponding sign bits in the second source operand.
// If the AND of the source sign bits with the dest sign bits produces all zeros, the ZF is 
// set else the ZF is clear. If the AND of the source sign bits with the inverted dest sign bits 
// produces all zeros the CF is set else the CF is clear"
// This means it can be used to test if two vector components have same sign components
MXC_VECTOR_ABI auto vtestsignCF_f(v128f v0, v128f v1) -> bool;  // _mm_testc_ps
MXC_VECTOR_ABI auto vtestsignCF_f(v256f v0, v256f v1) -> bool;  // _mm256_testc_ps
MXC_VECTOR_ABI auto vtestsignCF_d(v128d v0, v128d v1) -> bool;  // _mm_testc_ps
MXC_VECTOR_ABI auto vtestsignCF_d(v256d v0, v256d v1) -> bool;  // _mm256_testc_ps
MXC_VECTOR_ABI auto vtestsignZF_f(v128f v0, v128f v1) -> bool;  // _mm_testz_ps
MXC_VECTOR_ABI auto vtestsignZF_f(v256f v0, v256f v1) -> bool;  // _mm256_testz_ps
MXC_VECTOR_ABI auto vtestsignZF_d(v128d v0, v128d v1) -> bool;  // _mm_testz_ps
MXC_VECTOR_ABI auto vtestsignZF_d(v256d v0, v256d v1) -> bool;  // _mm256_testz_ps

// unpack and interleave from the high half of each lane
//     each lane of the resulting vector will contain 
//     double: the higher element of the corresponding lane from each input vector
//     float: |  v1.lane0[3]  |  v0.lane0[3]  |  v1.lane0[2]  |  v0.lane0[2]  |
//     double:|          v1.lane0[1]          |          v0.lane0[1]          |
//            (same for the other lane)
// unpack and interleave from the low half of each line
//     each lane of the resulting vector will contain 
//     double: the higher element of the corresponding lane from each input vector
//     float: |  v1.lane0[1]  |  v0.lane0[1]  |  v1.lane0[0]  |  v0.lane0[0]  |
//     double:|          v1.lane0[0]          |          v0.lane0[0]          |
//            (same for the other lane)
MXC_VECTOR_ABI auto vunpckh_f(v256f v0, v256f v1) -> v256f;     // _mm256_unpackhi_ps
MXC_VECTOR_ABI auto vunpckh_d(v256d v0, v256d v1) -> v256d;     // _mm256_unpackhi_pd
MXC_VECTOR_ABI auto vunpckl_f(v256f v0, v256f v1) -> v256f;     // _mm256_unpacklo_ps
MXC_VECTOR_ABI auto vunpckl_d(v256d v0, v256d v1) -> v256d;     // _mm256_unpacklo_pd

MXC_VECTOR_ABI auto xor_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto xor_d(v256d v0, v256d v1) -> v256d;
} // namespace mxc::platform::x86_64::avx

#endif // MXC_PLATFORM_X86_64_AVX_H
