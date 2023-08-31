#ifndef MXC_PLATFORM_SIMD_H
#define MXC_PLATFORM_SIMD_H

#include "mplatform/cpu.generated.h"

#include <type_traits>

// NOTE: From the kvasir-io mpl library
//#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if defined(__cplusplus)
#if __cplusplus >= 201402L
///\exclude
#define KVASIR_CONSTEXPR_14
#endif
#endif

#if defined(_MSC_VER) && !defined(__GNUC__) && !defined(__clang__)
#if _MSC_VER == 1910
///\exclude
#define KVASIR_MSVC_2017
#elif _MSC_VER == 1900
///\exclude
#define KVASIR_MSVC_2015
#elif _MSC_VER == 1800
///\exclude
#define KVASIR_MSVC_2013
#endif
#elif __INTEL_COMPILER

#elif __GNUC__
#ifndef __clang__
///\exclude
#define KVASIR_GCC
#if __GNUC__ < 5
// old GCC
#else
#if __GNUC__ < 6
///\exclude
#define KVASIR_GCC5
#else
#if __GNUC__ < 7
///\exclude
#define KVASIR_GCC6
#else
///\exclude
#define KVASIR_GCC7
#endif
#endif
#endif
#else
///\exclude
#define KVASIR_CLANG
#if __clang_major__ == 3
#if __clang_minor__ == 5
///\exclude
#define KVASIR_CLANG_35
#elif __clang_minor__ == 6
///\exclude
#define KVASIR_CLANG_36
#elif __clang_minor__ == 7
#define KVASIR_CLANG_37
#endif
#endif
#endif
#endif

namespace kvasir::mpl 
{
    template <bool>
    struct conditional;

    template <>
    struct conditional<true> {
        template <typename A, typename B>
        using f = A;
    };

    template <>
    struct conditional<false> {
        template <typename A, typename B>
        using f = B;
    };

    /// wrapper which represents bool types
    template <bool Value>
    struct bool_ {
        static constexpr bool value = Value;
    };
    /// universal true type in the library
    using true_ = bool_<true>;
    /// universal false type in the library
    using false_ = bool_<false>;

    struct identity {
        template <typename T>
        using f = T;
    };

    namespace eager {
        template <typename T>
        using identity = T;
    }    

    template <typename C = identity>
    struct is_integral {
        template <typename T>
        using f = typename C::template f<bool_<std::is_integral<T>::value>>;
    };

    template <typename C = identity>
    struct is_floating_point {
        template <typename T>
        using f = typename C::template f<bool_<std::is_floating_point<T>::value>>;
    };

    template <typename C = identity>
    struct is_same {
        template <typename T, typename U>
        using f = typename C::template f<bool_<std::is_same<T, U>::value>>;
    };   

    template <typename C = identity>
    struct is_standard_layout {
        template <typename T>
        using f = typename C::template f<bool_<std::is_standard_layout<T>::value>>;
    };

    template <template <typename...> class F, typename C = identity>
    struct cfl {
        template <typename... Ts>
        using f = typename dcall<C, sizeof...(Ts)>::template f<
                typename dcallf<bool(sizeof...(Ts) > 0)>::template f1<F, Ts...>::type>;
    };

    template <template <typename...> class F>
    struct cfl<F, identity> {
        template <typename... Ts>
        using f = typename dcallf<bool(sizeof...(Ts) > 0)>::template f1<F, Ts...>::type;
    };

    template <template <typename...> class F, typename C = identity>
    struct cfe {
        template <typename... Ts>
        using f = typename dcall<C, sizeof...(Ts)>::template f<
            typename dcallf<bool(sizeof...(Ts) > 0)>::template f1<F, Ts...>>;
    };

    template <template <typename...> class F>
    struct cfe<F, identity> {
        template <typename... Ts>
        using f = typename dcallf<bool(sizeof...(Ts) > 0)>::template f1<F, Ts...>;
    };

    template <typename... Ts>
    struct list {};
    namespace detail {
        // recursive list, for internal use only
        template <typename Head, typename Tail>
        struct rlist {};

        using rlist_tail_of8 = rlist<list<>, 
                               rlist<list<>, 
                               rlist<list<>, 
                               rlist<list<>, 
                               rlist<list<>, 
                               rlist<list<>, 
                               rlist<list<>, 
                               rlist<list<>, void>>>>>>>>;
    } // namespace detail

    using listify = cfe<list>;

    template <typename S>
    struct sequencify;
    template <template <typename...> class S, typename... Ts>
    struct sequencify<S<Ts...>> {
            using type = cfe<S>;
    };

    template <typename... Ts>
    list<Ts...> make_list(Ts...) {
            return {};
    }

    namespace detail {
        template <typename C, typename L, typename... Ts>
        struct unpack_impl;
        template <typename C, template <typename...> class Seq, typename... Ls, typename... Ts>
        struct unpack_impl<C, Seq<Ls...>, Ts...> {
            using type = typename dcall<C, sizeof...(Ls)>::template f<Ts..., Ls...>;
        };
    } // namespace detail

    template <typename C>
    struct unpack {
        template <typename... Ls>
        using f = typename detail::unpack_impl<C, Ls...>::type;
    };

    /// \brief call a continuation (left parameter) with a variadic pack
    template <typename C, typename... Ts>
    using call = typename dcall<C, sizeof...(Ts)>::template f<Ts...>;

    template <typename C = identity>
    struct call_f {
        template <typename... Ts>
        using f = typename C::template f<dcallf<(sizeof...(Ts) < 10000)>::template f1<call, Ts...>>;
    };

    template <>
    struct call_f<identity> {
        template <typename... Ts>
        using f = typename dcallf<(sizeof...(Ts) < 10000)>::template f1<call, Ts...>;
    };

    template <unsigned long long Value>
    struct uint_ {
        static constexpr unsigned long long value = Value;
    };

    template <long long Value>
    struct int_ {
        static constexpr long long value = Value;
    };

    template <typename C = identity>
    struct front {
        template <typename T, typename... Ts>
        using f = typename C::template f<T>;
    };

    template <>
    struct front<identity> {
        template <typename T, typename... Ts>
        using f = T;
    };

    namespace detail {
        template <bool b, typename C>
        struct dependant_impl;
        template <typename C>
        struct dependant_impl<true, C> : C {};
    } // namespace detail

    template <typename C, unsigned size>
    using dcall = typename detail::dependant_impl<static_cast<bool>(size < 100000), C>;

    template <bool>
    struct dcallf;

    template <>
    struct dcallf<true> {
        template <template <typename...> class F1, typename... Ts>
        using f1 = F1<Ts...>;
        template <template <typename...> class F1, template <typename...> class F2,
                  typename... Ts>
        using f2 = F1<F2<Ts...>>;
    };

    template <>
    struct dcallf<false> {
        template <template <typename...> class F1, typename... Ts>
        using f1 = F1<>;
        template <template <typename...> class F1, template <typename...> class F2,
                  typename... Ts>
        using f2 = F1<F2<>>;
    };

    namespace detail {
        template <typename C, typename L, typename... Ts>
        struct unpack_impl;
        template <typename C, template <typename...> class Seq, typename... Ls, typename... Ts>
        struct unpack_impl<C, Seq<Ls...>, Ts...> {
            using type = typename dcall<C, sizeof...(Ls)>::template f<Ts..., Ls...>;
        };
    } // namespace detail

    template <typename C>
    struct unpack {
        template <typename... Ls>
        using f = typename detail::unpack_impl<C, Ls...>::type;
    };

    /// \brief call a continuation (left parameter) with a variadic pack
    template <typename C, typename... Ts>
    using call = typename dcall<C, sizeof...(Ts)>::template f<Ts...>;

    template <typename C = identity>
    struct call_f {
        template <typename... Ts>
        using f = typename C::template f<dcallf<(sizeof...(Ts) < 10000)>::template f1<call, Ts...>>;
    };

    /// \exclude
    template <>
    struct call_f<identity> {
        template <typename... Ts>
        using f = typename dcallf<(sizeof...(Ts) < 10000)>::template f1<call, Ts...>;
    };

    template <typename C = identity>
    struct front {
        template <typename T, typename... Ts>
        using f = typename C::template f<T>;
    };

    template <>
    struct front<identity> {
        template <typename T, typename... Ts>
        using f = T;
    };

    namespace detail {
        constexpr unsigned select_next_drop_step(unsigned N, unsigned) {
            return N > 256 ? 256 : N > 64 ? 64 : N > 16 ? 16 : N > 8 ? 8 : N;
        }

        template <unsigned N, typename C>
        struct drop_impl;

        template <typename C>
        struct drop_impl<0, C> {
            template <unsigned N, typename... Ts>
            using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };

        template <typename C>
        struct drop_impl<1, C> {
            template <unsigned N, typename T, typename... Ts>
            using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<2, C> {
            template <unsigned N, typename T0, typename T1, typename... Ts>
            using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<3, C> {
            template <unsigned N, typename T0, typename T1, typename T2, typename... Ts>
            using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<4, C> {
            template <unsigned N, typename T0, typename T1, typename T2, typename T3, typename... Ts>
            using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<5, C> {
            template <unsigned N, typename T0, typename T1, typename T2, typename T3, typename T4, typename... Ts>
            using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<6, C> {
                template <unsigned N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename... Ts>
                using f = typename conditional<(sizeof...(Ts)<1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<7, C> {
                template <unsigned N, typename T0, typename T1, typename T2, typename T3,
                          typename T4, typename T5, typename T6, typename... Ts>
                using f = typename conditional<(sizeof...(Ts) < 1000000)>::template f<C, void>::template f<Ts...>;
        };
        template <typename C>
        struct drop_impl<8, C> {
                template <unsigned N, typename T0, typename T1, typename T2, typename T3,
                          typename T4, typename T5, typename T6, typename T7, typename... Ts>
                using f = typename drop_impl<N - 8, C>::template f<(N - 8), Ts...>;
        };
        template <typename C>
        struct drop_impl<16, C> {
                template <unsigned N, typename T0, typename T1, typename T2, typename T3,
                          typename T4, typename T5, typename T6, typename T7, typename T8,
                          typename T9, typename T10, typename T11, typename T12, typename T13,
                          typename T14, typename T15, typename... Ts>
                using f = typename drop_impl<select_next_drop_step(N - 16, sizeof...(Ts)), C>::template f<(N - 16), Ts...>;
        };
        template <typename C>
        struct drop_impl<64, C> {
                template <unsigned N, typename T0, typename T1, typename T2, typename T3,
                          typename T4, typename T5, typename T6, typename T7, typename T8,
                          typename T9, typename T10, typename T11, typename T12, typename T13,
                          typename T14, typename T15, typename T16, typename T17, typename T18,
                          typename T19, typename T20, typename T21, typename T22, typename T23,
                          typename T24, typename T25, typename T26, typename T27, typename T28,
                          typename T29, typename T30, typename T31, typename T32, typename T33,
                          typename T34, typename T35, typename T36, typename T37, typename T38,
                          typename T39, typename T40, typename T41, typename T42, typename T43,
                          typename T44, typename T45, typename T46, typename T47, typename T48,
                          typename T49, typename T50, typename T51, typename T52, typename T53,
                          typename T54, typename T55, typename T56, typename T57, typename T58,
                          typename T59, typename T60, typename T61, typename T62, typename T63,
                          typename... Ts>
                using f = typename drop_impl<select_next_drop_step(N - 64, sizeof...(Ts)), C>::template f<(N - 64), Ts...>;
        };
        template <typename C>
        struct drop_impl<256, C> {
                template <unsigned N, typename T0, typename T1, typename T2, typename T3,
                          typename T4, typename T5, typename T6, typename T7, typename T8,
                          typename T9, typename T10, typename T11, typename T12, typename T13,
                          typename T14, typename T15, typename T16, typename T17, typename T18,
                          typename T19, typename T20, typename T21, typename T22, typename T23,
                          typename T24, typename T25, typename T26, typename T27, typename T28,
                          typename T29, typename T30, typename T31, typename T32, typename T33,
                          typename T34, typename T35, typename T36, typename T37, typename T38,
                          typename T39, typename T40, typename T41, typename T42, typename T43,
                          typename T44, typename T45, typename T46, typename T47, typename T48,
                          typename T49, typename T50, typename T51, typename T52, typename T53,
                          typename T54, typename T55, typename T56, typename T57, typename T58,
                          typename T59, typename T60, typename T61, typename T62, typename T63,
                          typename T64, typename T65, typename T66, typename T67, typename T68,
                          typename T69, typename T70, typename T71, typename T72, typename T73,
                          typename T74, typename T75, typename T76, typename T77, typename T78,
                          typename T79, typename T80, typename T81, typename T82, typename T83,
                          typename T84, typename T85, typename T86, typename T87, typename T88,
                          typename T89, typename T90, typename T91, typename T92, typename T93,
                          typename T94, typename T95, typename T96, typename T97, typename T98,
                          typename T99, typename T100, typename T101, typename T102, typename T103,
                          typename T104, typename T105, typename T106, typename T107, typename T108,
                          typename T109, typename T110, typename T111, typename T112, typename T113,
                          typename T114, typename T115, typename T116, typename T117, typename T118,
                          typename T119, typename T120, typename T121, typename T122, typename T123,
                          typename T124, typename T125, typename T126, typename T127, typename T128,
                          typename T129, typename T130, typename T131, typename T132, typename T133,
                          typename T134, typename T135, typename T136, typename T137, typename T138,
                          typename T139, typename T140, typename T141, typename T142, typename T143,
                          typename T144, typename T145, typename T146, typename T147, typename T148,
                          typename T149, typename T150, typename T151, typename T152, typename T153,
                          typename T154, typename T155, typename T156, typename T157, typename T158,
                          typename T159, typename T160, typename T161, typename T162, typename T163,
                          typename T164, typename T165, typename T166, typename T167, typename T168,
                          typename T169, typename T170, typename T171, typename T172, typename T173,
                          typename T174, typename T175, typename T176, typename T177, typename T178,
                          typename T179, typename T180, typename T181, typename T182, typename T183,
                          typename T184, typename T185, typename T186, typename T187, typename T188,
                          typename T189, typename T190, typename T191, typename T192, typename T193,
                          typename T194, typename T195, typename T196, typename T197, typename T198,
                          typename T199, typename T200, typename T201, typename T202, typename T203,
                          typename T204, typename T205, typename T206, typename T207, typename T208,
                          typename T209, typename T210, typename T211, typename T212, typename T213,
                          typename T214, typename T215, typename T216, typename T217, typename T218,
                          typename T219, typename T220, typename T221, typename T222, typename T223,
                          typename T224, typename T225, typename T226, typename T227, typename T228,
                          typename T229, typename T230, typename T231, typename T232, typename T233,
                          typename T234, typename T235, typename T236, typename T237, typename T238,
                          typename T239, typename T240, typename T241, typename T242, typename T243,
                          typename T244, typename T245, typename T246, typename T247, typename T248,
                          typename T249, typename T250, typename T251, typename T252, typename T253,
                          typename T254, typename T255, typename... Ts>
                using f = typename drop_impl<select_next_drop_step(N - 256, sizeof...(Ts)), C>::template f<(N - 256), Ts...>;
            };
    } // namespace detail
    template <typename N, typename C = listify>
    struct drop {
            template <typename... Ts>
            using f = typename detail::drop_impl<detail::select_next_drop_step(N::value,
                                                                               sizeof...(Ts)),
                                                 C>::template f<N::value, Ts...>;
    };

    // composition matching for common lambda cases
    template <typename C>
    struct drop<uint_<0>, front<C>> {
        template <typename T, typename... Ts>
        using f = typename C::template f<T>;
    };

    template <typename C>
    struct drop<uint_<1>, front<C>> {
        template <typename T0, typename T1, typename... Ts>
        using f = typename C::template f<T1>;
    };

    template <typename C>
    struct drop<uint_<2>, front<C>> {
        template <typename T0, typename T1, typename T2, typename... Ts>
        using f = typename C::template f<T2>;
    };

    template <typename C>
    struct drop<uint_<3>, front<C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
        using f = typename C::template f<T3>;
    };

    template <>
    struct drop<uint_<0>, front<identity>> {
        template <typename T, typename... Ts>
        using f = T;
    };

    template <>
    struct drop<uint_<1>, front<identity>> {
        template <typename T0, typename T1, typename... Ts>
        using f = T1;
    };

    template <>
    struct drop<uint_<2>, front<identity>> {
        template <typename T0, typename T1, typename T2, typename... Ts>
        using f = T2;
    };

    template <>
    struct drop<uint_<3>, front<identity>> {
        template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
        using f = T3;
    };

    namespace eager {
        template <typename List, unsigned Index>
        using drop = call<unpack<mpl::drop<mpl::uint_<Index>>>, List>;
    }


#if defined(__x86_64__)
#if !defined(__MSVC__)
#include <x86intrin.h>
#else
#include <immintrin.h>
#endif
#endif

#include <cstdint>
#include <cstring>

namespace mxc::simd 
{

#if defined(MXC_DEBUG)
    bool checkAlignment_dbg_FUNC(void const* MXC_RESTRICT ptr, uint64_t align)
    {
        // Ensure align is a power of 2 for correct alignment checks
        if ((align & (align - 1)) != 0) {
            return false;
        }
        
        // Cast the pointer to uint64_t and perform modulo operation
        return ((uint64_t)ptr % align) == 0;
    }

#define checkAlignment_dbg(ptr,align) checkAlignment_dbg_FUNC(ptr, align)
#else
#define checkAlignment_dbg(ptr,align)
#endif

#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
#define MXC_NOT_VECTORIZED_CONSTEXPR 
#else
#define MXC_NOT_VECTORIZED_CONSTEXPR constexpr 
#endif

    // TODO complete
    struct float16 {};
    struct bfloat16 {};
    
    enum class EPackSize 
    { 
        _8_Bytes,   _64 = _8_Bytes,
        _16_Bytes, _128 = _16_Bytes,
        _32_Bytes, _256 = _32_Bytes,
        _64_Bytes, _512 = _64_Bytes
    };

    consteval uint32_t u32FromPackSize(EPackSize esz) 
    {  
        switch(esz)
        {
            case EPackSize::_8_Bytes:  return 8;
            case EPackSize::_16_Bytes: return 16;
            case EPackSize::_32_Bytes: return 32;
            case EPackSize::_64_Bytes: return 64;
        }
    }
    
    template <typename T>
    concept VScalarType = kvasir::mpl::is_integral<>::f<T>::value || kvasir::mpl::is_floating_point<>::f<T>::value;

    #if defined(__x86_64__)
    using all_f = kvasir::mpl::list<__m64, __m128, __m256, __m512>;
    using all_i = kvasir::mpl::list<__m64, __m128i, __m256i, __m512i>;
    using all_d = kvasir::mpl::list<__m64, __m128d, __m256d, __m512d>;
    #if MXC_X86_64_SUPPORTED_AVX512float16
    using all_h = kvasir::mpl::list<__m128i, __m128h, __m256h, __m512h>;
    #endif
    #if MXC_X86_64_SUPPORTED_AVXbfloat16
    using all_bh = kvasir::mpl::list<__m128bh, __m256bh, __m512bh>;
    #endif
    #endif

    consteval uint32_t typeIndexFromPackSize(EPackSize esz) 
    {  
        switch(esz)
        {
            case EPackSize::_8_Bytes:  return 0;
            case EPackSize::_16_Bytes: return 1;
            case EPackSize::_32_Bytes: return 2;
            case EPackSize::_64_Bytes: return 3;
        }
    }

    template <VScalarType T>
    struct VectorizedType
    {
        using selectedList = 
            typename kvasir::mpl::conditional<kvasir::mpl::is_same<>::template f<T, float>::value>::template f<all_f,
            typename kvasir::mpl::conditional<kvasir::mpl::is_integral<>::template f<T>::value>::template f<all_i,
            typename kvasir::mpl::conditional<kvasir::mpl::is_same<>::template f<T, double>::value>::template f<all_d,
            
    #if MXC_X86_64_SUPPORTED_AVX512float16
            typename kvasir::mpl::conditional<kvasir::mpl::is_same<>::template f<T, float16>::value>::template f<all_h, all_bh> 
    #else
            void
    #endif
            >>>;

        template <EPackSize esz>
        using f = kvasir::mpl::eager::at<selectedList, typeIndexFromPackSize(esz)>;
    };
    
    template <VScalarType T, EPackSize esz>
    struct VBase
    {
        static uint32_t constexpr size = u32FromPackSize(esz);
        static uint32_t constexpr count = size / sizeof(T);

		union alignas(size) U
        {
			float farr[count];
			uint32_t u32arr[count];
            typename VectorizedType<T>::template f<esz> v;
		};

        #if defined(__x86_64__) && !MXC_X86_64_SUPPORTED_SSE
        #endif
    };

    template struct VBase<float, EPackSize::_32_Bytes>;
    
    struct alignas(32) V256f
    {
        static uint32_t constexpr size = 32;
        static uint32_t constexpr count = 8;

        // NOTE: farr points to float[8]. C++ doesnt support restrict arrays.
        MXC_INLINE static MXC_NOT_VECTORIZED_CONSTEXPR auto load(float const* MXC_RESTRICT farr) -> V256f;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto storeTo(float* MXC_RESTRICT farr) -> void;

        using Storage = 
    #if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
            __m256;
    #else
            U;
    #endif

        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator<=(V256f other) const -> V256f;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator>=(V256f other) const -> V256f;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator<(V256f other) const -> V256f;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator>(V256f other) const -> V256f;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator==(V256f other) const -> bool;

        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator+=(V256f other) -> V256f&;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator-=(V256f other) -> V256f&;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator*=(V256f other) -> V256f&;
        MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator/=(V256f other) -> V256f&;

        static bool constexpr bVectorized = 
    #if defined(__x86_64__) 
        ::kvasir::mpl::is_same<>::f<Storage, __m256>::value;
    #endif

        Storage v;
    };
    static_assert(sizeof(V256f) == 32);
    static_assert(alignof(V256f) == 32);
    static_assert(kvasir::mpl::is_standard_layout<>::f<V256f>::value);

    // NOTE: this is a "==" comparison. In higher level abstractions, build up a comparison with tolerance
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto equalMemberwise(V256f v1, V256f v2) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator+(V256f v1, V256f v2) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator-(V256f v1, V256f v2) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator*(V256f v1, V256f v2) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator/(V256f v1, V256f v2) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fma(V256f v1, V256f v2, V256f v3) -> V256f;       // v1[i] * v2[i] + v3[i]
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fmsub(V256f v1, V256f v2, V256f v3) -> V256f;     // v1[i] * v2[i] - v3[i]
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fnma(V256f v1, V256f v2, V256f v3) -> V256f;      // -v1[i] * v2[i] + v3[i]
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fnmsub(V256f v1, V256f v2, V256f v3) -> V256f;    // -v1[i] * v2[i] - v3[i]

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto abs(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto ceil(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto floor(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto round(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto lerp(float t, V256f v0, V256f v1) -> V256f;       // fmadd(t, b, fnmadd(t, a, a)) = (t*b+(-t*a+a)) = (1-t)*a+t*b
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto sqrt(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto rsqrt(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto reciprocal(V256f v1) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto max(V256f v1, V256f v2) -> V256f;
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto min(V256f v1, V256f v2) -> V256f;

			// 0 1 2 3 4 5 6 7
		    //  01  23  45  67
			//   0123    4567
			// 	  max
}

#endif // MXC_PLATFORM_SIMD_H
