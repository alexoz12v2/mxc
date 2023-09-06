#if defined(MXC_SSE_AS_AVX)
#include "ssse3vex.h"
#else
#include "ssse3.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::ssse3vex
#else
namespace mxc::platform::x86_64::ssse3
#endif
{
} // namespace mxc::platform::x86_64::ssse3
