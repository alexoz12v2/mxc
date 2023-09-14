#include "mplatform/arch_macros.h"

#include <immintrin.h>

#if defined(MXC_DEBUG)
#include <mcore/logging.h>
#define MXC_SIMD_PERMUTE_CTRL(p1, p2, p3, p4)                                                                          \
    []() -> int {                                                                                                      \
        MXC_ASSERT((p1) >= 0u && (p1) < 4u && (p2) >= 0u && (p2) < 4u && (p3) >= 0u && (p3) < 4u && (p4) >= 0u &&      \
                       (p4) < 4u,                                                                                      \
                   "permutation control indices must be in between 0 and 3, inclusive");                               \
        return ((p4 << 6) | (p3 << 4) | (p2 << 2) | p1);                                                               \
    }()
#else
#define MXC_SIMD_PERMUTE_CTRL(p1, p2, p3, p4) (((p4) << 6) | ((p3) << 4) | ((p2) << 2) | (p1))
#endif

#if defined(__GNUC__) || defined(__clang__)
#define MXC_ASSUME_ALIGNED(p, align) reinterpret_cast<void *>(__builtin_assume_aligned(p, align))
#elif defined(_MSC_VER)

namespace mxc::platform::x86_64::detail
{

template <unsigned i> struct highbitindex
{
    static unsigned constexpr value = 1 + highbitindex<(i >> 1)>::value;
};

template <> struct highbitindex<1>
{
    static unsigned constexpr value = 0;
};

} // namespace mxc::platform::x86_64::detail

// expects a POT
#define MXC_ASSUME_ALIGNED(p, align)                                                                                   \
    __assume(((((char *)p) - ((char *)0)) << (mxc::platform::x86_64::detail::highbitindex<align>::value)) == 0),       \
        reinterpret_cast<void *>(p) #else
#error "Compiler not supported"
#endif // defined(__GNUC__) || defined(__clang__)

namespace mxc::platform::x86_64
{

using v128bh = __m128bh;
using v128h  = __m128h;
using v128f  = __m128;
using v128d  = __m128d;

using v128i8  = __m128i;
using v128i16 = __m128i;
using v128i32 = __m128i;
using v128i64 = __m128i;
using v128u8  = __m128i;
using v128u16 = __m128i;
using v128u32 = __m128i;
using v128u64 = __m128i;

using v256bh = __m256bh;
using v256h  = __m256h;
using v256f  = __m256;
using v256d  = __m256d;

using v256i8  = __m256i;
using v256i16 = __m256i;
using v256i32 = __m256i;
using v256i64 = __m256i;
using v256u8  = __m256i;
using v256u16 = __m256i;
using v256u32 = __m256i;
using v256u64 = __m256i;

using v512bh = __m512bh;
using v512h  = __m512h;
using v512f  = __m512;
using v512d  = __m512d;

using v512i8  = __m512i;
using v512i16 = __m512i;
using v512i32 = __m512i;
using v512i64 = __m512i;
using v512u8  = __m512i;
using v512u16 = __m512i;
using v512u32 = __m512i;
using v512u64 = __m512i;

// use only if operating on bits, should be convertible to/from all integer types
using v128ix = __m128i;
using v256ix = __m256i;
using v512ix = __m512i;
} // namespace mxc::platform::x86_64
