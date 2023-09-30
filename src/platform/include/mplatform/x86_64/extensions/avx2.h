#ifndef MXC_PLATFORM_X86_64_AVX2_H
#define MXC_PLATFORM_X86_64_AVX2_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::avx2
{

MXC_VECTOR_ABI auto abs_i8(v256i8 v) -> v256i8;                          // _mm256_abs_epi8
MXC_VECTOR_ABI auto abs_i16(v256i16 v) -> v256i16;                       // _mm256_abs_epi16
MXC_VECTOR_ABI auto abs_i32(v256i32 v) -> v256i32;                       // _mm256_abs_epi32

MXC_VECTOR_ABI auto add_i8(v256i8 v0, v256i8 v1) -> v256i8;              // _mm256_add_epi8
MXC_VECTOR_ABI auto add_i16(v256i16 v0, v256i16 v1) -> v256i16;          // _mm256_add_epi16
MXC_VECTOR_ABI auto add_i32(v256i32 v0, v256i32 v1) -> v256i32;          // _mm256_add_epi32

MXC_VECTOR_ABI auto addClamp_i8(v256i8 v0, v256i8 v1) -> v256i8;         // _mm256_adds_epi8
MXC_VECTOR_ABI auto addClamp_i16(v256i16 v0, v256i16 v1) -> v256i16;     // _mm256_adds_epi16
MXC_VECTOR_ABI auto addClamp_u8(v256u8 v0, v256u8 v1) -> v256u8;         // _mm256_adds_epu8
MXC_VECTOR_ABI auto addClamp_u16(v256u16 v0, v256u16 v1) -> v256u16;     // _mm256_adds_epu16

// concatenate 2 lanes from v0 and v1, shift them right by ctrl bytes. Repeat for the second lane
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catLanesShr_ix(v256ix vHigh, v256ix vLow) -> v256ix; // _mm256_alignr_epi8

MXC_VECTOR_ABI auto and_ix(v256ix v0, v256ix v1) -> v256ix;              // _mm256_and_si256

MXC_VECTOR_ABI auto andnot_ix(v256ix v0, v256ix v1) -> v256ix;           // _mm256_andnot_si256

MXC_VECTOR_ABI auto avg_u8(v256u8 v0, v256u8 v1) -> v256u8;              // _mm256_avg_epu8
MXC_VECTOR_ABI auto avg_u16(v256u16 v0, v256u16 v1) -> v256u16;          // _mm256_avg_epu16

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_i16(v256i16 v0, v256i16 v1) -> v256i16;       // _mm256_blend_epi16
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_i32(v128i32 v0, v128i32 v1) -> v128i32;       // _mm_blend_epi32
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_i32(v256i32 v0, v256i32 v1) -> v256i32;       // _mm256_blend_epi32

// _mm256_blendv_epi8
MXC_VECTOR_ABI auto chooseVariable_i8(v256i8 v0, v256i8 v1, v256ix mask) -> v256i8;

// broadcast = produce a vector containing copies of the first (low) element
//             from a source vector
MXC_VECTOR_ABI auto broadcast256_i8(v128i8 vSrc) -> v256i8;		// _mm256_broadcastb_epi8
MXC_VECTOR_ABI auto broadcast256_i16(v128i16 vSrc) -> v256i16;	// _mm256_broadcastw_epi16
MXC_VECTOR_ABI auto broadcast256_i32(v128i32 vSrc) -> v256i32;	// _mm256_broadcastd_epi32
MXC_VECTOR_ABI auto broadcast256_i64(v128i64 vSrc) -> v256i64;	// _mm256_broadcastq_epi64
MXC_VECTOR_ABI auto broadcast256_ix(v128ix vSrc) -> v256ix;		// _mm256_broadcastsi128_si256
MXC_VECTOR_ABI auto broadcast256_f(v128f vSrc) -> v256f;		// _mm256_broadcastss_ps
MXC_VECTOR_ABI auto broadcast256_d(v128d vSrc) -> v256d;		// _mm256_broadcastsd_pd
MXC_VECTOR_ABI auto broadcast_i8(v128i8 vSrc) -> v128i8;		// _mm_broadcastb_epi8
MXC_VECTOR_ABI auto broadcast_i16(v128i16 vSrc) -> v128i16;		// _mm_broadcastw_epi16
MXC_VECTOR_ABI auto broadcast_i32(v128i32 vSrc) -> v128i32;		// _mm_broadcastd_epi32
MXC_VECTOR_ABI auto broadcast_i64(v128i64 vSrc) -> v128i64;		// _mm_broadcastq_epi64
MXC_VECTOR_ABI auto broadcast_f(v128f vSrc) -> v128f;		    // _mm_broadcastss_ps
MXC_VECTOR_ABI auto broadcast_d(v128d vSrc) -> v128d;		    // _mm_broadcastsd_pd

template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0) // shamt is in bytes
MXC_VECTOR_ABI auto lshiftlanes_ix(v256ix v) -> v256ix;         // _mm256_bslli_epi128
template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0) // shamt is in bytes
MXC_VECTOR_ABI auto rshiftlanes_ix(v256ix v) -> v256ix;         // _mm256_bsrli_epi128

MXC_VECTOR_ABI auto cmpeq_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_cmpeq_epi8
MXC_VECTOR_ABI auto cmpeq_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_cmpeq_epi16
MXC_VECTOR_ABI auto cmpeq_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_cmpeq_epi32
MXC_VECTOR_ABI auto cmpeq_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_cmpeq_epi64
MXC_VECTOR_ABI auto cmpgt_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_cmpgt_epi8
MXC_VECTOR_ABI auto cmpgt_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_cmpgt_epi16
MXC_VECTOR_ABI auto cmpgt_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_cmpgt_epi32
MXC_VECTOR_ABI auto cmpgt_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_cmpgt_epi64

template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto extractlane_ix(v256ix v) -> v128ix;           // _mm256_extracti128_si256

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
MXC_VECTOR_ABI auto gatherd_i32(
    v128i32 vSrc, 
    int32_t const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v128i32 vMask) -> v128i32;          // _mm_mask_i32gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_i32(
    v256i32 vSrc, 
    int32_t const *MXC_RESTRICT pBase,
    v256i32 vIndices,
    v256i32 vMask) -> v256i32;          // _mm256_mask_i32gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_i64(
    v128i64 vSrc, 
    int64_t const *MXC_RESTRICT pBase,
    v128i32 vIndices, // only first 2 are used
    v128i64 vMask) -> v128i64;          // _mm_mask_i32gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_i64(
    v256i64 vSrc, 
    int64_t const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v256i64 vMask) -> v256i64;          // _mm256_mask_i32gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_d(
    v128d vSrc, 
    double const *MXC_RESTRICT pBase,
    v128i32 vIndices, // only first 2 are used
    v128d vMask) -> v128d;              // _mm_mask_i32gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_d(
    v256d vSrc, 
    double const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v256d vMask) -> v256d;              // _mm256_mask_i32gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_f(
    v128f vSrc, 
    float const *MXC_RESTRICT pBase,
    v128i32 vIndices,
    v128f vMask) -> v128f;              // _mm_mask_i32gather_ps
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherd_f(
    v256f vSrc, 
    float const *MXC_RESTRICT pBase,
    v256i32 vIndices,
    v256f vMask) -> v256f;              // _mm256_mask_i32gather_ps
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_i32(
    v128i32 vSrc,
    int32_t const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128i32 vMask) -> v128i32;          // _mm_mask_i64gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_i32(
    v128i32 vSrc,
    int32_t const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v128i32 vMask) -> v128i32;          // _mm256_mask_i64gather_epi32
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_i64(
    v128i64 vSrc,
    int64_t const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128i64 vMask) -> v128i64;          // _mm_mask_i64gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_i64(
    v256i64 vSrc,
    int64_t const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v256i64 vMask) -> v256i64;          // _mm256_mask_i64gather_epi64
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_d(
    v128d vSrc,
    double const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128d vMask) -> v128d;              // _mm_mask_i64gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_d(
    v256d vSrc,
    double const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v256d vMask) -> v256d;              // _mm256_mask_i64gather_pd
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_f(
    v128f vSrc, // only the first 2 elements are gathered
    float const *MXC_RESTRICT pBase,
    v128i64 vIndices,
    v128f vMask) -> v128f;              // _mm_mask_i64gather_ps
template <int32_t scale> requires (scale == 1 || scale == 2 || scale == 4 || scale == 8)
MXC_VECTOR_ABI auto gatherq_f(
    v256f vSrc, // only the first 4 elements are gathered
    float const *MXC_RESTRICT pBase,
    v256i64 vIndices,
    v256f vMask) -> v256f;              // _mm256_mask_i64gather_ps

template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto insert_ix(v256ix vSrc, v128ix vOpr) -> v256ix; // _mm256_inserti128_si256

MXC_VECTOR_ABI auto fmaddAdjacent_i16(v256i16 v0, v256i16 v1) -> v256i32; // _mm256_madd_epi16

// perform fma adding adjacent pairs, and saturate (clamp) the result
MXC_VECTOR_ABI auto fmaddClAdj_u8(v256u8 v0, v256u8 v1) -> v256i16; // _mm256_maddubs_epi16

// masked elements are zeroed out                                       // _mm_maskload_epi32
MXC_VECTOR_ABI auto maskload_i32(int32_t const *MXC_RESTRICT iarr, v128ix mask) -> v128i32;
                                                                        // _mm256_maskload_epi32
MXC_VECTOR_ABI auto maskload_i32(int32_t const *MXC_RESTRICT iarr, v256ix mask) -> v256i32;
                                                                        // _mm_maskload_epi64
MXC_VECTOR_ABI auto maskload_i64(int64_t const *MXC_RESTRICT iarr, v128ix mask) -> v128i64;
                                                                        // _mm256_maskload_epi64
MXC_VECTOR_ABI auto maskload_i64(int64_t const *MXC_RESTRICT iarr, v256ix mask) -> v256i64;

// masked elements are not stored, leaving "holes" in memory            // _mm_maskstore_epi32
MXC_VECTOR_ABI auto maskstore_i32(v128i32 v, int32_t *MXC_RESTRICT iarr, v128ix mask) -> void;
                                                                        // _mm256_maskstore_epi32
MXC_VECTOR_ABI auto maskstore_i32(v256i32 v, int32_t *MXC_RESTRICT iarr, v256ix mask) -> void;
                                                                        // _mm_maskstore_epi64
MXC_VECTOR_ABI auto maskstore_i64(v128i64 v, int64_t *MXC_RESTRICT iarr, v128ix mask) -> void;
                                                                        // _mm256_maskstore_epi64
MXC_VECTOR_ABI auto maskstore_i64(v256i64 v, int64_t *MXC_RESTRICT iarr, v256ix mask) -> void;

MXC_VECTOR_ABI auto max_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_max_epi8
MXC_VECTOR_ABI auto max_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_max_epi16
MXC_VECTOR_ABI auto max_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_max_epi32
MXC_VECTOR_ABI auto max_u8(v256u8 v0, v256u8 v1) -> v256u8;     // _mm256_max_epu8
MXC_VECTOR_ABI auto max_u16(v256u16 v0, v256u16 v1) -> v256u16; // _mm256_max_epu16
MXC_VECTOR_ABI auto max_u32(v256u32 v0, v256u32 v1) -> v256u32; // _mm256_max_epu32

MXC_VECTOR_ABI auto min_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_min_epi8
MXC_VECTOR_ABI auto min_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_min_epi16
MXC_VECTOR_ABI auto min_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_min_epi32
MXC_VECTOR_ABI auto min_u8(v256u8 v0, v256u8 v1) -> v256u8;     // _mm256_min_epu8
MXC_VECTOR_ABI auto min_u16(v256u16 v0, v256u16 v1) -> v256u16; // _mm256_min_epu16
MXC_VECTOR_ABI auto min_u32(v256u32 v0, v256u32 v1) -> v256u32; // _mm256_min_epu32

MXC_VECTOR_ABI auto grabMSBs(v256ix v) -> int32_t;  // _mm256_movemask_epi8

template <int32_t bits> requires ((bits & 0x0000'00ff) == 0)        // _mm256_mpsadbw_epu8
MXC_VECTOR_ABI auto selectiveSAD_u8(v256u8 vSrc, v256u8 vKern) -> v256u16;

// the instruction is the same, so there are no savings. Since it skips the offsetted evaluation,
// it produces less results
MXC_VECTOR_ABI auto SAD_u8(v256u8 v0, v256u8 v1) -> v256i64;

MXC_VECTOR_ABI auto mulClmp_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_mullo_epi16
MXC_VECTOR_ABI auto mulClmp_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_mullo_epi32

MXC_VECTOR_ABI auto or_ix(v256ix v0, v256ix v1) -> v256ix; // _mm256_or_si256

// packed integer coertion instructions (vpack[us]s(wb|dw)) are not added here.

// vperm2i128
template <int32_t lane> requires (lane >= 0 && lane < 4)             // _mm256_permute2x128_si256
MXC_VECTOR_ABI auto permutelanes_ix(v256ix v0, v256ix v1) -> v256ix;

// vperm(pd|ps|d|q)
template <int32_t lane> requires (lane >= 0 && lane < 4)
MXC_VECTOR_ABI auto permute_i64(v256i64 vSrc) -> v256i64;        // _mm256_permute4x64_epi64
template <int32_t lane> requires (lane >= 0 && lane < 4)
MXC_VECTOR_ABI auto permute_d(v256d v) -> v256d;                 // _mm256_permute4x64_pd

MXC_VECTOR_ABI auto permute_f(v256f v, v256ix vIdxs) -> v256f;   // _mm256_permutevar8x32_ps
                                                                     // _mm256_permutevar8x32_epi32
MXC_VECTOR_ABI auto permute_i32(v256i32 v, v256ix vIdxs) -> v256i32; 

// arbitrarily reorder elements within each lane
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_i32(v256i32 v) -> v256i32;            // _mm256_shuffle_epi32

MXC_VECTOR_ABI auto shuffle_i8(v256i8 v, v256i8 vIdxs) -> v256i8; // _mm256_shuffle_epi8

// shuffles high halfs of each lane. the 4 indices are 2 bits each and let you select exacly the 
// high four elements of each lane to rearrange them. Analogous functionality with vpshuflw
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffleHigh_i16(v256i16 v) -> v256i16;       // _mm256_shufflehi_epi16
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffleLow_i16(v256i16 v) -> v256i16;        // _mm256_shufflelo_epi16

MXC_VECTOR_ABI auto copysign_i16(v256i16 vSrc, v256i16 vSigns) -> v256i16; // _mm256_sign_epi16
MXC_VECTOR_ABI auto copysign_i32(v256i32 vSrc, v256i32 vSigns) -> v256i32; // _mm256_sign_epi32
MXC_VECTOR_ABI auto copysign_i8(v256i8 vSrc, v256i8 vSigns) -> v256i8;     // _mm256_sign_epi8

template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto lshift_i16(v256i16 v) -> v256i16;   // _mm256_slli_epi16
template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto lshift_i32(v256i32 v) -> v256i32;   // _mm256_slli_epi32
template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto lshift_i64(v256i64 v) -> v256i64;   // _mm256_slli_epi64

// overloads of non variable shift in which low 64-bit element in the vShamt operand is used
MXC_VECTOR_ABI auto lshift_i16(v256i16 v, v128u64 vShamt) -> v256i16; // _mm256_sll_epi16
MXC_VECTOR_ABI auto lshift_i32(v256i32 v, v128u64 vShamt) -> v256i32; // _mm256_sll_epi32
MXC_VECTOR_ABI auto lshift_i64(v256i64 v, v128u64 vShamt) -> v256i64; // _mm256_sll_epi64

MXC_VECTOR_ABI auto lshiftVariable_i32(v128i32 v, v128u32 vS) -> v128i32; // _mm_sllv_epi32
MXC_VECTOR_ABI auto lshiftVariable_i32(v256i32 v, v256u32 vS) -> v256i32; // _mm256_sllv_epi32
MXC_VECTOR_ABI auto lshiftVariable_i64(v128i64 v, v128u32 vS) -> v128i64; // _mm_sllv_epi64
MXC_VECTOR_ABI auto lshiftVariable_i64(v256i64 v, v256u32 vS) -> v256i64; // _mm256_sllv_epi64

template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto rshift_i16(v256i16 v) -> v256i16;   // _mm256_srli_epi16
template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto rshift_i32(v256i32 v) -> v256i32;   // _mm256_srli_epi32
template <int32_t shamt> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto rshift_i64(v256i64 v) -> v256i64;   // _mm256_srli_epi64

// overloads of non variable shift in which low 64-bit element in the vShamt operand is used
MXC_VECTOR_ABI auto rshift_i16(v256i16 v, v128u64 vShamt) -> v256i16; // _mm256_srl_epi16
MXC_VECTOR_ABI auto rshift_i32(v256i32 v, v128u64 vShamt) -> v256i32; // _mm256_srl_epi32
MXC_VECTOR_ABI auto rshift_i64(v256i64 v, v128u64 vShamt) -> v256i64; // _mm256_srl_epi64

MXC_VECTOR_ABI auto rshiftVariable_i32(v128i32 v, v128u32 vS) -> v128i32; // _mm_srlv_epi32
MXC_VECTOR_ABI auto rshiftVariable_i32(v256i32 v, v256u32 vS) -> v256i32; // _mm256_srlv_epi32
MXC_VECTOR_ABI auto rshiftVariable_i64(v128i64 v, v128u32 vS) -> v128i64; // _mm_srlv_epi64
MXC_VECTOR_ABI auto rshiftVariable_i64(v256i64 v, v256u32 vS) -> v256i64; // _mm256_srlv_epi64

MXC_VECTOR_ABI auto sub_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_sub_epi8
MXC_VECTOR_ABI auto sub_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_sub_epi16
MXC_VECTOR_ABI auto sub_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_sub_epi32
MXC_VECTOR_ABI auto sub_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_sub_epi64

MXC_VECTOR_ABI auto subClamped_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_subs_epi8
MXC_VECTOR_ABI auto subClamped_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_subs_epi16
MXC_VECTOR_ABI auto subClamped_u8(v256u8 v0, v256u8 v1) -> v256u8;     // _mm256_subs_epu8
MXC_VECTOR_ABI auto subClamped_u16(v256u16 v0, v256u16 v1) -> v256u16; // _mm256_subs_epu16

// take high halves of each lane and mix them
MXC_VECTOR_ABI auto unpackhi_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_unpackhi_epi8
MXC_VECTOR_ABI auto unpackhi_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_unpackhi_epi16
MXC_VECTOR_ABI auto unpackhi_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_unpackhi_epi32
MXC_VECTOR_ABI auto unpackhi_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_unpackhi_epi64

// take low halves of each lane and mix them
MXC_VECTOR_ABI auto unpacklo_i8(v256i8 v0, v256i8 v1) -> v256i8;     // _mm256_unpacklo_epi8
MXC_VECTOR_ABI auto unpacklo_i16(v256i16 v0, v256i16 v1) -> v256i16; // _mm256_unpacklo_epi16
MXC_VECTOR_ABI auto unpacklo_i32(v256i32 v0, v256i32 v1) -> v256i32; // _mm256_unpacklo_epi32
MXC_VECTOR_ABI auto unpacklo_i64(v256i64 v0, v256i64 v1) -> v256i64; // _mm256_unpacklo_epi64

MXC_VECTOR_ABI auto xor_ix(v256ix v0, v256ix v1) -> v256ix;          // _mm256_xor_si256

} // namespace mxc::platform::x86_64::avx2

#endif // MXC_PLATFORM_X86_64_AVX2_H
