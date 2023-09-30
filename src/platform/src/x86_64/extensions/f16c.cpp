#include "f16c.h"

namespace mxc::platform::x86_64::f16c
{

MXC_VECTOR_ABI auto F32ToF16(v128f v) -> v128ix     // _mm_cvtps_ph
{
    v128ix const vRes = _mm_cvtps_ph(v, _MM_FROUND_CUR_DIRECTION);
    return vRes;
}
MXC_VECTOR_ABI auto F32ToF16(v256f v) -> v128ix     // _mm256_cvtps_ph
{
    v128ix const vRes = _mm256_cvtps_ph(v, _MM_FROUND_CUR_DIRECTION);
    return vRes;
}
MXC_VECTOR_ABI auto F16ToF32(v128ix v) -> v128f     // _mm_cvtph_ps
{
    v128f const vRes = _mm_cvtph_ps(v);
    return vRes;
}
MXC_VECTOR_ABI auto F16ToF32_256(v128ix v) -> v256f     // _mm256_cvtph_ps
{
    v256f const vRes = _mm256_cvtph_ps(v);
    return vRes;
}

} // namespace mxc::platform::x86_64::f16c
