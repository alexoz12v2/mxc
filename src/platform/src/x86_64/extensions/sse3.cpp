#if defined(MXC_SSE_AS_AVX)
#include "sse3vex.h"
#else
#include "sse3.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse3vex
#else
namespace mxc::platform::x86_64::sse3
#endif
{
} // namespace mxc::platform::x86_64::sse3
