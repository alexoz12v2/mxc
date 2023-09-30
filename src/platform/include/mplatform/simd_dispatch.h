#ifndef MXC_PLATFORM_SIMD_DISPATCH_H
#define MXC_PLATFORM_SIMD_DISPATCH_H

#include "arch_macros.h"
#include "mcore/logging.h"

#if defined(MXC_ARCH_X86_64)
#include "x86_64/extensions/avx.h"
#include "x86_64/extensions/avx2.h"
#include "x86_64/extensions/avx512bw.h"
#include "x86_64/extensions/avx512cd.h"
#include "x86_64/extensions/avx512dq.h"
#include "x86_64/extensions/avx512f.h"
#include "x86_64/extensions/avx512vl.h"
#include "x86_64/extensions/bmi1.h"
#include "x86_64/extensions/common_types.h"
#include "x86_64/extensions/f16c.h"
#include "x86_64/extensions/fma3.h"
#include "x86_64/extensions/popcnt.h"
#include "x86_64/extensions/sse.h"
#include "x86_64/extensions/ssevex.h"
#include "x86_64/extensions/sse2.h"
#include "x86_64/extensions/sse2vex.h"
#include "x86_64/extensions/sse3.h"
#include "x86_64/extensions/sse3vex.h"
#include "x86_64/extensions/sse4_1.h"
#include "x86_64/extensions/sse4_1vex.h"
#include "x86_64/extensions/sse4_2.h"
#include "x86_64/extensions/sse4_2vex.h"
#include "x86_64/extensions/ssse3.h"
#include "x86_64/extensions/ssse3vex.h"
#endif // defined(MXC_ARCH_X86_64)

#include <type_traits> // std::underlying_type

namespace mxc::simd
{
/********************************************************************************
 * DO NOT USE DIRECT FUNCTIONS. 
 * PASSING DIRECTLY AVX REGISTERS WITHOUT ENABLING IT CHANGES ABI. 
 * BUILD UP HIGHER ORDER ABSTRACTIONS AND REMOVE THIS BROKEN DISPATCHING CODE
 ********************************************************************************/
// TODO: instead of chaining indirect calls to low level functions, provide for each instruction set higher level
// functionality to reduce the
//       number of dynamic dispatches
/*
 * Instructions to add a vectorized function:
 *  - declare its signature as "typedef ... <func name>_t(...)"
 *  - declare a dispatcher with MXC_SIMD_DISPATCHER_ATTRIB(<func name>_dispatch)...
 *  - ... and immediately after that, declare the actual function
 *  - in the 'extern "C"' section, define the actual dispatcher
 *  - in 'namespace detail', under the relevant architecture section, declare the vectorized overload of the function,
 * which are returned by the dispatcher
 *  - as a patch for msvc, which doesn't support indirect functions, whose overload is resolved by calling the
 * dispatcher at load time, global, inline pointers named g_<func name>_func are defined by initializing them calling
 * their associated dispatcher. Furthermore, the actual function declared in the third step is defined as empty Usage:
 *      MXC_SIMD_DISPATCH(<func name>, args...)
 */
typedef MXC_VECTOR_ABI void addfv_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                    uint32_t len);
MXC_SIMD_DISPATCHER_ATTRIB(addfv_dispatch)
MXC_VECTOR_ABI void addfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len);

typedef MXC_VECTOR_ABI void addf2_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(addf2_dispatch)
MXC_VECTOR_ABI void addf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void addf3_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(addf3_dispatch)
MXC_VECTOR_ABI void addf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void addf4_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(addf4_dispatch)
MXC_VECTOR_ABI void addf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void subfv_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                    uint32_t len);
MXC_SIMD_DISPATCHER_ATTRIB(subfv_dispatch)
MXC_VECTOR_ABI void subfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len);

typedef MXC_VECTOR_ABI void subf2_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(subf2_dispatch)
MXC_VECTOR_ABI void subf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void subf3_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(subf3_dispatch)
MXC_VECTOR_ABI void subf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void subf4_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(subf4_dispatch)
MXC_VECTOR_ABI void subf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void mulfv_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                    uint32_t len);
MXC_SIMD_DISPATCHER_ATTRIB(mulfv_dispatch)
MXC_VECTOR_ABI void mulfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len);

typedef MXC_VECTOR_ABI void mulf2_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(mulf2_dispatch)
MXC_VECTOR_ABI void mulf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void mulf3_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(mulf3_dispatch)
MXC_VECTOR_ABI void mulf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void mulf4_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(mulf4_dispatch)
MXC_VECTOR_ABI void mulf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void divfv_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                    uint32_t len);
MXC_SIMD_DISPATCHER_ATTRIB(divfv_dispatch)
MXC_VECTOR_ABI void divfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len);

typedef MXC_VECTOR_ABI void divf2_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(divf2_dispatch)
MXC_VECTOR_ABI void divf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void divf3_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(divf3_dispatch)
MXC_VECTOR_ABI void divf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

typedef MXC_VECTOR_ABI void divf4_t(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);
MXC_SIMD_DISPATCHER_ATTRIB(divf4_dispatch)
MXC_VECTOR_ABI void divf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res);

namespace detail
{

// functions
#if defined(MXC_ARCH_X86_64)

using namespace mxc::platform::x86_64;
MXC_VECTOR_ABI void addfv_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                              uint32_t len)
{
    MXC_WARN("AVX 256 bit operations should be used for long sequences of relatively cheap operations (i.e. not "
             "sqrt/div), as\n\t1) "
             "using AVX for one, cheap operation, will likely result in getting bandwidth limited\n\t2) Slow "
             "operations have lower latency on "
             "SSE(2,3,4.1,4.2, non-VEX or VEX)");
    MXC_ASSERT((len % 8 == 0),
               "[x86_64] to enable avx vectorization float32 vectors of length multiple of 8 is required");
    for (uint32_t i = 0; i < len; i += 8)
    {
        v256f va   = avx::load_f(a + i * sizeof(float));
        v256f vb   = avx::load_f(b + i * sizeof(float));
        v256f vRes = avx::add_f(va, vb);
        avx::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void addfv_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                               uint32_t len)
{
    MXC_ASSERT(len % 4 == 0,
               "[x86_64] to enable sse2 vectorization float32 vectors of length multiple of 4 is required");
    for (uint32_t i = 0; i < len; i += 4)
    {
        v128f va   = sse::load_f(a + i * sizeof(float));
        v128f vb   = sse::load_f(b + i * sizeof(float));
        v128f vRes = sse::add_f(va, vb);
        sse::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void addf2_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::add_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void addf2_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::add_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void addf3_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::add_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void addf3_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::add_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void addf4_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = sse::load_f(a);
    v128f vb   = sse::load_f(b);
    v128f vRes = sse::add_f(va, vb);
    sse::store_f(vRes, res);
}

MXC_VECTOR_ABI void addf4_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = ssevex::load_f(a);
    v128f vb   = ssevex::load_f(b);
    v128f vRes = ssevex::add_f(va, vb);
    ssevex::store_f(vRes, res);
}

MXC_VECTOR_ABI void subfv_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                              uint32_t len)
{
    MXC_WARN("AVX 256 bit operations should be used for long sequences of relatively cheap operations (i.e. not "
             "sqrt/div), as\n\t1) "
             "using AVX for one, cheap operation, will likely result in getting bandwidth limited\n\t2) Slow "
             "operations have lower latency on "
             "SSE(2,3,4.1,4.2, non-VEX or VEX)");
    MXC_ASSERT((len % 8 == 0),
               "[x86_64] to enable avx vectorization float32 vectors of length multiple of 8 is required");
    for (uint32_t i = 0; i < len; i += 8)
    {
        v256f va   = avx::load_f(a + i * sizeof(float));
        v256f vb   = avx::load_f(b + i * sizeof(float));
        v256f vRes = avx::sub_f(va, vb);
        avx::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void subfv_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                               uint32_t len)
{
    MXC_ASSERT(len % 4 == 0,
               "[x86_64] to enable sse2 vectorization float32 vectors of length multiple of 4 is required");
    for (uint32_t i = 0; i < len; i += 4)
    {
        v128f va   = sse::load_f(a + i * sizeof(float));
        v128f vb   = sse::load_f(b + i * sizeof(float));
        v128f vRes = sse::sub_f(va, vb);
        sse::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void subf2_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::sub_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void subf2_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::sub_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void subf3_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::sub_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void subf3_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::sub_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void subf4_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = sse::load_f(a);
    v128f vb   = sse::load_f(b);
    v128f vRes = sse::sub_f(va, vb);
    sse::store_f(vRes, res);
}

MXC_VECTOR_ABI void subf4_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = ssevex::load_f(a);
    v128f vb   = ssevex::load_f(b);
    v128f vRes = ssevex::sub_f(va, vb);
    ssevex::store_f(vRes, res);
}

MXC_VECTOR_ABI void mulfv_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                              uint32_t len)
{
    MXC_WARN("AVX 256 bit operations should be used for long sequences of relatively cheap operations (i.e. not "
             "sqrt/div), as\n\t1) "
             "using AVX for one, cheap operation, will likely result in getting bandwidth limited\n\t2) Slow "
             "operations have lower latency on "
             "SSE(2,3,4.1,4.2, non-VEX or VEX)");
    MXC_ASSERT((len % 8 == 0),
               "[x86_64] to enable avx vectorization float32 vectors of length multiple of 8 is required");
    for (uint32_t i = 0; i < len; i += 8)
    {
        v256f va   = avx::load_f(a + i * sizeof(float));
        v256f vb   = avx::load_f(b + i * sizeof(float));
        v256f vRes = avx::mul_f(va, vb);
        avx::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void mulfv_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                               uint32_t len)
{
    MXC_ASSERT(len % 4 == 0,
               "[x86_64] to enable sse2 vectorization float32 vectors of length multiple of 4 is required");
    for (uint32_t i = 0; i < len; i += 4)
    {
        v128f va   = sse::load_f(a + i * sizeof(float));
        v128f vb   = sse::load_f(b + i * sizeof(float));
        v128f vRes = sse::mul_f(va, vb);
        sse::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void mulf2_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::mul_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void mulf2_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::mul_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void mulf3_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::mul_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void mulf3_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::mul_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void mulf4_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = sse::load_f(a);
    v128f vb   = sse::load_f(b);
    v128f vRes = sse::mul_f(va, vb);
    sse::store_f(vRes, res);
}

MXC_VECTOR_ABI void mulf4_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = ssevex::load_f(a);
    v128f vb   = ssevex::load_f(b);
    v128f vRes = ssevex::mul_f(va, vb);
    ssevex::store_f(vRes, res);
}

MXC_VECTOR_ABI void divfv_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                              uint32_t len)
{
    MXC_WARN("AVX 256 bit operations should be used for long sequences of relatively cheap operations (i.e. not "
             "sqrt/div), as\n\t1) "
             "using AVX for one, cheap operation, will likely result in getting bandwidth limited\n\t2) Slow "
             "operations have lower latency on "
             "SSE(2,3,4.1,4.2, non-VEX or VEX)");
    MXC_ASSERT((len % 8 == 0),
               "[x86_64] to enable avx vectorization float32 vectors of length divtiple of 8 is required");
    for (uint32_t i = 0; i < len; i += 8)
    {
        v256f va   = avx::load_f(a + i * sizeof(float));
        v256f vb   = avx::load_f(b + i * sizeof(float));
        v256f vRes = avx::div_f(va, vb);
        avx::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void divfv_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                               uint32_t len)
{
    MXC_ASSERT(len % 4 == 0,
               "[x86_64] to enable sse2 vectorization float32 vectors of length divtiple of 4 is required");
    for (uint32_t i = 0; i < len; i += 4)
    {
        v128f va   = sse::load_f(a + i * sizeof(float));
        v128f vb   = sse::load_f(b + i * sizeof(float));
        v128f vRes = sse::div_f(va, vb);
        sse::store_f(vRes, res);
    }
}

MXC_VECTOR_ABI void divf2_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::div_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void divf2_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], 0, 0};
    alignas(16) float fb[4]   = {b[0], b[1], 0, 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::div_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
}

MXC_VECTOR_ABI void divf3_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = sse::load_f(fa);
    v128f vb   = sse::load_f(fb);
    v128f vRes = sse::div_f(va, vb);
    sse::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void divf3_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    alignas(16) float fa[4]   = {a[0], a[1], a[2], 0};
    alignas(16) float fb[4]   = {b[0], b[1], b[2], 0};
    alignas(16) float fres[4] = {};

    v128f va   = ssevex::load_f(fa);
    v128f vb   = ssevex::load_f(fb);
    v128f vRes = ssevex::div_f(va, vb);
    ssevex::store_f(vRes, fres);
    res[0] = fres[0];
    res[1] = fres[1];
    res[2] = fres[2];
}

MXC_VECTOR_ABI void divf4_sse2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = sse::load_f(a);
    v128f vb   = sse::load_f(b);
    v128f vRes = sse::div_f(va, vb);
    sse::store_f(vRes, res);
}

MXC_VECTOR_ABI void divf4_avx(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    v128f va   = ssevex::load_f(a);
    v128f vb   = ssevex::load_f(b);
    v128f vRes = ssevex::div_f(va, vb);
    ssevex::store_f(vRes, res);
}
#endif // defined(MXC_ARCH_X86_64)

MXC_VECTOR_ABI void addfv_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                  uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        res[i] = a[i] + b[i];
    }
}

MXC_VECTOR_ABI void addf2_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] + b[0];
    res[1] = a[1] + b[1];
}

MXC_VECTOR_ABI void addf3_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] + b[0];
    res[1] = a[1] + b[1];
    res[2] = a[2] + b[2];
}

MXC_VECTOR_ABI void addf4_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] + b[0];
    res[1] = a[1] + b[1];
    res[2] = a[2] + b[2];
    res[3] = a[3] + b[3];
}

MXC_VECTOR_ABI void subfv_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                  uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        res[i] = a[i] - b[i];
    }
}

MXC_VECTOR_ABI void subf2_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] - b[0];
    res[1] = a[1] - b[1];
}

MXC_VECTOR_ABI void subf3_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] - b[0];
    res[1] = a[1] - b[1];
    res[2] = a[2] - b[2];
}

MXC_VECTOR_ABI void subf4_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] - b[0];
    res[1] = a[1] - b[1];
    res[2] = a[2] - b[2];
    res[3] = a[3] - b[3];
}

MXC_VECTOR_ABI void mulfv_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                  uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        res[i] = a[i] * b[i];
    }
}

MXC_VECTOR_ABI void mulf2_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] * b[0];
    res[1] = a[1] * b[1];
}

MXC_VECTOR_ABI void mulf3_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] * b[0];
    res[1] = a[1] * b[1];
    res[2] = a[2] * b[2];
}

MXC_VECTOR_ABI void mulf4_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] * b[0];
    res[1] = a[1] * b[1];
    res[2] = a[2] * b[2];
    res[3] = a[3] * b[3];
}

MXC_VECTOR_ABI void divfv_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                                  uint32_t len)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        res[i] = a[i] / b[i];
    }
}

MXC_VECTOR_ABI void divf2_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] / b[0];
    res[1] = a[1] / b[1];
}

MXC_VECTOR_ABI void divf3_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] / b[0];
    res[1] = a[1] / b[1];
    res[2] = a[2] / b[2];
}

MXC_VECTOR_ABI void divf4_default(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
    res[0] = a[0] / b[0];
    res[1] = a[1] / b[1];
    res[2] = a[2] / b[2];
    res[3] = a[3] / b[3];
}
} // namespace detail

// ifunc needs to be declared with the mangled name of the dispatcher function. To avoid headaches, using C linking to
// avoid name mangling all together
#if defined(MXC_ARCH_X86_64)
#define MXC_SIMD_DEFINE_DISPATCHER(func)                        \
    extern "C"                                                  \
    {                                                           \
        func##_t *func##_dispatch()                             \
        {                                                       \
            MXC_SIMD_DISPATCHER_INIT();                         \
            using namespace ::mxc::simd::detail;                \
            if (MXC_SIMD_SUPPORT(avx))                          \
                return func##_avx;                              \
            else                                                \
                return func##_sse2;                             \
        }                                                       \
    }
#else // TODO add instruction set and platform support
#define MXC_SIMD_DEFINE_DISPATCHER(func)                        \
    extern "C"                                                  \
    {                                                           \
        func##_t *func##_dispatch()                             \
        {                                                       \
            using namespace ::mxc::simd::detail;                \
            return func##_default;                              \
        }                                                       \
    }
#endif

MXC_SIMD_DEFINE_DISPATCHER(addf2);
MXC_SIMD_DEFINE_DISPATCHER(addf3);
MXC_SIMD_DEFINE_DISPATCHER(addf4);
MXC_SIMD_DEFINE_DISPATCHER(addfv);

MXC_SIMD_DEFINE_DISPATCHER(subf2);
MXC_SIMD_DEFINE_DISPATCHER(subf3);
MXC_SIMD_DEFINE_DISPATCHER(subf4);
MXC_SIMD_DEFINE_DISPATCHER(subfv);

MXC_SIMD_DEFINE_DISPATCHER(mulf2);
MXC_SIMD_DEFINE_DISPATCHER(mulf3);
MXC_SIMD_DEFINE_DISPATCHER(mulf4);
MXC_SIMD_DEFINE_DISPATCHER(mulfv);

MXC_SIMD_DEFINE_DISPATCHER(divf2);
MXC_SIMD_DEFINE_DISPATCHER(divf3);
MXC_SIMD_DEFINE_DISPATCHER(divf4);
MXC_SIMD_DEFINE_DISPATCHER(divfv);

// function pointers (if indirect functions are not supported)
#if defined(_MSC_VER)
inline addfv_t *const g_addfv_func = addfv_dispatch();
inline addf2_t *const g_addf2_func = addf2_dispatch();
inline addf3_t *const g_addf3_func = addf3_dispatch();
inline addf4_t *const g_addf4_func = addf4_dispatch();

inline subfv_t *const g_subfv_func = subfv_dispatch();
inline subf2_t *const g_subf2_func = subf2_dispatch();
inline subf3_t *const g_subf3_func = subf3_dispatch();
inline subf4_t *const g_subf4_func = subf4_dispatch();

inline mulfv_t *const g_mulfv_func = mulfv_dispatch();
inline mulf2_t *const g_mulf2_func = mulf2_dispatch();
inline mulf3_t *const g_mulf3_func = mulf3_dispatch();
inline mulf4_t *const g_mulf4_func = mulf4_dispatch();

inline divfv_t *const g_divfv_func = divfv_dispatch();
inline divf2_t *const g_divf2_func = divf2_dispatch();
inline divf3_t *const g_divf3_func = divf3_dispatch();
inline divf4_t *const g_divf4_func = divf4_dispatch();

// these are not actually used in msvc, only their name is useful
MXC_VECTOR_ABI void addfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len)
{
}
MXC_VECTOR_ABI void addf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void addf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void addf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}

MXC_VECTOR_ABI void subfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len)
{
}
MXC_VECTOR_ABI void subf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void subf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void subf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}

MXC_VECTOR_ABI void mulfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len)
{
}
MXC_VECTOR_ABI void mulf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void mulf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void mulf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}

MXC_VECTOR_ABI void divfv(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res,
                          uint32_t len)
{
}
MXC_VECTOR_ABI void divf2(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void divf3(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
MXC_VECTOR_ABI void divf4(float const *MXC_RESTRICT a, float const *MXC_RESTRICT b, float *MXC_RESTRICT res)
{
}
#endif
} // namespace mxc::simd

namespace msimd = mxc::simd;

#endif // MXC_PLATFORM_SIMD_DISPATCH_H
