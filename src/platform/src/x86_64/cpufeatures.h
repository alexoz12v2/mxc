#ifndef MXC_PLATFORM_X86_64_CPU_FEATURES_H
#define MXC_PLATFORM_X86_64_CPU_FEATURES_H

#include <cstdint>

namespace mxc::platform::x86_64
{

struct FCpuIDFeatures_eax1
{
    struct EDX
    {
        EDX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bTimeStampCounter()
        {
            return bool(reg & 0x0000'0010u);
        }
        bool bModelSpecificRegisters()
        {
            return bool(reg & 0x0000'0020u);
        }
        bool bCompareExchange8B()
        {
            return bool(reg & 0x0000'0100u);
        }
        bool bConditionalMov()
        {
            return bool(reg & 0x0000'8000u);
        }
        bool bSSE2CachelineFlush()
        {
            return bool(reg & 0x0008'0000u);
        }
        bool bMMX()
        {
            return bool(reg & 0x0080'0000u);
        }
        bool bSSE()
        {
            return bool(reg & 0x0200'0000u);
        }
        bool bSSE2()
        {
            return bool(reg & 0x0400'0000u);
        }
        uint32_t reg;
    } edx;

    struct ECX
    {
        ECX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bSSE3()
        {
            return bool(reg & 0x0000'0001u);
        }
        bool bCarryLessMultiply()
        {
            return bool(reg & 0x0000'0002u);
        }
        bool bMonitorInstruction()
        {
            return bool(reg & 0x0000'0008u);
        }
        bool bSupplementalSSE3()
        {
            return bool(reg & 0x0000'0200u);
        }
        bool bFMA3()
        {
            return bool(reg & 0x0000'1000u);
        }
        bool bCompareExchange16B()
        {
            return bool(reg & 0x0000'2000u);
        }
        bool bSSE4_1()
        {
            return bool(reg & 0x0008'0000u);
        }
        bool bSSE4_2()
        {
            return bool(reg & 0x0010'0000u);
        }
        bool bPopCount()
        {
            return bool(reg & 0x0080'0000u);
        }
        bool bAES()
        {
            return bool(reg & 0x0200'0000u);
        }
        bool bAVX()
        {
            return bool(reg & 0x1000'0000u);
        }
        bool bF16()
        {
            return bool(reg & 0x2000'0000u);
        }
        bool bRDRand()
        {
            return bool(reg & 0x4000'0000u);
        }
        uint32_t reg;
    } ecx;
};
static_assert(sizeof(FCpuIDFeatures_eax1) == 8);

struct FCpuIDFeatures_eax7ecx0
{
    struct EBX
    {
        EBX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bSoftwareGuardExtensions()
        {
            return bool(reg & 0x0000'0004u);
        }
        bool bBitManipulationInstructionSet1()
        {
            return bool(reg & 0x0000'0008u);
        }
        bool bTransactionalSynchronizationExtensions()
        {
            return bool(reg & 0x0000'0010u);
        }
        bool bAVX2()
        {
            return bool(reg & 0x0000'0020u);
        }
        bool bBitManipulationInstructionSet2()
        {
            return bool(reg & 0x0000'0100u);
        }
        bool bRestrictedTSXMemory()
        {
            return bool(reg & 0x0000'0800u);
        }
        bool bMemoryProtectionExtensions()
        {
            return bool(reg & 0x0000'4000u);
        }
        bool bAVX512Foundation()
        {
            return bool(reg & 0x0001'0000u);
        }
        bool bAVX512DoubleWordQuadWord()
        {
            return bool(reg & 0x0002'0000u);
        }
        bool bRDSeed()
        {
            return bool(reg & 0x0004'0000u);
        }
        bool bArbitraryPrecisionArithmetic()
        {
            return bool(reg & 0x0008'0000u);
        }
        bool bAVX512iFMA()
        {
            return bool(reg & 0x0020'0000u);
        }
        bool bFlushCachelineContainingAddress()
        {
            return bool(reg & 0x0080'0000u);
        }
        bool bCachelineWriteBack()
        {
            return bool(reg & 0x0100'0000u);
        }
        bool bAVX512Prefetch()
        {
            return bool(reg & 0x0400'0000u);
        }
        bool bAVX512ExponentialReciprocal()
        {
            return bool(reg & 0x0800'0000u);
        }
        bool bAVX512ConflictDetection()
        {
            return bool(reg & 0x1000'0000u);
        }
        bool bSHA()
        {
            return bool(reg & 0x2000'0000u);
        }
        bool bAVX512ByteWord()
        {
            return bool(reg & 0x4000'0000u);
        }
        bool bAVX512VectorLength()
        {
            return bool(reg & 0x8000'0000u);
        }
        uint32_t reg;
    } ebx;

    // b5LevelPaging: if used, real addresses use 57 bits, otherwise 48 bits (useful for tagged pointers)
    // bCachelineDemote: HINTS to cpu that cache line that contains the address specified should be moved to a higher
    // (slower) level cache
    struct ECX
    {
        ECX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bPrefetchVectorDataIntoCaches()
        {
            return bool(reg & 0x0000'0001u);
        }
        bool bAVX512VectorBitManip()
        {
            return bool(reg & 0x0000'0002u);
        }
        bool bWaitUserSpace()
        {
            return bool(reg & 0x0000'0020u);
        }
        bool bAVX512VectorBitManip2()
        {
            return bool(reg & 0x0000'0040u);
        }
        bool bGaloisField()
        {
            return bool(reg & 0x0000'0100u);
        }
        bool bVexAES()
        {
            return bool(reg & 0x0000'0200u);
        }
        bool bVexCarryLessMultiplication()
        {
            return bool(reg & 0x0000'0400u);
        }
        bool bAVX512NeuralNetwork()
        {
            return bool(reg & 0x0000'0800u);
        }
        bool bAVX512BitAlg()
        {
            return bool(reg & 0x0000'1000u);
        }
        bool bAVX512VectorPopulationCountDoubleQuadword()
        {
            return bool(reg & 0x0000'4000u);
        }
        bool b5LevelPaging()
        {
            return bool(reg & 0x0001'0000u);
        }
        bool bMPXddressWidthAdjust()
        {
            return bool(reg & 0x003e'0000u);
        }
        bool bAESKeyLocker()
        {
            return bool(reg & 0x0080'0000u);
        }
        bool bCachelineDemote()
        {
            return bool(reg & 0x0200'0000u);
        }
        bool bMovDirectStore32B()
        {
            return bool(reg & 0x0800'0000u);
        }
        bool bMovDirectStore64B()
        {
            return bool(reg & 0x1000'0000u);
        }
        bool bSGXLaunchConfig()
        {
            return bool(reg & 0x4000'0000u);
        }
        uint32_t reg;
    } ecx;

    // bSerializeInstruction: Before the next instruction is fetched and executed, all modifications to flags,
    // registers, 					     and memory by previous instructions are completed, draining all buffered writes
    // to memory.
    struct EDX
    {
        EDX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bSGXKeyAttestation()
        {
            return bool(reg & 0x0000'0002u);
        }
        bool bAVX512NeuralNetwork4Registers()
        {
            return bool(reg & 0x0000'0004u);
        }
        bool bAVX512MultiplyAccumulationFloat324Registers()
        {
            return bool(reg & 0x0000'0008u);
        }
        bool bAVX512VectorIntersection()
        {
            return bool(reg & 0x0000'0100u);
        }
        bool bSerializeInstruction()
        {
            return bool(reg & 0x0000'4000u);
        }
        bool bTSXLoadAddressTracking()
        {
            return bool(reg & 0x0001'0000u);
        }
        bool bAMXbfloat16()
        {
            return bool(reg & 0x0040'0000u);
        }
        bool bAVX512float16()
        {
            return bool(reg & 0x0080'0000u);
        }
        bool bAMXTileLoadStore()
        {
            return bool(reg & 0x0100'0000u);
        }
        bool bAMXint8()
        {
            return bool(reg & 0x0200'0000u);
        }
        uint32_t reg;
    } edx;
};
static_assert(sizeof(FCpuIDFeatures_eax7ecx0) == 12);

struct FCpuIDFeatures_eax7ecx1
{
    struct EAX
    {
        EAX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bSHA512()
        {
            return bool(reg & 0x0000'0001u);
        }
        bool bSM3hash()
        {
            return bool(reg & 0x0000'0002u);
        }
        bool bSM4hash()
        {
            return bool(reg & 0x0000'0004u);
        }
        bool bRemoteAtomicOperations()
        {
            return bool(reg & 0x0000'0008u);
        }
        bool bAVXNeuralNetwork()
        {
            return bool(reg & 0x0000'0010u);
        }
        bool bAVX512bfloat16()
        {
            return bool(reg & 0x0000'0020u);
        }
        bool bCompareAndAdd()
        {
            return bool(reg & 0x0000'0080u);
        }
        bool bSerializeWriteMSR()
        {
            return bool(reg & 0x0008'0000u);
        }
        bool bAMXfloat16()
        {
            return bool(reg & 0x0020'0000u);
        }
        bool bResetMSR()
        {
            return bool(reg & 0x0040'0000u);
        }
        bool bAVXiFMA()
        {
            return bool(reg & 0x0080'0000u);
        }
        bool bMSRList()
        {
            return bool(reg & 0x0800'0000u);
        }
        uint32_t reg;
    } eax;

    struct EBX
    {
        EBX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        uint32_t reg;
    } ebx;

    struct EDX
    {
        EDX &operator=(uint32_t i)
        {
            reg = i;
            return *this;
        }
        bool bAVXNeuralNetworkInt8()
        {
            return bool(reg & 0x0000'0010u);
        }
        bool bAVXHalfToFloat32Conversions()
        {
            return bool(reg & 0x0000'0020u);
        }
        bool bAMXComplexTile()
        {
            return bool(reg & 0x0000'0100u);
        }
        bool bAVXNeuralNetworkInt16()
        {
            return bool(reg & 0x0000'0400u);
        }
        bool bInstructionCachePrefetch()
        {
            return bool(reg & 0x0000'4000u);
        }
        bool bAVX10()
        {
            return bool(reg & 0x0008'0000u);
        }
        bool bAdvancedPerformanceExtensions()
        {
            return bool(reg & 0x0020'0000u);
        }
        uint32_t reg;
    } edx;
};
static_assert(sizeof(FCpuIDFeatures_eax7ecx0) == 12);

struct FCPUFeatures
{
    FCpuIDFeatures_eax1 features1;
    FCpuIDFeatures_eax7ecx0 features70;
    FCpuIDFeatures_eax7ecx1 features71;
};

auto getCPUFeatures() -> FCPUFeatures;

} // namespace mxc::platform::x86_64

namespace mplat = mxc::platform;

#endif // MXC_PLATFORM_X86_64_CPU_FEATURES_H
