#ifndef MMATH_FTRIG_HPP
#define MMATH_FTRIG_HPP

namespace mmath
{
    constexpr float sin(float const x);
    constexpr float cos(float const x);
    constexpr float tan(float const x);
    constexpr float asin(float x);
    constexpr float acos(float x);
    constexpr float atan(float const x);
    constexpr float atan2(float const x, float const y);
    constexpr float sinh(float const x);
    constexpr float cosh(float const x);
    constexpr float tanh(float const x);
    constexpr float asinh(float const x);
    constexpr float acosh(float const x);
    constexpr float atanh(float const x);
    constexpr float deg2rad(float const x);
    constexpr float rad2deg(float const x);
}

#endif // MMATH_FTRIG_HPP