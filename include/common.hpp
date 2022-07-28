#ifndef MINMATH_COMMON_HPP
#define MINMATH_COMMON_HPP

#include <cstdint>

namespace mmath
{
    // code based on https://brnz.org/hbr/?p=1518
    [[nodiscard]]
        constexpr uint32_t bits(float const f);
    
    // infinity is present in c++ standard in the limits header, while
    // NaNs can be tested with condition (f != f). Therefore, only an implementation
    // of isDenormal has to be provided
    [[nodiscard]]
        constexpr bool isDenormal(float const f);
}

#endif // MINMATH_COMMON_HPP