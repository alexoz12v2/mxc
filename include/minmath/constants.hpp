
#ifndef MINMATH_CONSTANTS_HPP
#define MINMATH_CONSTANTS_HPP

#include <cstdint>
#include <bit>

namespace mmath 
{
	// inline for variables and functions allow to DEFINE, and not declare as usual, variables and
	// functions (not templates) in a HEADER, and including it in multiple translation units
	// without violating the ODR rule
    inline float constexpr pi = 3.14159265358979323846264338327950288419716939937510;
    inline float constexpr e  = 2.71828182845904523536028747135266249775724709369995;
    inline float constexpr m0 = std::bit_cast<float>(0x80000000);
    inline float constexpr p0 = std::bit_cast<float>(0x00000000);
    inline uint32_t constexpr m0_repr = 0x80000000;
    inline uint32_t constexpr p0_repr = 0x00000000;
}

#endif // MINMATH_CONSTANTS_HPP
