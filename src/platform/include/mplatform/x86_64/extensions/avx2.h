#ifndef MXC_PLATFORM_X86_64_AVX2_H
#define MXC_PLATFORM_X86_64_AVX2_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::avx2
{

tag MXC_VECTOR_ABI auto abs_i8(v256i8 v) -> v256i8;                          // _mm256_abs_epi8
tag MXC_VECTOR_ABI auto abs_i16(v256i16 v) -> v256i16;                       // _mm256_abs_epi16
tag MXC_VECTOR_ABI auto abs_i32(v256i32 v) -> v256i32;                       // _mm256_abs_epi32

tag MXC_VECTOR_ABI auto add_i8(v256i8 v0, v256i8 v1) -> v256i8;              // _mm256_add_epi8
tag MXC_VECTOR_ABI auto add_i16(v256i16 v0, v256i16 v1) -> v256i16;          // _mm256_add_epi16
tag MXC_VECTOR_ABI auto add_i32(v256i32 v0, v256i32 v1) -> v256i32;          // _mm256_add_epi32

tag MXC_VECTOR_ABI auto addClamp_u8(v256u8 v0, v256u8 v1) -> v256u8;         // _mm256_adds_epu8
tag MXC_VECTOR_ABI auto addClamp_u16(v256u16 v0, v256u16 v1) -> v256u16;     // _mm256_adds_epu16
tag MXC_VECTOR_ABI auto addClamp_u32(v256u32 v0, v256u32 v1) -> v256u32;     // _mm256_adds_epu32

// concatenate 2 lanes from v0 and v1, shift them right by ctrl bytes. Repeat for the second lane
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
tag MXC_VECTOR_ABI auto catLanesShr_ix(v256ix vHigh, v256ix vLow) -> v256ix; // _mm256_alignr_epi8

tag MXC_VECTOR_ABI auto and_ix(v256ix v0, v256ix v1) -> v256ix;              // _mm256_and_si256

tag MXC_VECTOR_ABI auto andnot_ix(v256ix v0, v256ix v1) -> v256ix;           // _mm256_andnot_si256

tag MXC_VECTOR_ABI auto avg_u8(v256u8 v0, v256u8 v1) -> v256u8;              // _mm256_avg_epu8
tag MXC_VECTOR_ABI auto avg_u16(v256u16 v0, v256u16 v1) -> v256u16;          // _mm256_avg_epu16

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
tag MXC_VECTOR_ABI auto choose_i16(v256i16 v0, v256i16 v1) -> v256i16;       // _mm256_blend_epi16
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
tag MXC_VECTOR_ABI auto choose_i32(v128i32 v0, v128i32 v1) -> v128i32;       // _mm_blend_epi32
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
tag MXC_VECTOR_ABI auto choose_i32(v256i32 v0, v256i32 v1) -> v256i32;       // _mm256_blend_epi32

// _mm256_blendv_epi8
MXC_VECTOR_ABI auto chooseVariable_i8(v256i8 v0, v256i8 v1, v256ix mask) -> v256i8;

// broadcast = produce a vector containing copies of the first (low) element
//             from a source vector
tag MXC_VECTOR_ABI auto broadcast_i8(v256i8 vSrc) -> v256i8;		// _mm256_broadcastb_epi8
tag MXC_VECTOR_ABI auto broadcast_i16(v256i16 vSrc) -> v256i16;		// _mm256_broadcastw_epi16
tag MXC_VECTOR_ABI auto broadcast_i32(v256i32 vSrc) -> v256i32;		// _mm256_broadcastd_epi32
tag MXC_VECTOR_ABI auto broadcast_i64(v256i64 vSrc) -> v256i64;		// _mm256_broadcastq_epi64
tag MXC_VECTOR_ABI auto broadcast_ix(v256ix vSrc) -> v256ix;		// _mm256_broadcastsi128_si256
tag MXC_VECTOR_ABI auto broadcast_f(v256f vSrc) -> v256f;		    // _mm256_broadcastss_ps
tag MXC_VECTOR_ABI auto broadcast_d(v256d vSrc) -> v256d;		    // _mm256_broadcastsd_pd
tag MXC_VECTOR_ABI auto broadcast_i8(v128i8 vSrc) -> v128i8;		// _mm_broadcastb_epi8
tag MXC_VECTOR_ABI auto broadcast_i16(v128i16 vSrc) -> v128i16;		// _mm_broadcastw_epi16
tag MXC_VECTOR_ABI auto broadcast_i32(v128i32 vSrc) -> v128i32;		// _mm_broadcastd_epi32
tag MXC_VECTOR_ABI auto broadcast_i64(v128i64 vSrc) -> v128i64;		// _mm_broadcastq_epi64
tag MXC_VECTOR_ABI auto broadcast_ix(v128ix vSrc) -> v128ix;		// _mm_broadcastsi128_si256
tag MXC_VECTOR_ABI auto broadcast_f(v128f vSrc) -> v128f;		    // _mm_broadcastss_ps
tag MXC_VECTOR_ABI auto broadcast_d(v128d vSrc) -> v128d;		    // _mm_broadcastsd_pd

template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0) // shamt is in bytes
tag MXC_VECTOR_ABI auto lshiftlanes_ix(v256ix v) -> v256ix;         // _mm256_bslli_epi128
template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0) // shamt is in bytes
tag MXC_VECTOR_ABI auto rshiftlanes_ix(v256ix v) -> v256ix;         // _mm256_bslri_epi128

tag MXC_VECTOR_ABI auto cmpeq_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_cmpeq_epi8
tag MXC_VECTOR_ABI auto cmpeq_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_cmpeq_epi16
tag MXC_VECTOR_ABI auto cmpeq_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_cmpeq_epi32
tag MXC_VECTOR_ABI auto cmpeq_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_cmpeq_epi64
tag MXC_VECTOR_ABI auto cmpgt_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_cmpgt_epi8
tag MXC_VECTOR_ABI auto cmpgt_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_cmpgt_epi16
tag MXC_VECTOR_ABI auto cmpgt_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_cmpgt_epi32
tag MXC_VECTOR_ABI auto cmpgt_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_cmpgt_epi64

template <int32_t lane> requires (lane == 0 || lane == 1)
tag MXC_VECTOR_ABI auto extractlane_ix(v256ix v) -> v128ix;           // _mm256_extracti128_si256

// gather: conditional load of elements specified with VSIB addressing, ie [ base + index * scale ]
// where base is a GPR, index is taken from a XMM/YMM register, and integer scale factor (1,2,4,8)
// the conditionality of the load operation is specified with a mask, using high bits of a 
// XMM/YMM register. where the mask is zero, then the result is taken from the src vector
//
// INDICES USES:
// Indices of the gather operation that can be specified by either a v128i32 or a v128i64. 
// 32-bit -> used in XMM register operations with 32-bit types, to fill all 4 elems
//             or in YMM register operations with 64-bit types, to fill all 4 elems
//             or in XMM register operations with 64-bit types, to fill all 2 elems (2 idx used)
// 64-bit -> used in XMM register operations with 32-bit types, to fill the 2 lower address elems
//             or in XMM register operations with 64-bit types, to fill all 2 elems
//
// Indices of the gather operation that can be specified by either a v256i32 or a v256i64. 
// 32-bit -> used in YMM register operations with 32-bit types, to fill all 8 elems
// 64-bit -> used in XMM register operations with 32-bit types, to fill all 4 elems
//             or in YMM register operations with 64-bit types, to fill all 4 elems
//
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128i32 vSrc, 
    int32_t const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v128i32 vMask) -> v128i32;          // _mm_mask_i32gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256i32 vSrc, 
    int32_t const *MXC_RESTRICT pBase,
    v256i32 vIndices,
    v256i32 vMask) -> v128i32;          // _mm256_mask_i32gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128i64 vSrc, 
    int64_t const *MXC_RESTRICT pBase,
    v128i32 vIndices, // only first 2 are used
    v128i64 vMask) -> v128i64;          // _mm_mask_i32gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256i64 vSrc, 
    int64_t const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v256i64 vMask) -> v128i64;          // _mm256_mask_i32gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128d vSrc, 
    double const *MXC_RESTRICT pBase,
    v128i32 vIndices, // only first 2 are used
    v128d vMask) -> v128d;              // _mm_mask_i32gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256d vSrc, 
    double const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v256d vMask) -> v256d;              // _mm256_mask_i32gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128f vSrc, 
    float const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v128f vMask) -> v128f;              // _mm_mask_i32gather_ps
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256f vSrc, 
    float const *MXC_RESTRICT pBase,
    v256i32 vIndices,
    v256f vMask) -> v256f;              // _mm256_mask_i32gather_ps
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128i32 vSrc,
    int32_t const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128i32 vMask) -> v128i32;          // _mm_mask_i64gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128i32 vSrc,
    int32_t const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v128i32 vMask) -> v128i32;          // _mm256_mask_i64gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128i64 vSrc,
    int64_t const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128i64 vMask) -> v128i64;          // _mm_mask_i64gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256i64 vSrc,
    int64_t const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v256i64 vMask) -> v256i64;          // _mm256_mask_i64gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128d vSrc,
    double const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128d vMask) -> v128d;              // _mm_mask_i64gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256d vSrc,
    double const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v256d vMask) -> v256d;              // _mm256_mask_i64gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v128f vSrc, // only the first 2 elements are gathered
    float const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128f vMask) -> v128f;              // _mm_mask_i64gather_ps
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
tag MXC_VECTOR_ABI auto gather(
    v256f vSrc, // only the first 4 elements are gathered
    float const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v256f vMask) -> v256f;              // _mm256_mask_i64gather_ps

} // namespace mxc::platform::x86_64::avx2

#endif // MXC_PLATFORM_X86_64_AVX2_H
