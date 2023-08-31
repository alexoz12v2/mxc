#include "cpufeatures.h"
#include <cstdint>

#ifdef __MSVC__
#include <intrin.h>
#else // gcc and clang
#include <cpuid.h>
#endif

namespace mxc::platform::x86_64
{

    auto getCPUFeatures() -> FCPUFeatures
    {
    
        struct R
        {
            uint32_t eax;
            uint32_t ebx;
            uint32_t ecx;
            uint32_t edx;
        };
        union
        {
            uint32_t reg[4];
            R r;
        };

        uint32_t maxBasicLeaf;
        [[maybe_unused]] uint32_t maxExtendedLeaf; // Note: when extended features are needed (eg SSE4a), use this

    #ifdef __MSVC__
        __cpuid(reg, 0);
        maxBasicLeaf = reg[0];
        __cpuid(reg, 0x8000'0000);
        maxExtendedLeaf = reg[0];
    #else // gcc and clang
        maxBasicLeaf    = __get_cpuid_max(0, nullptr);
        maxExtendedLeaf = __get_cpuid_max(0x8000'0000, nullptr);
    #endif
    
        // get basic cpuid info
        FCpuIDFeatures_eax1     features1{};
        FCpuIDFeatures_eax7ecx0 features70{};
        FCpuIDFeatures_eax7ecx1 features71{};
    
        uint32_t leaf = 1;
        if (leaf <= maxBasicLeaf)
        {
            r.eax = 1;
    #ifdef __MSVC__
            __cpuid(reg, leaf);
    #else
            __get_cpuid(leaf, &r.eax, &r.ebx, &r.ecx, &r.edx);
    #endif
    
            features1.ecx = r.ecx;
            features1.edx = r.edx;
        }
    
        leaf = 7;
        if (leaf <= maxBasicLeaf)
        {
            r.eax = 7; r.ecx = 0; r.ebx = 0; r.edx = 0;
    #ifdef __MSVC__
            __cpuid(reg, leaf);
    #else
            __get_cpuid_count(7, 0, &r.eax, &r.ebx, &r.ecx, &r.edx);
    #endif
            features70.ebx = r.ebx;
            features70.ecx = r.ecx;
            features70.edx = r.edx;
    
            r.eax = 7; r.ecx = 1; r.ebx = 0; r.edx = 0;
    #ifdef __MSVC__
            __cpuid(reg, leaf);
    #else
            __get_cpuid_count(leaf, 1, &r.eax, &r.ebx, &r.ecx, &r.edx);
    #endif
    
            features71.eax = r.eax;
            features71.ebx = r.ecx;
            features71.edx = r.edx;
        }
    
        return { features1, features70, features71 };
    }

} // namespace mxc::platform::x86_64

namespace mplat = mxc::platform;

