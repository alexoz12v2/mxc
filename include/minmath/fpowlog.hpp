#ifndef MMATH_FPOWLOG_HPP
#define MMATH_FPOWLOG_HPP

#include <cstdint>

namespace mmath
{
    constexpr auto sqrt(float const x) -> float;
    struct sqrt_rsqrt_return_t {auto sqrt;float rsqrt;};
    constexpr auto sqrt_rsqrt(auto const x) -> sqrt_rsqrt_return_t;
    constexpr auto rsqrt(float const x) -> float;
    constexpr auto exp(float const x) -> float;
    constexpr auto expm1(float const x) -> float;
    constexpr auto ln(float const x) -> float;
    constexpr auto log(float const x) -> float;
    constexpr auto powi(float const x, int32_t const i) -> float;
    constexpr auto twoxpi(int8_t x) -> float;
    constexpr auto twoxp(float x) -> float;
    constexpr auto pow(float const x, float const y) -> float;
    constexpr auto lg(float const x) -> float;
    constexpr auto log10(float const x) -> float;
    constexpr auto lb(float const x) -> float;
    constexpr auto lbp1(float const x) -> float;
    constexpr auto log2(float const x) -> float;
    constexpr auto log(float const x, float const b) -> float;
}

#endif //MMATH_FPOWLOG_HPP
