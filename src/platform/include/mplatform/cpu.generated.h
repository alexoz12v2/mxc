// support information:
//	cpuid(eax=1):      edx=0x178bfbff, ecx=0x7ed8320b
//	cpuid(eax=7,ecx=0): ebx=0x219c91a9, ecx=0x400004, edx=0x0
//	cpuid(eax=7,ecx=1): eax=0x0, ebx=0x0, edx=0x0

// preprocessor definitions:
#define MXC_X86_64_SUPPORTED_SSE true
#define MXC_X86_64_SUPPORTED_SSE2 true
#define MXC_X86_64_SUPPORTED_SEE3 true
#define MXC_X86_64_SUPPORTED_SupplementalSSE3 true
#define MXC_X86_64_SUPPORTED_SSE4_1 true
#define MXC_X86_64_SUPPORTED_SSE4_2 true
#define MXC_X86_64_SUPPORTED_ConditionalMov true
#define MXC_X86_64_SUPPORTED_CompareExchange8B true
#define MXC_X86_64_SUPPORTED_CompareExchange16B true
#define MXC_X86_64_SUPPORTED_F16 true
#define MXC_X86_64_SUPPORTED_RDRand true
#define MXC_X86_64_SUPPORTED_RDSeed true
#define MXC_X86_64_SUPPORTED_AVX   true
#define MXC_X86_64_SUPPORTED_AVX2   true
#define MXC_X86_64_SUPPORTED_FMA3   true
#define MXC_X86_64_SUPPORTED_AVX512Foundation   false
#define MXC_X86_64_SUPPORTED_AVX512DoubleWordQuadWord   false
#define MXC_X86_64_SUPPORTED_ArbitraryPrecisionArithmetic true
#define MXC_X86_64_SUPPORTED_AVX512iFMA   false
#define MXC_X86_64_SUPPORTED_AVX512Prefetch   false
#define MXC_X86_64_SUPPORTED_AVX512ExponentialReciprocal   false
#define MXC_X86_64_SUPPORTED_AVX512ConflictDetection   false
#define MXC_X86_64_SUPPORTED_AVX512ByteWord   false
#define MXC_X86_64_SUPPORTED_AVX512VectorLength   false
#define MXC_X86_64_SUPPORTED_AVX512VectorBitManip   false
#define MXC_X86_64_SUPPORTED_AVX512VectorBitManip2   false
#define MXC_X86_64_SUPPORTED_AVX512NeuralNetwork   false
#define MXC_X86_64_SUPPORTED_AVX512BitAlg   false
#define MXC_X86_64_SUPPORTED_AVX512NeuralNetwork4Registers   false
#define MXC_X86_64_SUPPORTED_AVX512MultiplyAccumulationFloat324Registers   false
#define MXC_X86_64_SUPPORTED_AVX512VectorIntersection   false
#define MXC_X86_64_SUPPORTED_AVX512float16   false
#define MXC_X86_64_SUPPORTED_AVXbfloat16 false
#define MXC_X86_64_SUPPORTED_WaitUserSpace false
#define MXC_X86_64_SUPPORTED_5LevelPaging false
#define MXC_X86_64_SUPPORTED_AMXTileLoadStore false
#define MXC_X86_64_SUPPORTED_AMXint8 false
#define MXC_X86_64_SUPPORTED_AVXNeuralNetwork false
#define MXC_X86_64_SUPPORTED_AVX512bfloat16 false
#define MXC_X86_64_SUPPORTED_AMXfloat16 false
#define MXC_X86_64_SUPPORTED_AMXbfloat16 false
#define MXC_X86_64_SUPPORTED_CompareAndAdd false
#define MXC_X86_64_SUPPORTED_AVXiFMA false
#define MXC_X86_64_SUPPORTED_AMXComplexTile false
#define MXC_X86_64_SUPPORTED_AVXNeuralNetworkInt8 false
#define MXC_X86_64_SUPPORTED_AVXNeuralNetworkInt16 false
#define MXC_X86_64_SUPPORTED_AVXHalfToFloat32Conversions false
#define MXC_X86_64_SUPPORTED_AVX10 false

// WARNING: DEPRECATED, DO NOT USE. 
// generated at build time
namespace mxc::platform
{
	namespace x86_64
	{
		inline bool constexpr bSSE = true;
		inline bool constexpr bSSE2 = true;
		inline bool constexpr bSEE3 = true;
		inline bool constexpr bSupplementalSSE3 = true;
		inline bool constexpr bSSE4_1 = true;
		inline bool constexpr bSSE4_2 = true;
		inline bool constexpr bConditionalMov = true;
		inline bool constexpr bCompareExchange8B = true;
		inline bool constexpr bCompareExchange16B = true;
		inline bool constexpr bF16 = true;
		inline bool constexpr bRDRand = true;
		inline bool constexpr bRDSeed = true;
		inline bool constexpr bAVX   = true;
		inline bool constexpr bAVX2   = true;
		inline bool constexpr bFMA3   = true;
		inline bool constexpr bAVX512Foundation   = false;
		inline bool constexpr bAVX512DoubleWordQuadWord   = false;
		inline bool constexpr bArbitraryPrecisionArithmetic = true;
		inline bool constexpr bAVX512iFMA   = false;
		inline bool constexpr bAVX512Prefetch   = false;
		inline bool constexpr bAVX512ExponentialReciprocal   = false;
		inline bool constexpr bAVX512ConflictDetection   = false;
		inline bool constexpr bAVX512ByteWord   = false;
		inline bool constexpr bAVX512VectorLength   = false;
		inline bool constexpr bAVX512VectorBitManip   = false;
		inline bool constexpr bAVX512VectorBitManip2   = false;
		inline bool constexpr bAVX512NeuralNetwork   = false;
		inline bool constexpr bAVX512BitAlg   = false;
		inline bool constexpr bAVX512NeuralNetwork4Registers   = false;
		inline bool constexpr bAVX512MultiplyAccumulationFloat324Registers   = false;
		inline bool constexpr bAVX512VectorIntersection   = false;
		inline bool constexpr bAVX512float16   = false;
		inline bool constexpr bAVXbfloat16 = false;
		inline bool constexpr bWaitUserSpace = false;
		inline bool constexpr b5LevelPaging = false;
		inline bool constexpr bAMXTileLoadStore = false;
		inline bool constexpr bAMXint8 = false;
		inline bool constexpr bAVXNeuralNetwork = false;
		inline bool constexpr bAVX512bfloat16 = false;
		inline bool constexpr bAMXfloat16 = false;
		inline bool constexpr bAMXbfloat16 = false;
		inline bool constexpr bCompareAndAdd = false;
		inline bool constexpr bAVXiFMA = false;
		inline bool constexpr bAMXComplexTile = false;
		inline bool constexpr bAVXNeuralNetworkInt8 = false;
		inline bool constexpr bAVXNeuralNetworkInt16 = false;
		inline bool constexpr bAVXHalfToFloat32Conversions = false;
		inline bool constexpr bAVX10 = false;
	}
}