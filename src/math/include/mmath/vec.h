#ifndef MXC_MATH_VEC_H
#define MXC_MATH_VEC_H

#include "common.h"
#include "detail/vec_base.h"

namespace mxc::math {

    template <typename T, uint32_t... comps>
    struct Vector : public VectorBase<T, comps...>
    {
        // 32 == sizeof an interval of complex numbers
        static_assert(sizeof(T) <= 32, "as of now, vector takes its parameters by copy as it's designed to contain numeric types");

        using VectorBase<T,comps...>::data;

        template <std::convertible_to<T>... Ts> requires (sizeof...(Ts) == sizeof...(comps))
        Vector(Ts... xs) : VectorBase<T,comps...>(xs...) {}

        Vector(std::array<T,sizeof...(comps)> const& list)
        : VectorBase<T,comps...>(list) {}

        Vector(std::array<T,sizeof...(comps)>&& list)
        : VectorBase<T,comps...>(list) {}

        Vector() : VectorBase<T,comps...>(std::array<T,sizeof...(comps)>{0}) {}

        MXC_INLINE constexpr auto operator[](uint32_t i) const -> T  { return data[i]; }
        MXC_INLINE constexpr auto operator[](uint32_t i)       -> T& { return data[i]; }
    };

    template <typename T, typename U, uint32_t... comps>
    MXC_INLINE constexpr auto operator+(Vector<T,comps...>v1, Vector<U,comps...> v2) -> Vector<decltype(std::declval<T>()+std::declval<U>()), comps...>
    {
        // TODO simd + concepts
        Vector<decltype(std::declval<T>()+std::declval<U>()), comps...> vsum;
        for (uint32_t i = 0; i != sizeof...(comps); ++i)
            vsum[i] = v1[i] + v2[i];
        return vsum;
    }

    template <typename T, typename U, uint32_t... comps>
    MXC_INLINE constexpr auto operator-(Vector<T,comps...> v1, Vector<U,comps...> v2) -> Vector<decltype(std::declval<T>()+std::declval<U>()), comps...>
    {
        // TODO simd
        Vector<decltype(std::declval<T>()+std::declval<U>()), comps...> vsum;
        for (uint32_t i = 0; i != sizeof...(comps); ++i)
            vsum[i] = v1[i] - v2[i];
        return vsum;
    }

    template <typename T, uint32_t... comps>
    MXC_INLINE constexpr auto operator*(Vector<T,comps...> v, T s) -> Vector<T, comps...>
    {
        // TODO simd
        Vector<T,comps...> v1;
        for (uint32_t i = 0; i != sizeof...(comps); ++i)
            v1[i] = s*v[i];
        return v1;
    }

    template <typename T, uint32_t... comps>
    MXC_INLINE constexpr auto operator*(T s, Vector<T,comps...> v) -> Vector<T, comps...>
    {
        return operator*(v,s);
    }

    template <typename T, uint32_t... comps>
    MXC_INLINE constexpr auto operator/(Vector<T,comps...> v, T s) -> Vector<T, comps...>
    {
        // TODO simd
        Vector<T,comps...> v1;
        for (uint32_t i = 0; i != sizeof...(comps); ++i)
            v1[i] = s*v[i];
        return v1;
    }

    template <typename T, uint32_t... comps>
    MXC_INLINE constexpr auto operator/(T s, Vector<T,comps...> v) -> Vector<T, comps...>
    {
        return operator*(v,s);
    }

    template <typename T, typename U, uint32_t... comps>
    MXC_INLINE constexpr auto dot(Vector<T,comps...>v1, Vector<U,comps...> v2) -> decltype(std::declval<T>()*std::declval<U>())
    {
        // TODO simd
        decltype(std::declval<T>()*std::declval<U>()) innerProd {0};
        for (uint32_t i = 0; i != sizeof...(comps); ++i)
            innerProd += v1[i]*v2[i];
        return innerProd;
    }

    template <typename T, typename U>
    MXC_INLINE constexpr auto cross(Vector<T,0,1,2> v1, Vector<U,0,1,2> v2) -> Vector<decltype(std::declval<T>()*std::declval<U>()),0,1,2>
    {
        using R = decltype(std::declval<T>()*std::declval<U>());
        return (v1.y*v2.z-v1.z*v2.y)*Vector<R,0,1,2>(1,0,0)
             - (v1.x*v2.z-v1.z*v2.x)*Vector<R,0,1,2>(0,1,0)
             + (v1.x*v2.y-v1.y*v2.x)*Vector<R,0,1,2>(0,0,1);
        
    }

    template <typename T, uint32_t... comps>
    MXC_INLINE constexpr auto hsum( Vector<T,comps...> v) -> T 
    {
        T res {v[0]};
        for (uint32_t i = 1; i != sizeof...(comps); ++i)
            res += v[i];
        return res;
    }

    template <typename T, uint32_t... comps>
    MXC_INLINE constexpr auto hprod( Vector<T,comps...> v) -> T 
    {
        T res {v[0]};
        for (uint32_t i = 1; i != sizeof...(comps); ++i)
            res *= v[i];
        return res;
    }

    template struct Vector<float,0,1>;
    using Vec2f = Vector<float,0,1>;
    static_assert(std::is_standard_layout_v<Vec2f>);

    template struct Vector<int32_t,0,1>;
    using Vec2i = Vector<int32_t,0,1>;
    static_assert(std::is_standard_layout_v<Vec2i>);

    template struct Vector<float,0,1,2>;
    using Vec3f = Vector<float,0,1,2>;
    static_assert(std::is_standard_layout_v<Vec3f>);

    template struct Vector<int32_t,0,1,2>;
    using Vec3i = Vector<int32_t,0,1,2>;
    static_assert(std::is_standard_layout_v<Vec3i>);

    template struct Vector<float,0,1,2,3>;
    using Vec4f = Vector<float,0,1,2,3>;
    static_assert(std::is_standard_layout_v<Vec4f>);

    template struct Vector<int32_t,0,1,2,3>;
    using Vec4i = Vector<int32_t,0,1,2,3>;
    static_assert(std::is_standard_layout_v<Vec4i>);
}

#endif //MXC_MATH_VEC_H
