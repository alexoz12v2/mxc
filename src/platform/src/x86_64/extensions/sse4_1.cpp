#if defined(MXC_SSE_AS_AVX)
#include "sse4_1vex.h"
#else
#include "sse4_1.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse4_1vex
#else
namespace mxc::platform::x86_64::sse4_1
#endif
{
// int8_t vector[16]
MXC_VECTOR_ABI auto chooseVariable_i8(v128i8 v0, v128i8 v1, v128i8 mask) -> v128i8
{
    v128i8 const vRes = _mm_blendv_epi8(v0, v1, mask);
    return vRes;
}

template <int32_t index>
    requires(index >= 0 && index < 16)
MXC_VECTOR_ABI auto extract_i8(v128i8 v) -> int8_t
{
    int8_t const res = static_cast<int8_t>(_mm_extract_epi8(v, index));
    return res;
}

template <int32_t index>
    requires(index >= 0 && index < 16)
MXC_VECTOR_ABI auto insert_i8(v128i8 v, int8_t elem) -> v128i8
{
    v128i8 const vRes = _mm_insert_epi8(v, elem, index);
    return vRes;
}

MXC_VECTOR_ABI auto max_i8(v128i8 v0, v128i8 v1) -> v128i8
{
    v128i8 const vRes = _mm_max_epi8(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto min_i8(v128i8 v0, v128i8 v1) -> v128i8
{
    v128i8 const vRes = _mm_min_epi8(v0, v1);
    return vRes;
}

template <int32_t bits>
    requires((bits & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto selectiveSAD_u8(v128u8 vSource, v128u8 vChoices) -> v128i16
{
    v128i16 vRes = _mm_mpsadbw_epu8(vSource, vChoices, bits);
    return vRes;
}

// int16_t vector[8]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_i16(v128i16 v0, v128i16 v1) -> v128i16
{
    v128i16 const vRes = _mm_blend_epi16(v0, v1, bits8_low);
    return vRes;
}

MXC_VECTOR_ABI auto max_u16(v128u16 v0, v128u16 v1) -> v128u16
{
    v128u16 const vRes = _mm_max_epu16(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto min_u16(v128u16 v0, v128u16 v1) -> v128u16
{
    v128u16 const vRes = _mm_min_epu16(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto minpos_u16(v128u16 v0) -> v128u16
{
    v128u16 const vRes = _mm_minpos_epu16(v0);
    return vRes;
}

// int32_t vector[4]
template <int32_t index>
    requires(index >= 0 && index < 4)
MXC_VECTOR_ABI auto extract_i32(v128i32 v) -> int32_t
{
    int32_t const res = _mm_extract_epi32(v, index);
    return res;
}

template <int32_t index>
    requires(index >= 0 && index < 4)
MXC_VECTOR_ABI auto insert_i32(v128i32 v, int32_t elem) -> v128i32
{
    v128i32 const vRes = _mm_insert_epi32(v, elem, index);
    return vRes;
}

MXC_VECTOR_ABI auto max_i32(v128i32 v0, v128i32 v1) -> v128i32
{
    v128i32 const vRes = _mm_max_epi32(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto max_u32(v128u32 v0, v128u32 v1) -> v128u32
{
    v128u32 const vRes = _mm_max_epu32(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto min_i32(v128i32 v0, v128i32 v1) -> v128i32
{
    v128i32 const vRes = _mm_min_epi32(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto min_u32(v128u32 v0, v128u32 v1) -> v128u32
{
    v128i32 const vRes = _mm_min_epu32(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto mulOdds_i32(v128i32 v0, v128i32 v1) -> v128i64
{
    v128i64 const vRes = _mm_mul_epi32(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto mul_i32(v128i32 v0, v128i32 v1) -> v128i32
{
    v128i32 const vRes = _mm_mullo_epi32(v0, v1);
    return vRes;
}

// int64_t vector[4]
MXC_VECTOR_ABI auto cmpeq_i64(v128i64 v0, v128i64 v1) -> v128i64
{
    v128i64 const vRes = _mm_cmpeq_epi64(v0, v1);
    return vRes;
}

template <int32_t index>
    requires(index >= 0 && index < 2)
MXC_VECTOR_ABI auto insert_i64(v128i64 v, int64_t elem) -> v128i64
{
    v128i64 const vRes = _mm_insert_epi64(v, elem, index);
    return vRes;
}

template <int32_t index>
    requires(index >= 0 && index < 2)
MXC_VECTOR_ABI auto extract_i64(v128i64 v) -> int64_t
{
    int64_t const res = _mm_extract_epi64(v, index);
    return res;
}

// float vector[4]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_blend_ps(v0, v1, bits8_low);
    return vRes;
}

MXC_VECTOR_ABI auto chooseVariable_f(v128f v0, v128f v1, v128f mask) -> v128f
{
    v128f const vRes = _mm_blendv_ps(v0, v1, mask);
    return vRes;
}

MXC_VECTOR_ABI auto ceil_f(v128f v) -> v128f
{
    v128f const vRes = _mm_ceil_ps(v);
    return vRes;
}

template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto conditionalDotProduct_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_dp_ps(v0, v1, bits8_low);
    return vRes;
}

template <int32_t index>
    requires(index >= 0 && index < 4)
MXC_VECTOR_ABI auto extract_f(v128f v) -> float
{
    float const res = _mm_extract_ps(v, index);
    return res;
}

MXC_VECTOR_ABI auto floor_f(v128f v) -> v128f
{
    v128f const vRes = _mm_floor_ps(v);
    return vRes;
}

template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto chooseInsertMask_f(v128f vSource, v128f vChoices) -> v128f
{
    v128f const vRes = _mm_insert_ps(vSource, vChoices, bits8_low);
    return vRes;
}

MXC_VECTOR_ABI auto round_f(v128f v) -> v128f
{
    v128f const vRes = _mm_round_ps(v, (_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
    return vRes;
}

// double vector[2]
template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto choose_d(v128d v0, v128d v1) -> v128d
{
    v128d const vRes = _mm_blend_pd(v0, v1, bits8_low);
    return vRes;
}

MXC_VECTOR_ABI auto chooseVariable_d(v128d v0, v128d v1, v128d mask) -> v128d
{
    v128d const vRes = _mm_blendv_pd(v0, v1, mask);
    return vRes;
}

MXC_VECTOR_ABI auto ceil_d(v128d v) -> v128d
{
    v128d const vRes = _mm_ceil_pd(v);
    return vRes;
}

template <int32_t bits8_low>
    requires((bits8_low & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto conditionalDotProduct_d(v128d v0, v128d v1) -> v128d
{
    v128d const vRes = _mm_dp_pd(v0, v1, bits8_low);
    return vRes;
}

MXC_VECTOR_ABI auto floor_d(v128d v) -> v128d
{
    v128d const vRes = _mm_floor_pd(v);
    return vRes;
}

MXC_VECTOR_ABI auto round_d(v128d v) -> v128d
{
    v128d const vRes = _mm_round_pd(v, (_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
    return vRes;
}

// integer conversion functions (take the max elements from lowest address that target
// type can store)
MXC_VECTOR_ABI auto i16Toi32(v128i16 v) -> v128i32
{
    v128i32 const vRes = _mm_cvtepi16_epi32(v);
    return vRes;
}

MXC_VECTOR_ABI auto i16Toi64(v128i16 v) -> v128i64
{
    v128i64 const vRes = _mm_cvtepi16_epi64(v);
    return vRes;
}

MXC_VECTOR_ABI auto i32Toi64(v128i32 v) -> v128i64
{
    v128i64 const vRes = _mm_cvtepi32_epi64(v);
    return vRes;
}

MXC_VECTOR_ABI auto i8Toi16(v128i8 v) -> v128i16
{
    v128i16 const vRes = _mm_cvtepi8_epi16(v);
    return vRes;
}

MXC_VECTOR_ABI auto i8Toi32(v128i8 v) -> v128i32
{
    v128i32 const vRes = _mm_cvtepi8_epi32(v);
    return vRes;
}

MXC_VECTOR_ABI auto i8Toi64(v128i8 v) -> v128i64
{
    v128i64 const vRes = _mm_cvtepi8_epi64(v);
    return vRes;
}

MXC_VECTOR_ABI auto u16Toi32(v128u16 v) -> v128i32
{
    v128i32 const vRes = _mm_cvtepu16_epi32(v);
    return vRes;
}

MXC_VECTOR_ABI auto u16Toi64(v128u16 v) -> v128i64
{
    v128i64 const vRes = _mm_cvtepu16_epi64(v);
    return vRes;
}

MXC_VECTOR_ABI auto u32Toi64(v128u32 v) -> v128i64
{
    v128i64 const vRes = _mm_cvtepu32_epi64(v);
    return vRes;
}

MXC_VECTOR_ABI auto u8Toi16(v128u8 v) -> v128i16
{
    v128i16 const vRes = _mm_cvtepu8_epi16(v);
    return vRes;
}

MXC_VECTOR_ABI auto u8Toi32(v128u8 v) -> v128i32
{
    v128i32 const vRes = _mm_cvtepu8_epi32(v);
    return vRes;
}

MXC_VECTOR_ABI auto u8Toi64(v128u8 v) -> v128i64
{
    v128i32 const vRes = _mm_cvtepu8_epi64(v);
    return vRes;
}

MXC_VECTOR_ABI auto i32Toi16clamp(v128i32 v0, v128i32 v1) -> v128i16
{
    v128i16 vRes = _mm_packus_epi32(v0, v1);
    return vRes;
}

// independent of integer type
MXC_VECTOR_ABI auto AndEqualsAllZero(v128ix v0, v128ix v1) -> bool
{
    bool const res = static_cast<bool>(_mm_test_all_zeros(v0, v1));
    return res;
}

MXC_VECTOR_ABI auto notAndEqualsAllZero(v128ix v0, v128ix v1) -> bool // _mm_testc_si128
{
    bool const res = static_cast<bool>(_mm_testc_si128(v0, v1));
    return res;
}
} // namespace mxc::platform::x86_64::sse4_1
