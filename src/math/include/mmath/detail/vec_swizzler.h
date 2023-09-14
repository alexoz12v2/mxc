#ifndef MXC_MATH_VEC_SWIZZLER_H
#define MXC_MATH_VEC_SWIZZLER_H

#include <concepts>
#include <cstdint>
#include <utility>

namespace mxc::math
{
template <uint32_t begin, uint32_t end> inline void unroll(auto f)
{
    if constexpr (begin < end)
    {
        f.template operator()<begin>();
        unroll<begin + 1, end>(f);
    }
}

template <uint32_t I, uint32_t N, uint32_t... R> struct pick : pick<I - 1, R...>
{
};

template <uint32_t N, uint32_t... R> struct pick<0, N, R...> : std::integral_constant<uint32_t, N>
{
};

template <uint32_t I, uint32_t N, uint32_t... R> inline constexpr auto pick_v = pick<I, N, R...>::value;

template <typename T, uint32_t... comps> struct Vector;

template <typename T, uint32_t N> struct Vec_withSize
{
};

template <typename T> struct Vec_withSize<T, 1>
{
    using type = T;
};
template <typename T> struct Vec_withSize<T, 2>
{
    using type = Vector<T, 0, 1>;
};
template <typename T> struct Vec_withSize<T, 3>
{
    using type = Vector<T, 0, 1, 2>;
};
template <typename T> struct Vec_withSize<T, 4>
{
    using type = Vector<T, 0, 1, 2, 3>;
};

// Target Vector Type: This is the type of vector that can be assigned from the swizzled class. For example, when you
// swizzle components
//   from a larger vector (e.g., vec3) into a smaller target vector (e.g., vec2), the target vector type would be vec2.
// Scalar Type: This is the data type of the vector components, such as float or double.
// Size of Original Vector: This indicates the size of the original vector that you are swizzling from, such as 1 for
// vec1, 2 for vec2,
//   3 for vec3, and 4 for vec4.
// Component Indices: These are the indices of the components you are selecting to form the swizzle. For example, xy
// represents the swizzle
//   of the x and y components.
template <typename VecT, typename T, uint32_t vecDims, uint32_t... accessors> struct Swizzler
{
    static uint32_t constexpr accessorsCount = sizeof...(accessors);

    // this is the entire vector, but it's not a duplicate, because this is
    // part of a union
    T data[vecDims];

    constexpr operator VecT() const
    {
        VecT v;
        if constexpr (std::floating_point<decltype(v)> || std::integral<decltype(v)>)
        {
            static_assert(accessorsCount == 1, "to convert to scalar you need 1 component");
            v = data[pick_v<0, accessors...>];
        }
        else
        {
            unroll<0, vecDims>([&]<uint32_t i>() { v[i] = data[pick_v<i, accessors...>]; });
        }
        return v;
    }

    constexpr Swizzler &operator=(VecT other)
    {
        uint32_t i = 0;
        ((data[accessors] = other[i++]), ...);
        return *this;
    }

    constexpr Swizzler &operator=(std::initializer_list<T> other)
    {
        auto it = other.begin();
        ((data[accessors] = *it++), ...);
        return *this;
    }
};
} // namespace mxc::math

#endif // MXC_MATH_VEC_SWIZZLER_H
