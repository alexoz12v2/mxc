#include "avx.h"

// Required compiler flags:
// -mavx -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args -msse2avx

namespace mxc::platform::x86_64::avx
{

// float vector[8]
MXC_VECTOR_ABI auto load_f(float const * MXC_RESTRICT farrAligned32) -> v256f
{
    auto pf = (decltype(farrAligned32)) MXC_ASSUME_ALIGNED(farrAligned32, 32);
    v256f v = _mm256_load_ps(pf);
    return v;
}

MXC_VECTOR_ABI auto store_f(v256f v, float * MXC_RESTRICT out_farrAligned32) -> void
{
    auto pf = (decltype(out_farrAligned32))MXC_ASSUME_ALIGNED(out_farrAligned32, 32);
    _mm256_store_ps(pf, v);
}

MXC_VECTOR_ABI auto add_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_add_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto sub_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_sub_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto mul_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_mul_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto div_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_div_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto sqrt_f(v256f v) -> v256f
{
    v256f vRes = _mm256_sqrt_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto rsqrt_f(v256f v) -> v256f
{
    v256f vRes = _mm256_rsqrt_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto rcp_f(v256f v) -> v256f
{
    v256f vRes = _mm256_rcp_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto max_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_max_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto min_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_min_ps(v0, v1);
    return v;
}

template <int32_t opi8_low> 
MXC_VECTOR_ABI auto cmp_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_cmp_ps(v0, v1, opi8_low);
    return v;
}

MXC_VECTOR_ABI auto or_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_or_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto xor_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_xor_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto and_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_and_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto andnot_f(v256f v0, v256f v1) -> v256f
{
    v256f v = _mm256_andnot_ps(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto round_f(v256f v0) -> v256f
{
    v256f v = _mm256_round_ps(v0, (_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
    return v;
}

MXC_VECTOR_ABI auto ceil_f(v256f v0) -> v256f
{
    v256f v = _mm256_ceil_ps(v0);
    return v;
}

MXC_VECTOR_ABI auto floor_f(v256f v0) -> v256f
{
    v256f v = _mm256_floor_ps(v0);
    return v;
}

template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_f(v256f v) -> v256f
{
    v256f vRes = _mm256_permute_ps(v, ctrli8_low);
    return vRes;
}

// float vector[4]
template <int32_t opi8_low> 
MXC_VECTOR_ABI auto cmp_f(v128f v0, v128f v1) -> v128f
{
    v128f vRes = _mm_cmp_ps(v0, v1, opi8_low);
    return vRes;
}

template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_f(v128f v) -> v128f
{
    v128f vRes = _mm_permute_ps(v, ctrli8_low);
    return vRes;
}

template <int32_t binaryFlag>
MXC_VECTOR_ABI auto extractf128_f(v256f v) -> v128f
{
    v128f vRes = _mm256_extractf128_ps(v, binaryFlag);
    return vRes;
}

// double vector[4]
MXC_VECTOR_ABI auto load_d(double const * MXC_RESTRICT darrAligned32) -> v256d
{
    auto pd = (decltype(darrAligned32)) MXC_ASSUME_ALIGNED(darrAligned32, 32);
    v256d v = _mm256_load_pd(pd);
    return v;
}

MXC_VECTOR_ABI auto store_d(v256d v, double * MXC_RESTRICT out_darrAligned32) -> void
{
    auto pd = (decltype(out_darrAligned32)) MXC_ASSUME_ALIGNED(out_darrAligned32, 32);
    _mm256_store_pd(pd, v);
}

MXC_VECTOR_ABI auto add_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_add_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto sub_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_sub_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto mul_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_mul_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto div_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_div_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto sqrt_d(v256d v) -> v256d
{
    v256d vRes = _mm256_sqrt_pd(v);
    return vRes;
}

MXC_VECTOR_ABI auto max_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_max_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto min_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_min_pd(v0, v1);
    return v;
}

template <int32_t opi8_low> 
MXC_VECTOR_ABI auto cmp_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_cmp_pd(v0, v1, opi8_low);
    return v;
}

MXC_VECTOR_ABI auto or_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_or_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto xor_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_xor_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto and_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_and_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto andnot_d(v256d v0, v256d v1) -> v256d
{
    v256d v = _mm256_andnot_pd(v0, v1);
    return v;
}

MXC_VECTOR_ABI auto round_d(v256d v0) -> v256d
{
    v256d v = _mm256_round_pd(v0, (_MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
    return v;
}

MXC_VECTOR_ABI auto ceil_d(v256d v0) -> v256d
{
    v256d v = _mm256_ceil_pd(v0);
    return v;
}

MXC_VECTOR_ABI auto floor_d(v256d v0) -> v256d
{
    v256d v = _mm256_floor_pd(v0);
    return v;
}

template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_d(v256d v) -> v256d
{
    v256d vRes = _mm256_permute_pd(v, ctrli8_low);
    return vRes;
}

// double vector[2]
template <int32_t opi8_low> 
MXC_VECTOR_ABI auto cmp_d(v128d v0, v128d v1) -> v128d
{
    v128d vRes = _mm_cmp_pd(v0, v1, opi8_low);
    return vRes;
}

template <int32_t ctrli8_low>
MXC_VECTOR_ABI auto permute_d(v128d v) -> v128d
{
    v128d vRes = _mm_permute_pd(v, ctrli8_low);
    return vRes;
}

template <int32_t binaryFlag>
MXC_VECTOR_ABI auto extractf128_d(v256d v) -> v128d
{
    v128d vRes = _mm256_extractf128_pd(v, binaryFlag);
    return vRes;
}

// int8_t vector[32]
MXC_VECTOR_ABI auto load_i8(int8_t const * MXC_RESTRICT i8arrAligned32) -> v256i8
{
    auto pi8 = (v256i8 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i8arrAligned32, 32);
    v256i8 v = _mm256_load_si256(pi8);
    return v;
}

MXC_VECTOR_ABI auto store_i8(v256i8 v, int8_t * MXC_RESTRICT out_i8arrAligned32) -> void
{
    auto pi8 = (v256i8 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i8arrAligned32, 32);
    _mm256_store_si256(pi8, v);
}

// int16_t vector[16]
MXC_VECTOR_ABI auto load_i16(int16_t const * MXC_RESTRICT i16arrAligned32) -> v256i16
{
    auto pi16 = (v256i16 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i16arrAligned32, 32);
    v256i16 v = _mm256_load_si256(pi16);
    return v;
}

MXC_VECTOR_ABI auto store_i16(v256i16 v, int8_t * MXC_RESTRICT out_i16arrAligned32) -> void
{
    auto pi16 = (v256i16 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i16arrAligned32, 32);
    _mm256_store_si256(pi16, v);
}

// int32_t vector[8]
MXC_VECTOR_ABI auto load_i32(int32_t const * MXC_RESTRICT i32arrAligned32) -> v256i32
{
    auto pi32 = (v256i32 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i32arrAligned32, 32);
    v256i32 v = _mm256_load_si256(pi32);
    return v;
}

MXC_VECTOR_ABI auto store_i32(v256i32 v, int32_t * MXC_RESTRICT out_i32arrAligned32) -> void
{
    auto pi32 = (v256i32 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i32arrAligned32, 32);
    _mm256_store_si256(pi32, v);
}

// int64_t vector[4]
MXC_VECTOR_ABI auto load_i64(int64_t const * MXC_RESTRICT i64arrAligned32) -> v256i64
{
    auto pi64 = (v256i64 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i64arrAligned32, 32);
    v256i64 v = _mm256_load_si256(pi64);
    return v;
}

MXC_VECTOR_ABI auto store_i64(v256i64 v, int8_t * MXC_RESTRICT out_i64arrAligned32) -> void
{
    auto pi64 = (v256i64 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i64arrAligned32, 32);
    _mm256_store_si256(pi64, v);
}

} // namespace mxc::platform::x86_64

