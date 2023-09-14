#if defined(MXC_SSE_AS_AVX)
#include "ssevex.h"
#else
#include "sse.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::ssevex
#else
namespace mxc::platform::x86_64::sse
#endif
{

MXC_VECTOR_ABI auto add_f(v128f v0, v128f v1) -> v128f
{
    v128f const vSum = _mm_add_ps(v0, v1);
    return vSum;
}

MXC_VECTOR_ABI auto and_f(v128f v0, v128f v1) -> v128f
{
    v128f const vAnd = _mm_and_ps(v0, v1);
    return vAnd;
}

MXC_VECTOR_ABI auto andnot_f(v128f v0, v128f v1) -> v128f
{
    v128f const vNand = _mm_andnot_ps(v0, v1);
    return vNand;
}

MXC_VECTOR_ABI auto cmpeq_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpeq_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpge_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpge_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpgt_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpgt_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmple_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmple_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmplt_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmplt_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpneq_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpneq_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpnge_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpnge_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpngt_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpngt_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpnle_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpnle_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpnlt_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpnlt_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpAllNotNaN_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpord_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto cmpAnyNotNaN_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_cmpunord_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto div_f(v128f vDividend, v128f vDivisor) -> v128f
{
    v128f const vRes = _mm_div_ps(vDividend, vDivisor);
    return vRes;
}

MXC_VECTOR_ABI auto load_f(float const * MXC_RESTRICT farrAligned16) -> v128f
{
    auto farr = (decltype(farrAligned16)) MXC_ASSUME_ALIGNED(farrAligned16, 16);
    v128f const vRes = _mm_load_ps(farr);
    return vRes;
}

MXC_VECTOR_ABI auto max_f(v128f v0, v128f v1) -> v128f
{
    v128f const vMax = _mm_max_ps(v0, v1);
    return vMax;
}

MXC_VECTOR_ABI auto min_f(v128f v0, v128f v1) -> v128f
{
    v128f const vMin = _mm_min_ps(v0, v1);
    return vMin;
}

MXC_VECTOR_ABI auto mul_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_mul_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto or_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_or_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto rcp_f(v128f v) -> v128f
{
    v128f const vRes = _mm_rcp_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto rsqrt_f(v128f v) -> v128f
{
    v128f const vRes = _mm_rsqrt_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto zeroVec_f() -> v128f
{
    v128f const vZero = _mm_setzero_ps();
    return vZero;
}

template <uint32_t shuffledIdxs> requires ((shuffledIdxs & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_shuffle_ps(v0, v1, shuffledIdxs);
    return vRes;
}

MXC_VECTOR_ABI auto sqrt_f(v128f v) -> v128f
{
    v128f const vRes = _mm_sqrt_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto store_f(v128f v, float * MXC_RESTRICT out_farrAligned16) -> void
{
    auto farr = (decltype(out_farrAligned16)) MXC_ASSUME_ALIGNED(out_farrAligned16, 16);
    _mm_store_ps(farr, v);
}

MXC_VECTOR_ABI auto sub_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_sub_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto interleaveHigh_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_unpackhi_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto interleaveLow_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_unpacklo_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto xor_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_xor_ps(v0, v1);
    return vRes;
}

}
