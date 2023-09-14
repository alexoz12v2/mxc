#ifndef MXC_MATH_VEC_BASE_H
#define MXC_MATH_VEC_BASE_H

#include "vec_swizzler.h"

#include <array>

namespace mxc::math
{
// TODO: scalar type traits
template <typename T, uint32_t... comps> struct VectorBase;

template <typename T> struct VectorBase<T, 0, 1>
{
    using ValueType                = T;
    static uint32_t constexpr size = 2;

    VectorBase(T x, T y) : data{x, y}
    {
    }
    VectorBase(std::array<T, size> const &list) : data{list[0], list[1]}
    {
    }
    VectorBase(std::array<T, size> &&list) : data{list[0], list[1]}
    {
    }

    union {
        T data[size];
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 0> x, r, s;
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 1> y, g, t;

        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 1> xx, rr, ss;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 1> xy, rg, st;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 0> yx, gr, ts;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 1> yy, gg, tt;

        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 0> xxx, rrr, sss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 1> xxy, rrg, sst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 0> xyx, rgr, sts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 1> xyy, rgg, stt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 0> yxx, grr, tss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 1> yxy, grg, tst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 0> yyx, ggr, tts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 1> yyy, ggg, ttt;

        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 0> xxxx, rrrr, ssss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 1> xxxy, rrrg, ssst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 0> xxyx, rrgr, ssts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 1> xxyy, rrgg, sstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 0> xyxx, rgrr, stss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 1> xyxy, rgrg, stst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 0> xyyx, rggr, stts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 1> xyyy, rggg, sttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 0> yxxx, grrr, tsss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 1> yxxy, grrg, tsst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 0> yxyx, grgr, tsts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 1> yxyy, grgg, tstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 0> yyxx, ggrr, ttss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 1> yyxy, ggrg, ttst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 0> yyyx, gggr, ttts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 1> yyyy, gggg, tttt;
    };
};

template <typename T> struct alignas(16) VectorBase<T, 0, 1, 2>
{
    using ValueType                = T;
    static uint32_t constexpr size = 3;

    VectorBase(T x, T y, T z) : data{x, y, z}
    {
    }
    VectorBase(std::array<T, size> const &list) : data{list[0], list[1], list[2]}
    {
    }
    VectorBase(std::array<T, size> &&list) : data{list[0], list[1], list[2]}
    {
    }

    union {
        T data[size];

        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 0> x, r, s;
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 1> y, g, t;
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 2> z, b, p;

        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 0> xx, rr, ss;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 1> xy, rg, st;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 2> xz, rb, sp;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 0> yx, gr, ts;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 1> yy, gg, tt;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 2> yz, gb, tp;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 0> zx, br, ps;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 1> zy, bg, pt;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 2> zz, bb, pp;

        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 0> xxx, rrr, sss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 1> xxy, rrg, sst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 2> xxz, rrb, ssp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 0> xyx, rgr, sts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 1> xyy, rgg, stt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 2> xyz, rgb, stp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 0> xzx, rbr, sps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 1> xzy, rbg, spt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 2> xzz, rbb, spp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 0> yxx, grr, tss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 1> yxy, grg, tst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 2> yxz, grb, tsp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 0> yyx, ggr, tts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 1> yyy, ggg, ttt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 2> yyz, ggb, ttp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 0> yzx, gbr, tps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 1> yzy, gbg, tpt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 2> yzz, gbb, tpp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 0> zxx, brr, pss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 1> zxy, brg, pst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 2> zxz, brb, psp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 0> zyx, bgr, pts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 1> zyy, bgg, ptt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 2> zyz, bgb, ptp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 0> zzx, bbr, pps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 1> zzy, bbg, ppt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 2> zzz, bbb, ppp;

        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 0> xxxx, rrrr, ssss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 1> xxxy, rrrg, ssst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 2> xxxz, rrrb, sssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 0> xxyx, rrgr, ssts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 1> xxyy, rrgg, sstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 2> xxyz, rrgb, sstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 0> xxzx, rrbr, ssps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 1> xxzy, rrbg, sspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 2> xxzz, rrbb, sspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 0> xyxx, rgrr, stss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 1> xyxy, rgrg, stst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 2> xyxz, rgrb, stsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 0> xyyx, rggr, stts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 1> xyyy, rggg, sttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 2> xyyz, rggb, sttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 0> xyzx, rgbr, stps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 1> xyzy, rgbg, stpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 2> xyzz, rgbb, stpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 0> xzxx, rbrr, spss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 1> xzxy, rbrg, spst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 2> xzxz, rbrb, spsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 0> xzyx, rbgr, spts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 1> xzyy, rbgg, sptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 2> xzyz, rbgb, sptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 0> xzzx, rbbr, spps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 1> xzzy, rbbg, sppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 2> xzzz, rbbb, sppp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 0> yxxx, grrr, tsss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 1> yxxy, grrg, tsst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 2> yxxz, grrb, tssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 0> yxyx, grgr, tsts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 1> yxyy, grgg, tstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 2> yxyz, grgb, tstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 0> yxzx, grbr, tsps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 1> yxzy, grbg, tspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 2> yxzz, grbb, tspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 0> yyxx, ggrr, ttss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 1> yyxy, ggrg, ttst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 2> yyxz, ggrb, ttsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 0> yyyx, gggr, ttts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 1> yyyy, gggg, tttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 2> yyyz, gggb, tttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 0> yyzx, ggbr, ttps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 1> yyzy, ggbg, ttpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 2> yyzz, ggbb, ttpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 0> yzxx, gbrr, tpss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 1> yzxy, gbrg, tpst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 2> yzxz, gbrb, tpsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 0> yzyx, gbgr, tpts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 1> yzyy, gbgg, tptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 2> yzyz, gbgb, tptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 0> yzzx, gbbr, tpps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 1> yzzy, gbbg, tppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 2> yzzz, gbbb, tppp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 0> zxxx, brrr, psss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 1> zxxy, brrg, psst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 2> zxxz, brrb, pssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 0> zxyx, brgr, psts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 1> zxyy, brgg, pstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 2> zxyz, brgb, pstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 0> zxzx, brbr, psps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 1> zxzy, brbg, pspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 2> zxzz, brbb, pspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 0> zyxx, bgrr, ptss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 1> zyxy, bgrg, ptst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 2> zyxz, bgrb, ptsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 0> zyyx, bggr, ptts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 1> zyyy, bggg, pttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 2> zyyz, bggb, pttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 0> zyzx, bgbr, ptps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 1> zyzy, bgbg, ptpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 2> zyzz, bgbb, ptpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 0> zzxx, bbrr, ppss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 1> zzxy, bbrg, ppst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 2> zzxz, bbrb, ppsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 0> zzyx, bbgr, ppts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 1> zzyy, bbgg, pptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 2> zzyz, bbgb, pptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 0> zzzx, bbbr, ppps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 1> zzzy, bbbg, pppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 2> zzzz, bbbb, pppp;
    };
};

template <typename T> struct alignas(16) VectorBase<T, 0, 1, 2, 3>
{
    using ValueType                = T;
    static uint32_t constexpr size = 4;

    VectorBase(T x, T y, T z, T w) : data{x, y, z, w}
    {
    }
    VectorBase(std::array<T, size> const &list) : data{list[0], list[1], list[2], list[3]}
    {
    }
    VectorBase(std::array<T, size> &&list) : data{list[0], list[1], list[2], list[3]}
    {
    }

    union {
        T data[size];
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 0> x, r, s;
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 1> y, g, t;
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 2> z, b, p;
        Swizzler<typename Vec_withSize<T, 1>::type, ValueType, size, 3> w, a, q;

        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 0> xx, rr, ss;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 1> xy, rg, st;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 2> xz, rb, sp;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 0, 3> xw, ra, sq;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 0> yx, gr, ts;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 1> yy, gg, tt;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 2> yz, gb, tp;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 1, 3> yw, ga, tq;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 0> zx, br, ps;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 1> zy, bg, pt;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 2> zz, bb, pp;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 2, 3> zw, ba, pq;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 3, 0> wx, ar, qs;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 3, 1> wy, ag, qt;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 3, 2> wz, ab, qp;
        Swizzler<typename Vec_withSize<T, 2>::type, ValueType, size, 3, 3> ww, aa, qq;

        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 0> xxx, rrr, sss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 1> xxy, rrg, sst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 2> xxz, rrb, ssp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 0, 3> xxw, rra, ssq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 0> xyx, rgr, sts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 1> xyy, rgg, stt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 2> xyz, rgb, stp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 1, 3> xyw, rga, stq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 0> xzx, rbr, sps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 1> xzy, rbg, spt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 2> xzz, rbb, spp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 2, 3> xzw, rba, spq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 3, 0> xwx, rar, sqs;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 3, 1> xwy, rag, sqt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 3, 2> xwz, rab, sqp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 0, 3, 3> xww, raa, sqq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 0> yxx, grr, tss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 1> yxy, grg, tst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 2> yxz, grb, tsp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 0, 3> yxw, gra, tsq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 0> yyx, ggr, tts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 1> yyy, ggg, ttt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 2> yyz, ggb, ttp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 1, 3> yyw, gga, ttq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 0> yzx, gbr, tps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 1> yzy, gbg, tpt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 2> yzz, gbb, tpp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 2, 3> yzw, gba, tpq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 3, 0> ywx, gar, tqs;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 3, 1> ywy, gag, tqt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 3, 2> ywz, gab, tqp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 1, 3, 3> yww, gaa, tqq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 0> zxx, brr, pss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 1> zxy, brg, pst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 2> zxz, brb, psp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 0, 3> zxw, bra, psq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 0> zyx, bgr, pts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 1> zyy, bgg, ptt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 2> zyz, bgb, ptp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 1, 3> zyw, bga, ptq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 0> zzx, bbr, pps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 1> zzy, bbg, ppt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 2> zzz, bbb, ppp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 2, 3> zzw, bba, ppq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 3, 0> zwx, bar, pqs;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 3, 1> zwy, bag, pqt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 3, 2> zwz, bab, pqp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 2, 3, 3> zww, baa, pqq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 0, 0> wxx, arr, qss;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 0, 1> wxy, arg, qst;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 0, 2> wxz, arb, qsp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 0, 3> wxw, ara, qsq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 1, 0> wyx, agr, qts;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 1, 1> wyy, agg, qtt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 1, 2> wyz, agb, qtp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 1, 3> wyw, aga, qtq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 2, 0> wzx, abr, qps;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 2, 1> wzy, abg, qpt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 2, 2> wzz, abb, qpp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 2, 3> wzw, aba, qpq;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 3, 0> wwx, aar, qqs;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 3, 1> wwy, aag, qqt;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 3, 2> wwz, aab, qqp;
        Swizzler<typename Vec_withSize<T, 3>::type, ValueType, size, 3, 3, 3> www, aaa, qqq;

        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 0> xxxx, rrrr, ssss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 1> xxxy, rrrg, ssst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 2> xxxz, rrrb, sssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 0, 3> xxxw, rrra, sssq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 0> xxyx, rrgr, ssts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 1> xxyy, rrgg, sstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 2> xxyz, rrgb, sstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 1, 3> xxyw, rrga, sstq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 0> xxzx, rrbr, ssps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 1> xxzy, rrbg, sspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 2> xxzz, rrbb, sspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 2, 3> xxzw, rrba, sspq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 3, 0> xxwx, rrar, ssqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 3, 1> xxwy, rrag, ssqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 3, 2> xxwz, rrab, ssqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 0, 3, 3> xxww, rraa, ssqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 0> xyxx, rgrr, stss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 1> xyxy, rgrg, stst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 2> xyxz, rgrb, stsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 0, 3> xyxw, rgra, stsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 0> xyyx, rggr, stts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 1> xyyy, rggg, sttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 2> xyyz, rggb, sttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 1, 3> xyyw, rgga, sttq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 0> xyzx, rgbr, stps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 1> xyzy, rgbg, stpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 2> xyzz, rgbb, stpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 2, 3> xyzw, rgba, stpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 3, 0> xywx, rgar, stqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 3, 1> xywy, rgag, stqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 3, 2> xywz, rgab, stqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 1, 3, 3> xyww, rgaa, stqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 0> xzxx, rbrr, spss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 1> xzxy, rbrg, spst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 2> xzxz, rbrb, spsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 0, 3> xzxw, rbra, spsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 0> xzyx, rbgr, spts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 1> xzyy, rbgg, sptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 2> xzyz, rbgb, sptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 1, 3> xzyw, rbga, sptq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 0> xzzx, rbbr, spps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 1> xzzy, rbbg, sppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 2> xzzz, rbbb, sppp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 2, 3> xzzw, rbba, sppq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 3, 0> xzwx, rbar, spqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 3, 1> xzwy, rbag, spqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 3, 2> xzwz, rbab, spqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 2, 3, 3> xzww, rbaa, spqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 0, 0> xwxx, rarr, sqss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 0, 1> xwxy, rarg, sqst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 0, 2> xwxz, rarb, sqsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 0, 3> xwxw, rara, sqsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 1, 0> xwyx, ragr, sqts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 1, 1> xwyy, ragg, sqtt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 1, 2> xwyz, ragb, sqtp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 1, 3> xwyw, raga, sqtq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 2, 0> xwzx, rabr, sqps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 2, 1> xwzy, rabg, sqpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 2, 2> xwzz, rabb, sqpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 2, 3> xwzw, raba, sqpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 3, 0> xwwx, raar, sqqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 3, 1> xwwy, raag, sqqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 3, 2> xwwz, raab, sqqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 0, 3, 3, 3> xwww, raaa, sqqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 0> yxxx, grrr, tsss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 1> yxxy, grrg, tsst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 2> yxxz, grrb, tssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 0, 3> yxxw, grra, tssq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 0> yxyx, grgr, tsts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 1> yxyy, grgg, tstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 2> yxyz, grgb, tstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 1, 3> yxyw, grga, tstq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 0> yxzx, grbr, tsps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 1> yxzy, grbg, tspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 2> yxzz, grbb, tspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 2, 3> yxzw, grba, tspq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 3, 0> yxwx, grar, tsqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 3, 1> yxwy, grag, tsqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 3, 2> yxwz, grab, tsqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 0, 3, 3> yxww, graa, tsqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 0> yyxx, ggrr, ttss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 1> yyxy, ggrg, ttst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 2> yyxz, ggrb, ttsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 0, 3> yyxw, ggra, ttsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 0> yyyx, gggr, ttts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 1> yyyy, gggg, tttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 2> yyyz, gggb, tttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 1, 3> yyyw, ggga, tttq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 0> yyzx, ggbr, ttps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 1> yyzy, ggbg, ttpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 2> yyzz, ggbb, ttpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 2, 3> yyzw, ggba, ttpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 3, 0> yywx, ggar, ttqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 3, 1> yywy, ggag, ttqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 3, 2> yywz, ggab, ttqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 1, 3, 3> yyww, ggaa, ttqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 0> yzxx, gbrr, tpss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 1> yzxy, gbrg, tpst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 2> yzxz, gbrb, tpsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 0, 3> yzxw, gbra, tpsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 0> yzyx, gbgr, tpts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 1> yzyy, gbgg, tptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 2> yzyz, gbgb, tptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 1, 3> yzyw, gbga, tptq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 0> yzzx, gbbr, tpps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 1> yzzy, gbbg, tppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 2> yzzz, gbbb, tppp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 2, 3> yzzw, gbba, tppq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 3, 0> yzwx, gbar, tpqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 3, 1> yzwy, gbag, tpqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 3, 2> yzwz, gbab, tpqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 2, 3, 3> yzww, gbaa, tpqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 0, 0> ywxx, garr, tqss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 0, 1> ywxy, garg, tqst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 0, 2> ywxz, garb, tqsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 0, 3> ywxw, gara, tqsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 1, 0> ywyx, gagr, tqts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 1, 1> ywyy, gagg, tqtt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 1, 2> ywyz, gagb, tqtp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 1, 3> ywyw, gaga, tqtq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 2, 0> ywzx, gabr, tqps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 2, 1> ywzy, gabg, tqpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 2, 2> ywzz, gabb, tqpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 2, 3> ywzw, gaba, tqpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 3, 0> ywwx, gaar, tqqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 3, 1> ywwy, gaag, tqqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 3, 2> ywwz, gaab, tqqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 1, 3, 3, 3> ywww, gaaa, tqqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 0> zxxx, brrr, psss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 1> zxxy, brrg, psst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 2> zxxz, brrb, pssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 0, 3> zxxw, brra, pssq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 0> zxyx, brgr, psts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 1> zxyy, brgg, pstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 2> zxyz, brgb, pstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 1, 3> zxyw, brga, pstq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 0> zxzx, brbr, psps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 1> zxzy, brbg, pspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 2> zxzz, brbb, pspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 2, 3> zxzw, brba, pspq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 3, 0> zxwx, brar, psqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 3, 1> zxwy, brag, psqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 3, 2> zxwz, brab, psqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 0, 3, 3> zxww, braa, psqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 0> zyxx, bgrr, ptss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 1> zyxy, bgrg, ptst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 2> zyxz, bgrb, ptsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 0, 3> zyxw, bgra, ptsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 0> zyyx, bggr, ptts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 1> zyyy, bggg, pttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 2> zyyz, bggb, pttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 1, 3> zyyw, bgga, pttq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 0> zyzx, bgbr, ptps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 1> zyzy, bgbg, ptpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 2> zyzz, bgbb, ptpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 2, 3> zyzw, bgba, ptpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 3, 0> zywx, bgar, ptqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 3, 1> zywy, bgag, ptqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 3, 2> zywz, bgab, ptqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 1, 3, 3> zyww, bgaa, ptqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 0> zzxx, bbrr, ppss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 1> zzxy, bbrg, ppst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 2> zzxz, bbrb, ppsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 0, 3> zzxw, bbra, ppsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 0> zzyx, bbgr, ppts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 1> zzyy, bbgg, pptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 2> zzyz, bbgb, pptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 1, 3> zzyw, bbga, pptq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 0> zzzx, bbbr, ppps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 1> zzzy, bbbg, pppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 2> zzzz, bbbb, pppp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 2, 3> zzzw, bbba, pppq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 3, 0> zzwx, bbar, ppqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 3, 1> zzwy, bbag, ppqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 3, 2> zzwz, bbab, ppqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 2, 3, 3> zzww, bbaa, ppqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 0, 0> zwxx, barr, pqss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 0, 1> zwxy, barg, pqst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 0, 2> zwxz, barb, pqsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 0, 3> zwxw, bara, pqsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 1, 0> zwyx, bagr, pqts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 1, 1> zwyy, bagg, pqtt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 1, 2> zwyz, bagb, pqtp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 1, 3> zwyw, baga, pqtq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 2, 0> zwzx, babr, pqps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 2, 1> zwzy, babg, pqpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 2, 2> zwzz, babb, pqpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 2, 3> zwzw, baba, pqpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 3, 0> zwwx, baar, pqqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 3, 1> zwwy, baag, pqqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 3, 2> zwwz, baab, pqqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 2, 3, 3, 3> zwww, baaa, pqqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 0, 0> wxxx, arrr, qsss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 0, 1> wxxy, arrg, qsst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 0, 2> wxxz, arrb, qssp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 0, 3> wxxw, arra, qssq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 1, 0> wxyx, argr, qsts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 1, 1> wxyy, argg, qstt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 1, 2> wxyz, argb, qstp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 1, 3> wxyw, arga, qstq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 2, 0> wxzx, arbr, qsps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 2, 1> wxzy, arbg, qspt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 2, 2> wxzz, arbb, qspp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 2, 3> wxzw, arba, qspq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 3, 0> wxwx, arar, qsqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 3, 1> wxwy, arag, qsqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 3, 2> wxwz, arab, qsqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 0, 3, 3> wxww, araa, qsqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 0, 0> wyxx, agrr, qtss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 0, 1> wyxy, agrg, qtst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 0, 2> wyxz, agrb, qtsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 0, 3> wyxw, agra, qtsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 1, 0> wyyx, aggr, qtts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 1, 1> wyyy, aggg, qttt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 1, 2> wyyz, aggb, qttp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 1, 3> wyyw, agga, qttq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 2, 0> wyzx, agbr, qtps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 2, 1> wyzy, agbg, qtpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 2, 2> wyzz, agbb, qtpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 2, 3> wyzw, agba, qtpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 3, 0> wywx, agar, qtqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 3, 1> wywy, agag, qtqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 3, 2> wywz, agab, qtqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 1, 3, 3> wyww, agaa, qtqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 0, 0> wzxx, abrr, qpss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 0, 1> wzxy, abrg, qpst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 0, 2> wzxz, abrb, qpsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 0, 3> wzxw, abra, qpsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 1, 0> wzyx, abgr, qpts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 1, 1> wzyy, abgg, qptt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 1, 2> wzyz, abgb, qptp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 1, 3> wzyw, abga, qptq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 2, 0> wzzx, abbr, qpps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 2, 1> wzzy, abbg, qppt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 2, 2> wzzz, abbb, qppp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 2, 3> wzzw, abba, qppq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 3, 0> wzwx, abar, qpqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 3, 1> wzwy, abag, qpqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 3, 2> wzwz, abab, qpqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 2, 3, 3> wzww, abaa, qpqq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 0, 0> wwxx, aarr, qqss;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 0, 1> wwxy, aarg, qqst;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 0, 2> wwxz, aarb, qqsp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 0, 3> wwxw, aara, qqsq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 1, 0> wwyx, aagr, qqts;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 1, 1> wwyy, aagg, qqtt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 1, 2> wwyz, aagb, qqtp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 1, 3> wwyw, aaga, qqtq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 2, 0> wwzx, aabr, qqps;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 2, 1> wwzy, aabg, qqpt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 2, 2> wwzz, aabb, qqpp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 2, 3> wwzw, aaba, qqpq;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 3, 0> wwwx, aaar, qqqs;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 3, 1> wwwy, aaag, qqqt;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 3, 2> wwwz, aaab, qqqp;
        Swizzler<typename Vec_withSize<T, 4>::type, ValueType, size, 3, 3, 3, 3> wwww, aaaa, qqqq;
    };
};
} // namespace mxc::math

#endif // MXC_MATH_VEC_BASE_H
