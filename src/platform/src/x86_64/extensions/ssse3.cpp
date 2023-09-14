#if defined(MXC_SSE_AS_AVX)
#include "ssse3vex.h"
#else
#include "ssse3.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::ssse3vex
#else
namespace mxc::platform::x86_64::ssse3
#endif
{
MXC_VECTOR_ABI auto abs_i8(v128i8 v) -> v128i8
{
    v128i8 const vRes = _mm_abs_epi8(v);
    return vRes;
}

template <int32_t shift8_low>
    requires(shift8_low >= 0 && shift8_low < 256)
MXC_VECTOR_ABI auto concatAndShift_i8(v128i8 high, v128i8 low) -> v128i8
{
    v128i8 const vRes = _mm_alignr_epi8(high, low, shift8_low);
    return vRes;
}

MXC_VECTOR_ABI auto fma4EvenOdd_i8(v128i8 v0, v128i8 v1) -> v128i16
{
    v128i16 const vRes = _mm_maddubs_epi16(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto shuffle_i8(v128i8 v0, v128i8 v1) -> v128i8
{
    v128i8 const vRes = _mm_shuffle_epi8(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto condNegate_i8(v128i8 vals, v128i8 signs) -> v128i8
{
    v128i8 const vRes = _mm_sign_epi8(vals, signs);
    return vRes;
}

MXC_VECTOR_ABI auto abs_i16(v128i16 v) -> v128i16
{
    v128i16 const vRes = _mm_abs_epi16(v);
    return vRes;
}

MXC_VECTOR_ABI auto condNegate_i16(v128i16 vals, v128i16 signs) -> v128i16
{
    v128i16 const vRes = _mm_sign_epi16(vals, signs);
    return vRes;
}

MXC_VECTOR_ABI auto mulDiv2_i16(v128i16 v0, v128i16 v1) -> v128i16
{
    v128i16 const vRes = _mm_mulhrs_epi16(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto abs_i32(v128i32 v) -> v128i32
{
    v128i32 const vRes = _mm_abs_epi32(v);
    return vRes;
}

MXC_VECTOR_ABI auto condNegate_i32(v128i32 vals, v128i32 signs) -> v128i32
{
    v128i32 const vRes = _mm_sign_epi32(vals, signs);
    return vRes;
}
} // namespace mxc::platform::x86_64::ssse3
