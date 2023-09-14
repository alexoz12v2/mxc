#include "simd_dispatch.h"

static SIMDSupport const g_SIMDSupport = []() {
    using namespace mxc::platform;
    SIMDSupport result = SIMDSupport::invalid;

// switch on cpu architecture
#if defined(MXC_ARCH_X86_64)
    FCPUFeatures f = x86_64::getCPUFeatures();

    // Avoid generating subnormal numbers (SSE support assumed)
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

    // existing denormals are treated as zero (SSE2 support assumed)
    _mm_setcsr(_mm_getcsr() | 0x8040);

    if (f.features1.edx.bSSE2())
        f |= SIMDSupport::sse2;
    else
        MXC_ASSERT(false, "current implementation assumes at least SSE2 support for x86_64 cpus");
    if (f.features1.ecx.bSSE3())
        f |= SIMDSupport::sse3;
    if (f.features1.ecx.bSupplementalSSE3())
        f |= SIMDSupport::ssse3;
    if (f.features1.ecx.bSSE4_1())
        f |= SIMDSupport::sse4_1;
    if (f.features1.ecx.bSSE4_2())
        f |= SIMDSupport::sse4_2;
    if (f.features1.ecx.bAVX())
        f |= SIMDSupport::avx;
    if (f.features70.ebx.bAVX2())
        f |= SIMDSupport::avx2;
    if (f.features70.ebx.bAVX512Foundation())
        f |= SIMDSupport::avx512f;
    if (f.features70.ebx.bAVX512ByteWord())
        f |= SIMDSupport::avx512bw;
    if (f.features70.ebx.bAVX512ConflictDetection())
        f |= SIMDSupport::avx512cd;
    if (f.features70.ebx.bAVX512DoubleWordQuadWord())
        f |= SIMDSupport::avx512dq;
    if (f.features70.ebx.bAVX512VectorLength())
        f |= SIMDSupport::avx512vl;
    if (f.features70.ebx.bBitManipulationInstructionSet1)
        f |= SIMDSupport::bmi1;
    if (f.features1.ecx.bF16())
        f |= SIMDSupport::f16c;
    if (f.features1.ecx.bFMA3())
        f |= SIMDSupport::fma3;
    if (f.features1.ecx.bPopCount())
        f |= SIMDSupport::popcnt;
#endif

    return result;
}();
