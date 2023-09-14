#ifndef MINMATH_FNUMBER_HPP
#define MINMATH_FNUMBER_HPP

#include "common_private.h"
#include "mmath/common.h"
#include "mmath/powlog.h"

#include <bit>
#include <cstdint>
/*
 * Outline:
 *
 * mod(float const x, float const y) -> float;
 * factorial(float const x) -> float;
 * binomial_coeff() -> float;
 * gamma(float const x) -> float;
 * lngamma(float x) -> float;
 */

namespace mmath
{
namespace detail
{
static float constexpr sqrt_2pi      = 2.50662827463f;
static float constexpr oneovere      = 0.367879441171f;
static float constexpr ln_2pi_halved = 0.9189385332f;
}; // namespace detail

MXC_FORCEINLINE auto constexpr mod(float const x, float const y) -> float
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    float const res = x - y * static_cast<int64_t>(x / y);
    return res;
}

// TODO: stirling is accurate enough only for large numbers
auto constexpr factorial(float const x) -> float
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    assert(x > 0 && "Stirling's approximation works for x > 0");
    assert(x <= 34.f && "function 'factorial' will overflow with inputs bigger "
                        "than 34.f\n");

    // Stirling's approximation https://en.wikipedia.org/wiki/Stirling%27s_approximation
    float const res = detail::sqrt_2pi * pow(detail::oneovere * x, x);
    return res;
}

auto constexpr gamma(float const x) -> float
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    assert(x > 0.2f && "Rocktaeschel's approximation works for x > 0.2");

    // Rocktaeschel's approximation for large Re(x), the more precise one
    // Gamma(x)~= x^(x-0.5)*e^-x*sqrt(2*pi)*poly(x)
    // with poly(x)=1+1/(12*x)+1/(288*x^2)-139/(51840*x^3)-571/(2488320*x^4)+o(1/z^5)
    // I will approximate poly(x) with a piecewise approximation
    float const res =
        pow(x, x - 0.5f) * exp(-x) * detail::sqrt_2pi * (0.1f * (x - 0.2f) / (x * x - 0.14f * x + 0.0049f) + 1.f);
    return res;
}

auto constexpr lngamma(float x) -> float
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    // https://stackoverflow.com/questions/62458079/static-constexpr-variables-in-a-constexpr-function
    // static float constexpr ln_2pi_halved = 0.9189385332f; moved to detail namespace

    // logarithmic terms of the approximation
    float const lnx = log(x);
    float res       = (x - 0.5) * lnx - x + detail::ln_2pi_halved;

    // coefficients for the polynomial part
    float const x2 = 1377180 * x * x;
    float const x3 = 33052320 * x2 * x;
    float const x4 = 396627840 * x2 * x2;
    x *= 1063489;
    x += 92502;

    // Rocktaeschel's approximation
    res += (x4 + x3 + x2 - x) / x4;
    return res;
}

auto constexpr binomial_coeff(float const x, float const k) -> float
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    assert(x > 0.2f && k > 0.2f && "i");

    // gamma, lngamma, exp required
    // binomial_coeff(n,k) == exp(lngamma(x+1)-lngamma(k+1)-lngamma(n-k+1))
    float const res = exp(lngamma(x + 1.f) - lngamma(k + 1.f) - lngamma(x - k + 1.f));
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(res);
    return res;
}

// TODO: implement
// auto constexpr gcd() -> int32_t
// auto constexpr lcm() -> int32_t
} // namespace mmath

#endif // MINMATH_FNUMER_HPP
