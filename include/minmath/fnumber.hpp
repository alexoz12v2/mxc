#ifndef MINMATH_FNUMBER_HPP
#define  MINMATH_FNUMBER_HPP

#include <cstdint>

#include "common_private.hpp"

namespace mmath
{
    MMATH_FORCE_INLINE auto constexpr floor(float const x) -> float;
    MMATH_FORCE_INLINE auto constexpr trunc(float const x) -> float;
    MMATH_FORCE_INLINE auto constexpr ceil(float const x) -> float;
    MMATH_FORCE_INLINE auto constexpr round(float const x) -> float;
    MMATH_FORCE_INLINE auto constexpr frac(float const x) -> float;
    MMATH_FORCE_INLINE auto constexpr mod(float const x, float const y) -> float;
    auto constexpr factorial(float const x) -> float;
    auto constexpr binomial_coeff() -> float;
    auto constexpr gcd() -> int32_t;
    auto constexpr lcm() -> int32_t;
    MMATH_FORCE_INLINE auto constexpr abs(float const x) -> float;
    MMATH_FORCE_INLINE auto constexpr min(float const x, float const y) -> bool;
    MMATH_FORCE_INLINE auto constexpr max(float const x, float const y) -> bool;
    MMATH_FORCE_INLINE 
        auto constexpr close(float const x,             float const y,
                             float const rel_tol=1e-9f, float const abs_tol=1e-8f) -> bool;
    auto constexpr gamma(float const x) -> float;
    auto constexpr lngamma(float const x) -> float;
}

#endif // MINMATH_FNUMER_HPP
