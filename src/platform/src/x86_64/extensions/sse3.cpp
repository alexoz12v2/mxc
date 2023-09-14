#if defined(MXC_SSE_AS_AVX)
#include "sse3vex.h"
#else
#include "sse3.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse3vex
#else
namespace mxc::platform::x86_64::sse3
#endif
{
// float vector[4]
MXC_VECTOR_ABI auto addsub_f(v128f v0, v128f v1) -> v128f
{
    v128f const vRes = _mm_addsub_ps(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto duplicateEven2Odd_f(v128f v) -> v128f
{
    v128f const vRes = _mm_movehdup_ps(v);
    return vRes;
}

MXC_VECTOR_ABI auto duplicateOdd2Even_f(v128f v) -> v128f
{
    v128f const vRes = _mm_moveldup_ps(v);
    return vRes;
}

// double vector[2]
MXC_VECTOR_ABI auto loadBoth_d(double const *MXC_RESTRICT dSingleAligned16) -> v128d
{
    auto pd          = (decltype(dSingleAligned16))MXC_ASSUME_ALIGNED(dSingleAligned16, 16);
    v128d const vRes = _mm_loaddup_pd(pd);
    return vRes;
}

MXC_VECTOR_ABI auto duplicateDouble_d(v128d v) -> v128d
{
    v128d const vRes = _mm_movedup_pd(v);
    return vRes;
}

MXC_VECTOR_ABI auto addsub_d(v128d v0, v128d v1) -> v128d
{
    v128d const vRes = _mm_addsub_pd(v0, v1);
    return vRes;
}
} // namespace mxc::platform::x86_64::sse3
