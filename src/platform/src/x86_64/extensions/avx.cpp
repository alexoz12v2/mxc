#include "avx.h"

// Required compiler flags:
// -mavx -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args -msse2avx

namespace mxc::platform::x86_64::avx
{

// float vector[8]
MXC_VECTOR_ABI auto load_f(float const *MXC_RESTRICT farrAligned32) -> v256f
{
    auto pf = (decltype(farrAligned32))MXC_ASSUME_ALIGNED(farrAligned32, 32);
    v256f v = _mm256_load_ps(pf);
    return v;
}

MXC_VECTOR_ABI auto store_f(v256f v, float *MXC_RESTRICT out_farrAligned32) -> void
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

template <int32_t opi8_low> MXC_VECTOR_ABI auto cmp_f(v256f v0, v256f v1) -> v256f
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

template <int32_t ctrli8_low> MXC_VECTOR_ABI auto permute_f(v256f v) -> v256f
{
    v256f vRes = _mm256_permute_ps(v, ctrli8_low);
    return vRes;
}

// float vector[4]
template <int32_t opi8_low> MXC_VECTOR_ABI auto cmp_f(v128f v0, v128f v1) -> v128f
{
    v128f vRes = _mm_cmp_ps(v0, v1, opi8_low);
    return vRes;
}

template <int32_t ctrli8_low> MXC_VECTOR_ABI auto permute_f(v128f v) -> v128f
{
    v128f vRes = _mm_permute_ps(v, ctrli8_low);
    return vRes;
}

template <int32_t binaryFlag> MXC_VECTOR_ABI auto extractf128_f(v256f v) -> v128f
{
    v128f vRes = _mm256_extractf128_ps(v, binaryFlag);
    return vRes;
}

// double vector[4]
MXC_VECTOR_ABI auto load_d(double const *MXC_RESTRICT darrAligned32) -> v256d
{
    auto pd = (decltype(darrAligned32))MXC_ASSUME_ALIGNED(darrAligned32, 32);
    v256d v = _mm256_load_pd(pd);
    return v;
}

MXC_VECTOR_ABI auto store_d(v256d v, double *MXC_RESTRICT out_darrAligned32) -> void
{
    auto pd = (decltype(out_darrAligned32))MXC_ASSUME_ALIGNED(out_darrAligned32, 32);
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

template <int32_t opi8_low> MXC_VECTOR_ABI auto cmp_d(v256d v0, v256d v1) -> v256d
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

template <int32_t ctrli8_low> MXC_VECTOR_ABI auto permute_d(v256d v) -> v256d
{
    v256d vRes = _mm256_permute_pd(v, ctrli8_low);
    return vRes;
}

// double vector[2]
template <int32_t opi8_low> MXC_VECTOR_ABI auto cmp_d(v128d v0, v128d v1) -> v128d
{
    v128d vRes = _mm_cmp_pd(v0, v1, opi8_low);
    return vRes;
}

template <int32_t ctrli8_low> MXC_VECTOR_ABI auto permute_d(v128d v) -> v128d
{
    v128d vRes = _mm_permute_pd(v, ctrli8_low);
    return vRes;
}

template <int32_t binaryFlag> MXC_VECTOR_ABI auto extractf128_d(v256d v) -> v128d
{
    v128d vRes = _mm256_extractf128_pd(v, binaryFlag);
    return vRes;
}

// int8_t vector[32]
MXC_VECTOR_ABI auto load_i8(int8_t const *MXC_RESTRICT i8arrAligned32) -> v256i8
{
    auto pi8 = (v256i8 const *MXC_RESTRICT)MXC_ASSUME_ALIGNED(i8arrAligned32, 32);
    v256i8 v = _mm256_load_si256(pi8);
    return v;
}

MXC_VECTOR_ABI auto store_i8(v256i8 v, int8_t *MXC_RESTRICT out_i8arrAligned32) -> void
{
    auto pi8 = (v256i8 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i8arrAligned32, 32);
    _mm256_store_si256(pi8, v);
}

// int16_t vector[16]
MXC_VECTOR_ABI auto load_i16(int16_t const *MXC_RESTRICT i16arrAligned32) -> v256i16
{
    auto pi16 = (v256i16 const *MXC_RESTRICT)MXC_ASSUME_ALIGNED(i16arrAligned32, 32);
    v256i16 v = _mm256_load_si256(pi16);
    return v;
}

MXC_VECTOR_ABI auto store_i16(v256i16 v, int8_t *MXC_RESTRICT out_i16arrAligned32) -> void
{
    auto pi16 = (v256i16 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i16arrAligned32, 32);
    _mm256_store_si256(pi16, v);
}

// int32_t vector[8]
MXC_VECTOR_ABI auto load_i32(int32_t const *MXC_RESTRICT i32arrAligned32) -> v256i32
{
    auto pi32 = (v256i32 const *MXC_RESTRICT)MXC_ASSUME_ALIGNED(i32arrAligned32, 32);
    v256i32 v = _mm256_load_si256(pi32);
    return v;
}

MXC_VECTOR_ABI auto store_i32(v256i32 v, int32_t *MXC_RESTRICT out_i32arrAligned32) -> void
{
    auto pi32 = (v256i32 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i32arrAligned32, 32);
    _mm256_store_si256(pi32, v);
}

// int64_t vector[4]
MXC_VECTOR_ABI auto load_i64(int64_t const *MXC_RESTRICT i64arrAligned32) -> v256i64
{
    auto pi64 = (v256i64 const *MXC_RESTRICT)MXC_ASSUME_ALIGNED(i64arrAligned32, 32);
    v256i64 v = _mm256_load_si256(pi64);
    return v;
}

MXC_VECTOR_ABI auto store_i64(v256i64 v, int8_t *MXC_RESTRICT out_i64arrAligned32) -> void
{
    auto pi64 = (v256i64 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i64arrAligned32, 32);
    _mm256_store_si256(pi64, v);
}

MXC_VECTOR_ABI auto addsub_f(v256f v0, v256f v1) -> v256f;
MXC_VECTOR_ABI auto addsub_d(v256d v0, v256d v1) -> v256d;

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

template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto extractf128_ix(v256ix v0) -> v128ix;

MXC_VECTOR_ABI auto maskload_f(
    float const *MXC_RESTRICT farrAligned16, 
    v128ix vMask) -> v128f;
MXC_VECTOR_ABI auto maskload256_f(
    float const *MXC_RESTRICT farrAligned32, 
    v256ix vMask) -> v256f;
MXC_VECTOR_ABI auto maskload_d(
    double const *MXC_RESTRICT darrAligned16, 
    v128ix vMask) -> v128d;
MXC_VECTOR_ABI auto maskload256_d(
    double const *MXC_RESTRICT darrAligned32, 
    v256ix vMask) -> v256d;

MXC_VECTOR_ABI auto maskstore_f(
    v128f v, 
    float *MXC_RESTRICT farrAligned16, 
    v128ix mask) -> void;
MXC_VECTOR_ABI auto maskstore256_f(
    v256f v, 
    float *MXC_RESTRICT arrAligned32, 
    v256ix mask) -> void;
MXC_VECTOR_ABI auto maskstore_d(
    v128d v, 
    float *MXC_RESTRICT darrAligned16, 
    v128ix mask) -> void;
MXC_VECTOR_ABI auto maskstore256_d(
    v256d v, 
    double *MXC_RESTRICT arAligned32, 
    v256ix mask) -> void;

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto conditionalDotProduct_f(v256f v0, v256f v1) -> v256f
{
    v256f const vRes = _mm256_dp_ps(v0, v1, ctrl);
    return vRes;
}

template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto insertv128_f(v256f vSource, v128f vOperand) -> v256f
{
    v256f const vRes = _mm256_insertf128_ps(vSource, vOperand, lane);
    return vRes;
}
template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto insertv128_d(v256d vSource, v128d vOperand) -> v256d
{
    v256d const vRes = _mm256_insertf128_pd(vSource, vOperand, lane);
    return vRes;
}
template <int32_t lane> requires (lane == 0 || lane == 1)
MXC_VECTOR_ABI auto insertv128_ix(v256ix vSource, v128ix vOperand) -> v256ix
{
    v256ix const vRes = _mm256_insertf128_si256(vSource, vOperand, lane);
    return vRes;
}

MXC_VECTOR_ABI auto copyEvens_d(v256d vSrc) -> v256d
{
    v256d const vRes = _mm256_movedup_pd(vSrc);
    return vRes;
}
MXC_VECTOR_ABI auto copyEvens_f(v256f vSrc) -> v256f
{
    v256f const vRes = _mm256_moveldup_ps(vSrc);
    return vRes;
}
MXC_VECTOR_ABI auto copyOdds_f(v256f vSrc) -> v256f
{
    v256f const vRes = _mm256_movehdup_ps(vSrc);
    return vRes;
}

MXC_VECTOR_ABI auto negatives_d(v256d v) -> int32_t
{
    int32_t const vRes = _mm256_movemask_pd(v);
    return vRes;
}
MXC_VECTOR_ABI auto negatives_f(v256f v) -> int32_t
{
    int32_t const vRes = _mm256_movemask_ps(v);
    return vRes;
}

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)    
MXC_VECTOR_ABI auto permutelanes_f(v256f v0, v256f v1) -> v256f
{
    v256f const vRes = _mm256_permute2f128_ps(v0, v1, ctrl);
    return vRes;
}
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)    
MXC_VECTOR_ABI auto permutelanes_d(v256d v0, v256d v1) -> v256d
{
    v256d const vRes = _mm256_permute2f128_pd(v0, v1, ctrl);
    return vRes;
}
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)    
MXC_VECTOR_ABI auto permutelanes_ix(v256ix v0, v256ix v1) -> v256ix
{
    v256ix const vRes = _mm256_permute2f128_si256(v0, v1, ctrl);
    return vRes;
}

MXC_VECTOR_ABI auto permilvar_f(v128f v, v128ix mask) -> v128f
{
    v128f const vRes = _mm_permutevar_ps(v, mask);
    return vRes;
}
MXC_VECTOR_ABI auto permilvar_f(v256f v, v256ix mask) -> v256f
{
    v256f const vRes = _mm256_permutevar_ps(v, mask);
    return vRes;
}
MXC_VECTOR_ABI auto permilvar_d(v128d v, v128ix mask) -> v128d
{
    v128d const vRes = _mm_permutevar_pd(v, mask);
    return vRes;
}
MXC_VECTOR_ABI auto permilvar_d(v256d v, v256ix mask) -> v256d
{
    v256d const vRes = _mm256_permutevar_pd(v, mask);
    return vRes;
}

template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_f(v256f v0, v256f v1) -> v256f
{
    v256f const vRes = _mm256_shuffle_ps(v0, v1, ctrl);
    return vRes;
}
template <int32_t ctrl> requires ((ctrl & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_d(v256d v0, v256d v1) -> v256d
{
    v256d const vRes = _mm256_shuffle_pd(v0, v1, ctrl);
    return vRes;
}

MXC_VECTOR_ABI auto vtestsignCF_f(v128f v0, v128f v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm_testc_ps(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignCF_f(v256f v0, v256f v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm256_testc_ps(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignCF_d(v128d v0, v128d v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm_testc_pd(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignCF_d(v256d v0, v256d v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm256_testc_pd(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignZF_f(v128f v0, v128f v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm_testz_ps(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignZF_f(v256f v0, v256f v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm256_testz_ps(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignZF_d(v128d v0, v128d v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm_testz_pd(v0, v1));
    return vRes;
}
MXC_VECTOR_ABI auto vtestsignZF_d(v256d v0, v256d v1) -> bool
{
    bool const vRes = static_cast<bool>(_mm256_testz_pd(v0, v1));
    return vRes;
}

MXC_VECTOR_ABI auto vunpckh_f(v256f v0, v256f v1) -> v256f
{
    v256f const vRes = _mm256_unpackhi_ps(v0, v1);
    return vRes;
}
MXC_VECTOR_ABI auto vunpckh_d(v256d v0, v256d v1) -> v256d
{
    v256d const vRes = _mm256_unpackhi_pd(v0, v1);
    return vRes;
}
MXC_VECTOR_ABI auto vunpckl_f(v256f v0, v256f v1) -> v256f
{
    v256f const vRes = _mm256_unpacklo_ps(v0, v1);
    return vRes;
}
MXC_VECTOR_ABI auto vunpckl_d(v256d v0, v256d v1) -> v256d
{
    v256d const vRes = _mm256_unpacklo_pd(v0, v1);
    return vRes;
}
} // namespace mxc::platform::x86_64::avx
