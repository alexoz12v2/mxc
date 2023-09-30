#ifndef MXC_PLATFORM_X86_64_AVX_512F_H
#define MXC_PLATFORM_X86_64_AVX_512F_H

#include "common_types.h"
#include <cstdint>

// in AVX-512 rounding mode is not automatically determined by MXCSR.RD, 
// but is directly embedded in the instruction itself. That said, I'll still use 
// _MM_FROUND_CUR_DIRECTION, which should be set by the simd library initialization to 
// _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC

namespace mxc::platform::x86_64::avx512f
{

struct MaskMerging {};
struct MaskZeroing {};
inline MaskMerging constexpr mask {};
inline MaskZeroing constexpr maskz{};

// vpabsd
MXC_VECTOR_ABI auto abs_i32(
    v512i32 v) -> v512i32;                  // _mm512_abs_epi32
MXC_VECTOR_ABI auto abs_i32(
    v512i32 v, 
    MaskMerging m,
    int16_t mask,// if an element is masked out, then vAlt[i] is the result (src in docs)
    v512i32 vAlt) -> v512i32;               // _mm512_mask_abs_epi32
MXC_VECTOR_ABI auto abs_i32(
    v512i32 v, 
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_abs_epi32

// vpabsq
MXC_VECTOR_ABI auto abs_i64(
    v512i64 v) -> v512i64;                  // _mm512_abs_epi64
MXC_VECTOR_ABI auto abs_i64(
    v512i64 v, 
    MaskMerging m,
    int8_t mask,
    v512i64 vAlt) -> v512i64;               // _mm512_mask_abs_epi64
MXC_VECTOR_ABI auto abs_i64(
    v512i64 v, 
    MaskZeroing m,
    int8_t mask) -> v512i64;                // _mm512_maskz_abs_epi64

// vpandq with 0x7fff'ffff'ffff'ffff (remove sign bit)(that's why there's no zeromask version?)
MXC_VECTOR_ABI auto abs_d(
    v512d v) -> v512d;                      // _mm512_abs_pd
MXC_VECTOR_ABI auto abs_d(
    v512d v, 
    MaskMerging m,
    int8_t mask,
    v512d vAlt) -> v512d;                   // _mm512_abs_pd

// vpandd with 0x7fff'ffff (remove sign bit) (that's why there's no zeromask version?)
MXC_VECTOR_ABI auto abs_f(
    v512f v) -> v512f;                      // _mm512_abs_ps
MXC_VECTOR_ABI auto abs_f(
    v512f v, 
    MaskMerging m,
    int8_t mask,
    v512f vAlt) -> v512f;                   // _mm512_abs_ps

// vpaddd
MXC_VECTOR_ABI auto add_i32(
    v512i32 v0,
    v512i32 v1) -> v512i32;                 // _mm512_add_epi32
MXC_VECTOR_ABI auto add_i32(
    v512i32 v0,
    v512i32 v1,
    MaskMerging m,
    int16_t mask,
    v512i32 vAlt) -> v512i32;               // _mm512_mask_add_epi32
MXC_VECTOR_ABI auto add_i32(
    v512i32 v0,
    v512i32 v1,
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_add_epi32

// vpaddq
MXC_VECTOR_ABI auto add_i64(
    v512i64 v0,
    v512i64 v1) -> v512i64;                 // _mm512_add_epi64
MXC_VECTOR_ABI auto add_i64(
    v512i64 v0,
    v512i64 v1,
    MaskMerging m,
    int8_t mask,
    v512i64 vAlt) -> v512i64;               // _mm512_mask_add_epi64
MXC_VECTOR_ABI auto add_i64(
    v512i64 v0,
    v512i64 v1,
    MaskZeroing m,
    int8_t mask) -> v512i64;                // _mm512_maskz_add_epi64

// vaddpd
MXC_VECTOR_ABI auto add_d(
    v512d v0,
    v512d v1) -> v512d;                     // _mm512_add_rounding_pd
MXC_VECTOR_ABI auto add_d(
    v512d v0,
    v512d v1,
    MaskMerging m,
    int8_t mask,
    v512d vAlt) -> v512d;                   // _mm512_mask_add_rounding_pd
MXC_VECTOR_ABI auto add_d(
    v512d v0,
    v512d v1,
    MaskZeroing m,
    int8_t mask) -> v512d;                  // _mm512_maskz_add_rounding_pd

// vaddps
MXC_VECTOR_ABI auto add_f(
    v512f v0,
    v512f v1) -> v512f;                     // _mm512_add_rounding_ps
MXC_VECTOR_ABI auto add_f(
    v512f v0,
    v512f v1,
    MaskMerging m,
    int16_t mask,
    v512f vAlt) -> v512f;                   // _mm512_mask_add_rounding_ps
MXC_VECTOR_ABI auto add_f(
    v512f v0,
    v512f v1,
    MaskZeroing m,
    int16_t mask) -> v512f;                 // _mm512_maskz_add_rounding_ps

// valignd
template <int32_t shamt/*element count*/> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catrshift_i32(
    v512i32 vHigh,
    v512i32 vLow) -> v512i32;               // _mm512_alignr_epi32
template <int32_t shamt/*element count*/> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catrshift_i32(
    v512i32 vHigh,
    v512i32 vLow,
    MaskMerging m,
    int16_t mask,
    v512i32 vAlt) -> v512i32;               // _mm512_mask_alignr_epi32
template <int32_t shamt/*element count*/> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catrshift_i32(
    v512i32 vHigh,
    v512i32 vLow,
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_alignr_epi32

// valignq
template <int32_t shamt/*element count*/> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catrshift_i64(
    v512i64 vHigh,
    v512i64 vLow) -> v512i64;               // _mm512_alignr_epi64
template <int32_t shamt/*element count*/> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catrshift_i64(
    v512i64 vHigh,
    v512i64 vLow,
    MaskMerging m,
    int8_t mask,
    v512i64 vAlt) -> v512i64;               // _mm512_mask_alignr_epi64
template <int32_t shamt/*element count*/> requires ((shamt & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto catrshift_i64(
    v512i64 vHigh,
    v512i64 vLow,
    int8_t mask,
    MaskZeroing m) -> v512i64;              // _mm512_maskz_alignr_epi64

// vpandd
MXC_VECTOR_ABI auto and_i32(
    v512i32 v0,
    v512i32 v1) -> v512i32;                 // _mm512_and_epi32
MXC_VECTOR_ABI auto and_i32(
    v512i32 v0,
    v512i32 v1,
    MaskMerging m,
    int16_t mask,
    v512i32 vAlt) -> v512i32;               // _mm512_mask_and_epi32
MXC_VECTOR_ABI auto and_i32(
    v512i32 v0,
    v512i32 v1,
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_and_epi32

// vpandq
MXC_VECTOR_ABI auto and_i64(
    v512i64 v0,
    v512i64 v1) -> v512i64;                 // _mm512_and_epi64
MXC_VECTOR_ABI auto and_i64(
    v512i64 v0,
    v512i64 v1,
    MaskMerging m,
    int8_t mask,
    v512i64 vAlt) -> v512i64;               // _mm512_mask_and_epi64
MXC_VECTOR_ABI auto and_i64(
    v512i64 v0,
    v512i64 v1,
    MaskZeroing m,
    int8_t mask) -> v512i64;                // _mm512_maskz_and_epi64

// vpandnd
MXC_VECTOR_ABI auto andnot_i32(
    v512i32 v0,
    v512i32 v1) -> v512i32;                 // _mm512_andnot_epi32
MXC_VECTOR_ABI auto andnot_i32(
    v512i32 v0,
    v512i32 v1,
    MaskMerging m,
    int16_t mask,
    v512i32 vAlt) -> v512i32;               // _mm512_mask_andnot_epi32
MXC_VECTOR_ABI auto andnot_i32(
    v512i32 v0,
    v512i32 v1,
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_andnot_epi32

// vpandnq
MXC_VECTOR_ABI auto andnot_i64(
    v512i64 v0,
    v512i64 v1) -> v512i64;                 // _mm512_andnot_epi64
MXC_VECTOR_ABI auto andnot_i64(
    v512i64 v0,
    v512i64 v1,
    MaskMerging m,
    int8_t mask,
    v512i64 vAlt) -> v512i64;               // _mm512_mask_andnot_epi64
MXC_VECTOR_ABI auto andnot_i64(
    v512i64 v0,
    v512i64 v1,
    MaskZeroing m,
    int8_t mask) -> v512i64;                // _mm512_maskz_andnot_epi64

// vpblendmd
MXC_VECTOR_ABI auto choose_i32(
    v512i32 v0,
    v512i32 v1,
    int16_t mask) -> v512i32;               // _mm512_mask_blend_epi32

// vpblendmq
MXC_VECTOR_ABI auto choose_i64(
    v512i64 v0,
    v512i64 v1,
    int8_t mask) -> v512i64;                // _mm512_mask_blend_epi64

// vblendmpd
MXC_VECTOR_ABI auto choose_d(
    v512d v0,
    v512d v1,
    int8_t mask) -> v512d;                  // _mm512_mask_blend_pd

// vblendmps
MXC_VECTOR_ABI auto choose_f(
    v512f v0,
    v512f v1,
    int16_t mask) -> v512f;                 // _mm512_mask_blend_ps

// vbroadcoastf32x4
MXC_VECTOR_ABI auto broadcast4_f(
    v128f v) -> v512f;                      // _mm512_broadcast_f32x4
MXC_VECTOR_ABI auto broadcast4_f(
    v128f v,
    MaskMerging m,
    int16_t mask,
    v512f vAlt) -> v512f;                   // _mm512_mask_broadcast_f32x4
MXC_VECTOR_ABI auto broadcast4_f(
    v128f v,
    MaskZeroing m,
    int16_t mask) -> v512f;                 // _mm512_maskz_broadcast_f32x4

// vbroadcastf64x4
MXC_VECTOR_ABI auto broadcast4_d(
    v256d v) -> v512d;                      // _mm512_broadcast_f64x4
MXC_VECTOR_ABI auto broadcast4_d(
    v256d v,
    MaskMerging m,
    int8_t mask,
    v512d vAlt) -> v512d;                   // _mm512_mask_broadcast_f64x4
MXC_VECTOR_ABI auto broadcast4_d(
    v256d v,
    MaskZeroing m,
    int8_t mask) -> v512d;                  // _mm512_maskz_broadcast_f64x4

// vbroadcasti32x4
MXC_VECTOR_ABI auto broadcast4_i32(
    v128i32 v) -> v512i32;                  // _mm512_broadcast_i32x4
MXC_VECTOR_ABI auto broadcast4_i32(
    v128i32 v,
    MaskMerging m,
    int16_t mask,
    v512i32 vAlt) -> v512i32;               // _mm512_mask_broadcast_i32x4
MXC_VECTOR_ABI auto broadcast4_i32(
    v128i32 v,
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_broadcast_i32x4

// vbroadcasti64x4
MXC_VECTOR_ABI auto broadcast4_i64(
    v256i64 v) -> v512i64;                  // _mm512_broadcast_i64x4
MXC_VECTOR_ABI auto broadcast4_i64(
    v256i64 v,
    MaskMerging m,
    int8_t mask,
    v512i64 vAlt) -> v512i64;               // _mm512_mask_broadcast_i64x4
MXC_VECTOR_ABI auto broadcast4_i64(
    v256i64 v,
    MaskZeroing m,
    int8_t mask) -> v512i64;                // _mm512_maskz_broadcast_i64x4

// vpbroadcastd
MXC_VECTOR_ABI auto broadcast_i32(
    v128i32 vSingle) -> v512i32;            // _mm512_broadcastd_epi32
MXC_VECTOR_ABI auto broadcast_i32(
    v128i32 vSingle,
    MaskMerging m,
    int16_t mask,
    v512i64 vAlt) -> v512i32;               // _mm512_mask_broadcastd_epi32
MXC_VECTOR_ABI auto broadcast_i32(
    v128i32 vSigle,
    MaskZeroing m,
    int16_t mask) -> v512i32;               // _mm512_maskz_broadcastd_epi32
} // namespace mxc::platform::x86_64::avx512f

#endif // MXC_PLATFORM_X86_64_AVX_512F_H
