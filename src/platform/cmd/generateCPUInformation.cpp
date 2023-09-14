#if defined(__x86_64__)
#include "x86_64/cpufeatures.h"
#else
#error "CPU architecture not supported!"
#endif

#include <cstdint>
#include <cstdio> // TODO future

// NOTE: When adding new architectures, still define all the other namespaces and defines with all the relative values,
// because somewhere else (eg simd.h) the defines are used for the purpose of conditional compilation, and #if doesn't
// short circuit!
auto main() -> int32_t
{
    // Strings for General Information
    char const *start = R"DELIM(
// WARNING: DEPRECATED, DO NOT USE.
// generated at build time
namespace mxc::platform
{
)DELIM";

    char const *qualifiers   = "inline bool constexpr";
    char const *falseTrue[2] = {"false", "true"};

    static uint32_t constexpr features_x86_64_count = 48;
    char const *start_x86_64                        = "\tnamespace x86_64\n\t{\n";
    // x86_64 specific strings
    char const *features_x86_64[features_x86_64_count] = {"bSSE",
                                                          "bSSE2",
                                                          "bSEE3",
                                                          "bSupplementalSSE3",
                                                          "bSSE4_1",
                                                          "bSSE4_2",
                                                          "bConditionalMov",
                                                          "bCompareExchange8B",
                                                          "bCompareExchange16B",
                                                          "bF16",
                                                          "bRDRand",
                                                          "bRDSeed",
                                                          "bAVX  ",
                                                          "bAVX2  ",
                                                          "bFMA3  ",
                                                          "bAVX512Foundation  ",
                                                          "bAVX512DoubleWordQuadWord  ",
                                                          "bArbitraryPrecisionArithmetic",
                                                          "bAVX512iFMA  ",
                                                          "bAVX512Prefetch  ",
                                                          "bAVX512ExponentialReciprocal  ",
                                                          "bAVX512ConflictDetection  ",
                                                          "bAVX512ByteWord  ",
                                                          "bAVX512VectorLength  ",
                                                          "bAVX512VectorBitManip  ",
                                                          "bAVX512VectorBitManip2  ",
                                                          "bAVX512NeuralNetwork  ",
                                                          "bAVX512BitAlg  ",
                                                          "bAVX512NeuralNetwork4Registers  ",
                                                          "bAVX512MultiplyAccumulationFloat324Registers  ",
                                                          "bAVX512VectorIntersection  ",
                                                          "bAVX512float16  ",
                                                          "bAVXbfloat16",
                                                          "bWaitUserSpace",
                                                          "b5LevelPaging",
                                                          "bAMXTileLoadStore",
                                                          "bAMXint8",
                                                          "bAVXNeuralNetwork",
                                                          "bAVX512bfloat16",
                                                          "bAMXfloat16",
                                                          "bAMXbfloat16",
                                                          "bCompareAndAdd",
                                                          "bAVXiFMA",
                                                          "bAMXComplexTile",
                                                          "bAVXNeuralNetworkInt8",
                                                          "bAVXNeuralNetworkInt16",
                                                          "bAVXHalfToFloat32Conversions",
                                                          "bAVX10"};

    char const *features_x86_64_defines[features_x86_64_count] = {
        "MXC_X86_64_SUPPORTED_SSE",
        "MXC_X86_64_SUPPORTED_SSE2",
        "MXC_X86_64_SUPPORTED_SEE3",
        "MXC_X86_64_SUPPORTED_SupplementalSSE3",
        "MXC_X86_64_SUPPORTED_SSE4_1",
        "MXC_X86_64_SUPPORTED_SSE4_2",
        "MXC_X86_64_SUPPORTED_ConditionalMov",
        "MXC_X86_64_SUPPORTED_CompareExchange8B",
        "MXC_X86_64_SUPPORTED_CompareExchange16B",
        "MXC_X86_64_SUPPORTED_F16",
        "MXC_X86_64_SUPPORTED_RDRand",
        "MXC_X86_64_SUPPORTED_RDSeed",
        "MXC_X86_64_SUPPORTED_AVX  ",
        "MXC_X86_64_SUPPORTED_AVX2  ",
        "MXC_X86_64_SUPPORTED_FMA3  ",
        "MXC_X86_64_SUPPORTED_AVX512Foundation  ",
        "MXC_X86_64_SUPPORTED_AVX512DoubleWordQuadWord  ",
        "MXC_X86_64_SUPPORTED_ArbitraryPrecisionArithmetic",
        "MXC_X86_64_SUPPORTED_AVX512iFMA  ",
        "MXC_X86_64_SUPPORTED_AVX512Prefetch  ",
        "MXC_X86_64_SUPPORTED_AVX512ExponentialReciprocal  ",
        "MXC_X86_64_SUPPORTED_AVX512ConflictDetection  ",
        "MXC_X86_64_SUPPORTED_AVX512ByteWord  ",
        "MXC_X86_64_SUPPORTED_AVX512VectorLength  ",
        "MXC_X86_64_SUPPORTED_AVX512VectorBitManip  ",
        "MXC_X86_64_SUPPORTED_AVX512VectorBitManip2  ",
        "MXC_X86_64_SUPPORTED_AVX512NeuralNetwork  ",
        "MXC_X86_64_SUPPORTED_AVX512BitAlg  ",
        "MXC_X86_64_SUPPORTED_AVX512NeuralNetwork4Registers  ",
        "MXC_X86_64_SUPPORTED_AVX512MultiplyAccumulationFloat324Registers  ",
        "MXC_X86_64_SUPPORTED_AVX512VectorIntersection  ",
        "MXC_X86_64_SUPPORTED_AVX512float16  ",
        "MXC_X86_64_SUPPORTED_AVXbfloat16",
        "MXC_X86_64_SUPPORTED_WaitUserSpace",
        "MXC_X86_64_SUPPORTED_5LevelPaging",
        "MXC_X86_64_SUPPORTED_AMXTileLoadStore",
        "MXC_X86_64_SUPPORTED_AMXint8",
        "MXC_X86_64_SUPPORTED_AVXNeuralNetwork",
        "MXC_X86_64_SUPPORTED_AVX512bfloat16",
        "MXC_X86_64_SUPPORTED_AMXfloat16",
        "MXC_X86_64_SUPPORTED_AMXbfloat16",
        "MXC_X86_64_SUPPORTED_CompareAndAdd",
        "MXC_X86_64_SUPPORTED_AVXiFMA",
        "MXC_X86_64_SUPPORTED_AMXComplexTile",
        "MXC_X86_64_SUPPORTED_AVXNeuralNetworkInt8",
        "MXC_X86_64_SUPPORTED_AVXNeuralNetworkInt16",
        "MXC_X86_64_SUPPORTED_AVXHalfToFloat32Conversions",
        "MXC_X86_64_SUPPORTED_AVX10"};

    // call all necessary functions for each platform
#if defined(__x86_64__)
    auto [features1, features70, features71]          = mxc::platform::x86_64::getCPUFeatures();
    bool featureSupport_x86_64[features_x86_64_count] = {features1.edx.bSSE(),
                                                         features1.edx.bSSE2(),
                                                         features1.ecx.bSSE3(),
                                                         features1.ecx.bSupplementalSSE3(),
                                                         features1.ecx.bSSE4_1(),
                                                         features1.ecx.bSSE4_2(),
                                                         features1.edx.bConditionalMov(),
                                                         features1.edx.bCompareExchange8B(),
                                                         features1.ecx.bCompareExchange16B(),
                                                         features1.ecx.bF16(),
                                                         features1.ecx.bRDRand(),
                                                         features70.ebx.bRDSeed(),
                                                         features1.ecx.bAVX(),
                                                         features70.ebx.bAVX2(),
                                                         features1.ecx.bFMA3(),
                                                         features70.ebx.bAVX512Foundation(),
                                                         features70.ebx.bAVX512DoubleWordQuadWord(),
                                                         features70.ebx.bArbitraryPrecisionArithmetic(),
                                                         features70.ebx.bAVX512iFMA(),
                                                         features70.ebx.bAVX512Prefetch(),
                                                         features70.ebx.bAVX512ExponentialReciprocal(),
                                                         features70.ebx.bAVX512ConflictDetection(),
                                                         features70.ebx.bAVX512ByteWord(),
                                                         features70.ebx.bAVX512VectorLength(),
                                                         features70.ecx.bAVX512VectorBitManip(),
                                                         features70.ecx.bAVX512VectorBitManip2(),
                                                         features70.ecx.bAVX512NeuralNetwork(),
                                                         features70.ecx.bAVX512BitAlg(),
                                                         features70.edx.bAVX512NeuralNetwork4Registers(),
                                                         features70.edx.bAVX512MultiplyAccumulationFloat324Registers(),
                                                         features70.edx.bAVX512VectorIntersection(),
                                                         features70.edx.bAVX512float16(),
                                                         features70.edx.bAMXbfloat16(),
                                                         features70.ecx.bWaitUserSpace(),
                                                         features70.ecx.b5LevelPaging(),
                                                         features70.edx.bAMXTileLoadStore(),
                                                         features70.edx.bAMXint8(),
                                                         features71.eax.bAVXNeuralNetwork(),
                                                         features71.eax.bAVX512bfloat16(),
                                                         features71.eax.bAMXfloat16(),
                                                         features70.edx.bAMXbfloat16(),
                                                         features71.eax.bCompareAndAdd(),
                                                         features71.eax.bAVXiFMA(),
                                                         features71.edx.bAMXComplexTile(),
                                                         features71.edx.bAVXNeuralNetworkInt8(),
                                                         features71.edx.bAVXNeuralNetworkInt16(),
                                                         features71.edx.bAVXHalfToFloat32Conversions(),
                                                         features71.edx.bAVX10()};

    printf("// support information:\n//\tcpuid(eax=1):      edx=0x%x, ecx=0x%x\n//\tcpuid(eax=7,ecx=0): ebx=0x%x, "
           "ecx=0x%x, edx=0x%x\n//\t"
           "cpuid(eax=7,ecx=1): eax=0x%x, ebx=0x%x, edx=0x%x\n",
           features1.edx.reg, features1.ecx.reg, features70.ebx.reg, features70.ecx.reg, features70.edx.reg,
           features71.eax.reg, features71.ebx.reg, features71.edx.reg);
    printf("\n// preprocessor definitions:\n");

    for (uint32_t i = 0; i != features_x86_64_count; ++i)
    {
        printf("#define %s %s\n", features_x86_64_defines[i],
               falseTrue[static_cast<uint32_t>(featureSupport_x86_64[i])]);
    }
#endif

    // start outputting information
    printf("%s", start);

    // print platform specific namespaces
#if defined(__x86_64__)
    printf("%s", start_x86_64);
#endif

#if defined(__x86_64__)
    for (uint32_t i = 0; i != features_x86_64_count; ++i)
    {
        printf("\t\t%s %s = %s;\n", qualifiers, features_x86_64[i],
               falseTrue[static_cast<uint32_t>(featureSupport_x86_64[i])]);
    }

    printf("\t}\n");
#endif

    // print platform agnostic information
    printf("}");
}
