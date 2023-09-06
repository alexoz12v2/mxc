#ifndef MXC_MATH_COMMON_HPP
#define MXC_MATH_COMMON_HPP

#include "mmath/macros.h"
#include "mcore/macros.h"

#include <cstdint>
#include <bit>

// TODO refactor in a class similiar to numeric limits
#define MMATH_F32_MAX_SAFE_INTEGER 16777215

namespace mxc::math
{
    namespace detail 
    {
        constexpr auto countLeadingZeroes(uint64_t n) -> int32_t 
        {
            // De Brujin sequence
            char constexpr bitPosition[64] = {
                0,  1,  2,  7,  3, 13,  8, 19,  4, 25, 14, 28,  9, 34, 20, 40, 
                5, 17, 26, 38, 15, 46, 29, 48, 10, 31, 35, 54, 21, 50, 41, 57, 
                63,  6, 12, 18, 24, 27, 33, 39, 16, 37, 45, 47, 30, 53, 49, 56, 
                62, 11, 23, 32, 36, 44, 52, 55, 61, 22, 43, 51, 60, 42, 59, 58
            };
            
            // ceil to one less than the nearest bigger power of 2
            n |= (n >> 1);
            n |= (n >> 2);
            n |= (n >> 4);
            n |= (n >> 8);
            n |= (n >> 16);
            n |= (n >> 32);
            
            // then get the nearest smaller power of 2
            n= (n >> 1) + 1;
            
            // then count number of 0 from least significant bit using table
            return 63 - bitPosition[(n * 0x0218a392cd3d5dbf) >> 58];
        }
    }

    // code based on https://brnz.org/hbr/?p=1518
    // WARNING: THIS FUNCTION SHOULD NOT BE USED AS THERE IS IN C++20 std::bit_cast, which is
    // constexpr. It stays here because it has been a learning experience for me and I want to
    // revisit it from time to time
    auto bits(float const f) -> uint32_t;
    
    // infinity is present in c++ standard in the limits header, while
    // NaNs can be tested with condition (f != f). Therefore, only an implementation
    // of isDenormal has to be provided
    MXC_FORCEINLINE auto constexpr isDenormal(float const f) -> bool
    {
        if (f == 0)
            return false;
        
        // code snippet from the bits function
        int32_t exponent = 254;
        float abs_f = f < 0.f ? -f : f;
        
        while (abs_f < 0x1p87f)
        {
            abs_f *= 0x1p41f;
            exponent -= 41;
        }
        
        return exponent <= 0;
    }

    MXC_FORCEINLINE auto constexpr abs(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        float const res = x > 0.f ? x : -x;
        return res;
    }

    // result given as a float to get bigger numbers with 32 bits
    MXC_FORCEINLINE auto constexpr floor(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(MMATH_F32_MAX_SAFE_INTEGER > x && "flooring the number will result in precision loss");
        int8_t const x_sign = -2*static_cast<int8_t>(std::bit_cast<uint32_t>(x) >> 31u)+1;
        float const x_truncated = x_sign*static_cast<float>(static_cast<uint64_t>(abs(x)));

        return x_truncated;
    }

    MXC_FORCEINLINE auto constexpr ceil(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = floor(x)+1.f;
        return res;
    }

    MXC_FORCEINLINE auto constexpr frac(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = abs(x) - floor(x);
        return res;
    }

    MXC_FORCEINLINE auto constexpr round(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = frac(x) > 0x1p-1f ? ceil(x) : floor(x);
        return res;
    }

    MXC_FORCEINLINE auto constexpr min(float const x, float const y) -> bool
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(y);
        float const res = x > y ? y : x;
        return res;
    }

    MXC_FORCEINLINE auto constexpr max(float const x, float const y) -> bool
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        float const res = min(y, x);
        return res;
    }

    MXC_FORCEINLINE 
    auto constexpr close(float const x,             float const y,
                         float const rel_tol=1e-9f, float const abs_tol=1e-8f) -> bool
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(y);
        bool const res = abs(x - y) <= max(rel_tol * max(abs(x), abs(y)), abs_tol);
        return res;
    }
}

namespace mmath = mxc::math;

#endif // MXC_MATH_COMMON_HPP
