#include "fma3.h"

namespace mxc::platform::x86_64::fma3
{

// float vector[4]
MXC_VECTOR_ABI auto fmadd_f(v128f a, v128f b, v128f c) -> v128f
{
    v128f fma = _mm_fmadd_ps(a, b, c);
    return fma;
}

// float vector[8]
MXC_VECTOR_ABI auto fmadd_f(v256f a, v256f b, v256f c) -> v256f
{
    v256f fma = _mm256_fmadd_ps(a, b, c);
    return fma;
}

// double vector[2]
MXC_VECTOR_ABI auto fmadd_d(v128d a, v128d b, v128d c) -> v128d
{
    v128d fma = _mm_fmadd_pd(a, b, c);
    return fma;
}

// double vector[4]
MXC_VECTOR_ABI auto fmadd_d(v256d a, v256d b, v256d c) -> v256d
{
    v256d fma = _mm256_fmadd_pd(a, b, c);
    return fma;
}

} // namespace mxc::platform::x86_64::fma3 
