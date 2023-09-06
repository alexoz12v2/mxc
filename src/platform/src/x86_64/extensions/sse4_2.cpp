#if defined(MXC_SSE_AS_AVX)
#include "sse4_2vex.h"
#else
#include "sse4_2.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse4_2vex
#else
namespace mxc::platform::x86_64::sse4_2
#endif
{
} // namespace mxc::platform::x86_64::sse4_2
