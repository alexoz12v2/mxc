#ifndef MINMATH_COMMON_HPP
#define MINMATH_COMMON_HPP

#include <cstdint>

namespace mmath
{
    // code based on https://brnz.org/hbr/?p=1518
    [[nodiscard]]
        auto constexpr bits(float const f) -> int32_t;
    
    // infinity is present in c++ standard in the limits header, while
    // NaNs can be tested with condition (f != f). Therefore, only an implementation
    // of isDenormal has to be provided
    [[nodiscard]]
        auto constexpr isDenormal(float const f) -> bool;
    
    auto constexpr close(float const x, float const y) -> bool;
}

#endif // MINMATH_COMMON_HPP