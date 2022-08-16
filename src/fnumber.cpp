#include "fnumber.hpp"

#include "common.hpp"

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <limits>
#include <bit>

namespace mmath
{
    // result given as a float to get bigger numbers with 32 bits
    MMATH_FORCE_INLINE auto constexpr floor(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        int8_t const x_sign = -2*static_cast<int8_t>(std::bit_cast<uint32_t>(x) >> 31u)+1;
        float const x_truncated = x_sign*static_cast<float>(static_cast<uint64_t>(abs(x)));
        return x_truncated;
    }
    
    MMATH_FORCE_INLINE auto constexpr trunc(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = floor(x);
        return res;
    }
    
    MMATH_FORCE_INLINE auto constexpr ceil(float const x) -> float 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = floor(x)+1.f;
        return res;
    }
    
    MMATH_FORCE_INLINE auto constexpr round(float const x) -> float 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = frac(x) > 0x1p-1f ? ceil(x) : trunc(x);
        return res;
    }
    
    MMATH_FORCE_INLINE auto constexpr frac(float const x) -> float 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = abs(x) - trunc(x);
        return res;
    }
    
    MMATH_FORCE_INLINE auto constexpr mod(float const x, float const y) -> float 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        float const res = x-y*static_cast<int64_t>(x/y);
        return res;
    }
    
    auto constexpr factorial(float const x) -> float 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x > 0 && "Stirling's approximation works for x > 0");
        assert(x <= 34.f && "function 'factorial' will overflow with inputs bigger "
               "than 34.f\n");
        
        // Stirling's approximation https://en.wikipedia.org/wiki/Stirling%27s_approximation
        float constexpr sqrt_2pi = 2.50662827463f;
        float constexpr oneovere = 0.367879441171f;
        float const res = srqt_2pi * pow(oneovere*x, x);
        return res;
    }
    
    auto constexpr gamma(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x > 0 && "Stirling's approximation works for x > 0");
        float const res = factorial(x - 1.f);
        return res;
    }
    
    auto constexpr binomial_coeff(float const x, float const k) -> float 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        // gamma, lngamma, exp required
        // binomial_coeff(n,k) == exp(lngamma(k+1)-lngamma(k+1)-lngamma(n-k+1))
    }
    
    auto constexpr gcd() -> int32_t {}
    auto constexpr lcm() -> int32_t {}
    MMATH_FORCE_INLINE auto constexpr abs(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        float const res = x > 0.f ? x : -x;
        return res;
    }
    
    MMATH_FORCE_INLINE auto constexpr min(float const x, float const y) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(y);
        float const res = x > y ? y : x;
        return res;
    }
    
    MMATH_FORCE_INLINE auto constexpr max(float const x, float const y) -> bool
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        float const res = min(y, x);
        return res;
    }
    
    MMATH_FORCE_INLINE 
        auto constexpr close(float const x,             float const y,
                             float const rel_tol=1e-9f, float const abs_tol=1e-8f) -> bool
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(y);
        bool const res = abs(x - y) <= max(rel_tol * max(abs(x), abs(y)), abs_tol);
        return res;
    }
}