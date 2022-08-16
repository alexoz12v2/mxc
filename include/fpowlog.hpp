#ifndef MMATH_FPOWLOG_HPP
#define MMATH_FPOWLOG_HPP

#include <cstdint>

namespace mmath
{
    constexpr float sqrt(float const x);
    struct sqrt_rsqrt_return_t {float sqrt;float rsqrt;};
    constexpr sqrt_rsqrt_return_t sqrt_rsqrt(float const x);
    constexpr float rsqrt(float const x);
    constexpr float exp(float const x);
    constexpr float expm1(float const x);
    constexpr float ln(float const x);
    constexpr float log(float const x);
    constexpr float powi(float const x, int32_t const x);
    constexpr float twoxpi(int8_t x);
    constexpr float twoxp(float x);
    constexpr float pow(float const x, float const y);
    constexpr float lg(float const x);
    constexpr float log10(float const x);
    constexpr float lb(float const x);
    constexpr float lbp1(float const x);
    constexpr float log2(float const x);
    constexpr float log(float const x, float const b);
}

#endif //MMATH_FPOWLOG_HPP