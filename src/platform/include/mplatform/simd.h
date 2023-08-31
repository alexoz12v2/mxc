#ifndef MXC_PLATFORM_SIMD_H
#define MXC_PLATFORM_SIMD_H

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

        #if MXC_DEBUG
        // https://stackoverflow.com/questions/15175654/sqrt-vs-rsqrt-vs-sse-mm-rsqrt-ps-benchmark
        VBase() {MXC_WARN("It seems that you are instancing a vectorized type. Remember, "
                          "if you want to ensure that your code is efficient, look at the compiler's disassembly. "
                          "One thing that often kills performance (and it looks like it might affect you) is moving data " 
                          "between memory and SSE registers unnecessarily.");}
        #endif

        union alignas(size) U
        {
            float farr[count];
            uint32_t u32arr[count];
            typename VectorizedType<T>::template f<esz> v; // NOTE: simd register intrinsics, when put as data members, they are stored on the stack
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
