#ifndef MXC_PLATFORM_X86_64_SSEVEX_H
#define MXC_PLATFORM_X86_64_SSEVEX_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::ssevex
{

MXC_VECTOR_ABI auto add_f(v128f v0, v128f v1) -> v128f;                         // _mm_add_ps
MXC_VECTOR_ABI auto and_f(v128f v0, v128f v1) -> v128f;                         // _mm_and_ps
MXC_VECTOR_ABI auto andnot_f(v128f v0, v128f v1) -> v128f;                      // _mm_andnot_ps
MXC_VECTOR_ABI auto cmpeq_f(v128f v0, v128f v1) -> v128f;                       // _mm_cmpeq_ps
MXC_VECTOR_ABI auto cmpge_f(v128f v0, v128f v1) -> v128f;                       // _mm_cmpge_ps
MXC_VECTOR_ABI auto cmpgt_f(v128f v0, v128f v1) -> v128f;                       // _mm_cmpgt_ps
MXC_VECTOR_ABI auto cmple_f(v128f v0, v128f v1) -> v128f;                       // _mm_cmple_ps
MXC_VECTOR_ABI auto cmplt_f(v128f v0, v128f v1) -> v128f;                       // _mm_cmplt_ps
MXC_VECTOR_ABI auto cmpneq_f(v128f v0, v128f v1) -> v128f;                      // _mm_cmpneq_ps
MXC_VECTOR_ABI auto cmpnge_f(v128f v0, v128f v1) -> v128f;                      // _mm_cmpnge_ps
MXC_VECTOR_ABI auto cmpngt_f(v128f v0, v128f v1) -> v128f;                      // _mm_cmpngt_ps
MXC_VECTOR_ABI auto cmpnle_f(v128f v0, v128f v1) -> v128f;                      // _mm_cmpnle_ps
MXC_VECTOR_ABI auto cmpnlt_f(v128f v0, v128f v1) -> v128f;                      // _mm_cmpnlt_ps
MXC_VECTOR_ABI auto cmpAllNotNaN_f(v128f v0, v128f v1) -> v128f;                // _mm_cmpord_ps
MXC_VECTOR_ABI auto cmpAnyNotNaN_f(v128f v0, v128f v1) -> v128f;                // _mm_cmpunord_ps
MXC_VECTOR_ABI auto div_f(v128f vDividend, v128f vDivisor) -> v128f;            // _mm_div_ps
MXC_VECTOR_ABI auto load_f(float const * MXC_RESTRICT farrAligned16) -> v128f;  // _mm_load_ps
MXC_VECTOR_ABI auto max_f(v128f v0, v128f v1) -> v128f;                         // _mm_max_ps
MXC_VECTOR_ABI auto min_f(v128f v0, v128f v1) -> v128f;                         // _mm_min_ps
MXC_VECTOR_ABI auto mul_f(v128f v0, v128f v1) -> v128f;                         // _mm_mul_ps
MXC_VECTOR_ABI auto or_f(v128f v0, v128f v1) -> v128f;                          // _mm_or_ps
MXC_VECTOR_ABI auto rcp_f(v128f v) -> v128f;                                    // _mm_rcp_ps
MXC_VECTOR_ABI auto rsqrt_f(v128f v) -> v128f;                                  // _mm_rsqrt_pa
MXC_VECTOR_ABI auto zeroVec_f() -> v128f;                                       // _mm_setzero_ps

template <uint32_t shuffledIdxs> requires ((shuffledIdxs & 0x0000'00ff) == 0)
MXC_VECTOR_ABI auto shuffle_f(v128f v0, v128f v1) -> v128f;                     // _mm_shuffle_ps
MXC_VECTOR_ABI auto sqrt_f(v128f v) -> v128f;                                   // _mm_sqrt_ps
MXC_VECTOR_ABI auto store_f(v128f v, 
                            float * MXC_RESTRICT out_farrAligned16) -> void;    // _mm_store_ps
MXC_VECTOR_ABI auto sub_f(v128f v0, v128f v1) -> v128f;                         // _mm_sub_ps
MXC_VECTOR_ABI auto interleaveHigh_f(v128f v0, v128f v1) -> v128f;              // _mm_unpackhi_ps
MXC_VECTOR_ABI auto interleaveLow_f(v128f v0, v128f v1) -> v128f;               // _mm_unpacklo_ps
MXC_VECTOR_ABI auto xor_f(v128f v0, v128f v1) -> v128f;                         // _mm_xor_ps

} // namespace mxc::platform::x86_64::ssevex

#endif // MXC_PLATFORM_X86_64_SSEVEX_H
