//
// -msse -msse2 -mfpmath=sse -ffast-math -fno-trapping-math -mno-push-args -mno-sse2avx

#if defined(MXC_SSE_AS_AVX)
#include "sse2vex.h"
#else
#include "sse2.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse2vex
#else
namespace mxc::platform::x86_64::sse2
#endif
{

// float vector[4]
MXC_VECTOR_ABI auto load_f(float const * MXC_RESTRICT farrAligned16) -> v128f
{
	auto pf = (decltype(farrAligned16)) MXC_ASSUME_ALIGNED(farrAligned16, 16);
	v128f v = _mm_load_ps(pf); 
	return v;
}

MXC_VECTOR_ABI auto store_f(v128f v, float * MXC_RESTRICT out_farrAligned16) -> void
{
	auto pf = (decltype(out_farrAligned16)) MXC_ASSUME_ALIGNED(out_farrAligned16, 16);
	_mm_store_ps(pf, v);
}

MXC_VECTOR_ABI auto add_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_add_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sub_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_sub_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto mul_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_mul_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto div_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_div_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sqrt_f(v128f v) -> v128f
{
	v128f vRes = _mm_sqrt_ps(v);
	return vRes;
}

MXC_VECTOR_ABI auto rsqrt_f(v128f v) -> v128f
{
	v128f vRes = _mm_rsqrt_ps(v);
	return vRes;
}

MXC_VECTOR_ABI auto rcp_f(v128f v) -> v128f
{
	v128f vRes = _mm_rcp_ps(v);
	return vRes;
}

MXC_VECTOR_ABI auto max_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_max_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto min_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_min_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpeq_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_cmpeq_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpneq_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_cmpneq_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpge_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_cmpge_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpgt_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_cmpgt_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmplt_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_cmplt_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmple_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_cmple_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto or_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_or_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto xor_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_xor_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto and_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_and_ps(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto andnot_f(v128f v0, v128f v1) -> v128f
{
	v128f v = _mm_andnot_ps(v0, v1);
	return v;
}

// double vector[2]
MXC_VECTOR_ABI auto load_d(double const * MXC_RESTRICT darrAligned16) -> v128d
{
	auto pd = (decltype(darrAligned16)) MXC_ASSUME_ALIGNED(darrAligned16, 16);
	v128d v = _mm_load_pd(pd);
	return v;
}

MXC_VECTOR_ABI auto store_d(v128d v, double * MXC_RESTRICT out_darrAligned16) -> void
{
	auto pd = (decltype(out_darrAligned16)) MXC_ASSUME_ALIGNED(out_darrAligned16, 16);
	_mm_store_pd(pd, v);
}

MXC_VECTOR_ABI auto add_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_add_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sub_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_sub_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto mul_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_mul_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto div_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_div_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sqrt_d(v128d v) -> v128d
{
	v128d vRes = _mm_sqrt_pd(v);
	return vRes;
}

MXC_VECTOR_ABI auto max_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_max_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto min_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_min_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpeq_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_cmpeq_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpneq_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_cmpneq_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpge_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_cmpge_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpgt_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_cmpgt_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmplt_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_cmplt_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmple_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_cmple_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto or_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_or_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto xor_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_xor_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto and_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_and_pd(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto andnot_d(v128d v0, v128d v1) -> v128d
{
	v128d v = _mm_andnot_pd(v0, v1);
	return v;
}

// int8_t vector[16]
MXC_VECTOR_ABI auto load_i8(int8_t const * MXC_RESTRICT i8arrAligned16) -> v128i8
{
	auto pi = (v128i8 const * MXC_RESTRICT)MXC_ASSUME_ALIGNED(i8arrAligned16, 16);
	v128i8 v = _mm_load_si128(pi);
	return v;
}

MXC_VECTOR_ABI auto store_i8(v128i8 v, int8_t * MXC_RESTRICT out_i8arrAligned16) -> void
{
	auto pi = (v128i8 * MXC_RESTRICT)MXC_ASSUME_ALIGNED(out_i8arrAligned16, 16);
	_mm_store_si128(pi, v);
}

MXC_VECTOR_ABI auto add_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_add_epi8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sub_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_sub_epi8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto or_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_or_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto xor_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_xor_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto and_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_and_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto andnot_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_andnot_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto avg_u8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_avg_epu8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpeq_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_cmpeq_epi8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmplt_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_cmplt_epi8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpgt_i8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_cmpgt_epi8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto min_u8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_min_epu8(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto max_u8(v128i8 v0, v128i8 v1) -> v128i8
{
	v128i8 v = _mm_max_epu8(v0, v1);
	return v;
}

// int16_t vector[8]
MXC_VECTOR_ABI auto load_i16(int16_t const * MXC_RESTRICT i16arrAligned16) -> v128i16
{
	auto pi = (v128i16 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i16arrAligned16, 16);
	v128i16 v = _mm_load_si128(pi);
	return v;
}

MXC_VECTOR_ABI auto store_i16(v128i16 v, int16_t * MXC_RESTRICT out_i16arrAligned16) -> void
{
	auto pi = (v128i16 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i16arrAligned16, 16);
	_mm_store_si128(pi, v);
}

MXC_VECTOR_ABI auto add_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_add_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sub_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_sub_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto or_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_or_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto xor_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_xor_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto and_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_and_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto andnot_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_andnot_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto avg_u16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_avg_epu16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpeq_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i8 v = _mm_cmpeq_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmplt(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_cmplt_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpgt_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_cmpgt_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto maddadjacent_i16(v128i16 v0, v128i16 v1) -> v128i32
{
	v128i16 v = _mm_madd_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sll_i16(v128i16 v, v128i16 u64_low) -> v128i16
{
	v128i16 vRes = _mm_sll_epi16(v, u64_low);
	return vRes;
}

MXC_VECTOR_ABI auto slli_i16(v128i16 v, int32_t shiftAmount) -> v128i16
{
	v128i16 vRes = _mm_slli_epi16(v, shiftAmount);
	return vRes;
}

MXC_VECTOR_ABI auto srl_i16(v128i16 v0, v128i16 v1) -> v128i16
{
	v128i16 v = _mm_srl_epi16(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto srli_i16(v128i16 v, int32_t shiftAmount) -> v128i16
{
	v128i16 vRes = _mm_srli_epi16(v, shiftAmount);
	return vRes;
}

// int32_t vector[4]
MXC_VECTOR_ABI auto load_i32(int32_t const * MXC_RESTRICT i32arrAligned16) -> v128i32
{
	auto pi = (v128i32 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i32arrAligned16, 16);
	v128i32 v = _mm_load_si128(pi);
	return v;
}

MXC_VECTOR_ABI auto store_i32(v128i32 v, int32_t * MXC_RESTRICT out_i32arrAligned16) -> void
{
	auto pi = (v128i32 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i32arrAligned16, 16);
	_mm_store_si128(pi, v);
}

MXC_VECTOR_ABI auto add_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_add_epi32(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sub_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_sub_epi32(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto or_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_or_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto xor_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_xor_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto and_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_and_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto andnot_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_andnot_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpeq_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_cmpeq_epi32(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmplt_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_cmplt_epi32(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto cmpgt_i32(v128i32 v0, v128i32 v1) -> v128i32
{
	v128i32 v = _mm_cmpgt_epi32(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sll_i32(v128i32 v, v128i32 u64_low) -> v128i32
{
	v128i32 vRes = _mm_sll_epi32(v, u64_low);
	return vRes;
}

MXC_VECTOR_ABI auto slli_i32(v128i32 v, int32_t shiftAmount) -> v128i32
{
	v128i32 vRes = _mm_slli_epi32(v, shiftAmount);
	return vRes;
}

MXC_VECTOR_ABI auto srl_i32(v128i32 v, v128i32 u64_low) -> v128i32
{
	v128i32 vRes = _mm_srl_epi32(v, u64_low);
	return vRes;
}

MXC_VECTOR_ABI auto srli_i32(v128i32 v, int32_t shiftAmount) -> v128i32
{
	v128i32 vRes = _mm_srli_epi32(v, shiftAmount);
	return vRes;
}

// int64_t vector[2]
MXC_VECTOR_ABI auto load_i64(int64_t const * MXC_RESTRICT i64arrAligned16) -> v128i64
{
	auto pi = (v128i64 const * MXC_RESTRICT) MXC_ASSUME_ALIGNED(i64arrAligned16, 16);
	v128i64 v = _mm_load_si128(pi);
	return v;
}

MXC_VECTOR_ABI auto store_i64(v128i64 v, int64_t * MXC_RESTRICT out_i64arrAligned16) -> void
{
	auto pi = (v128i64 * MXC_RESTRICT) MXC_ASSUME_ALIGNED(out_i64arrAligned16, 16);
	_mm_store_si128(pi, v);
}

MXC_VECTOR_ABI auto add_i64(v128i64 v0, v128i64 v1) -> v128i64
{
	v128i64 v = _mm_add_epi64(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sub_i64(v128i64 v0, v128i64 v1) -> v128i64
{
	v128i64 v = _mm_sub_epi64(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto or_i64(v128i64 v0, v128i64 v1) -> v128i64
{
	v128i64 v = _mm_or_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto xor_i64(v128i64 v0, v128i64 v1) -> v128i64
{
	v128i64 v = _mm_xor_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto and_i64(v128i64 v0, v128i64 v1) -> v128i64
{
	v128i64 v = _mm_and_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto andnot_i64(v128i64 v0, v128i64 v1) -> v128i64
{
	v128i64 v = _mm_andnot_si128(v0, v1);
	return v;
}

MXC_VECTOR_ABI auto sll_i64(v128i64 v, v128i64 u64_low) -> v128i64
{
	v128i64 vRes = _mm_sll_epi64(v, u64_low);
	return vRes;
}

MXC_VECTOR_ABI auto slli_i64(v128i64 v, int32_t shiftAmount) -> v128i64
{
	v128i64 vRes = _mm_slli_epi64(v, shiftAmount);
	return vRes;
}

MXC_VECTOR_ABI auto srl_i64(v128i64 v, v128i64 u64_low) -> v128i64
{
	v128i64 vRes = _mm_srl_epi64(v, u64_low);
	return vRes;
}

MXC_VECTOR_ABI auto srli_i64(v128i64 v, int32_t shiftAmount) -> v128i64
{
	v128i64 vRes = _mm_srli_epi64(v, shiftAmount);
	return vRes;
}

} // namespace mxc::platform::x86_64
