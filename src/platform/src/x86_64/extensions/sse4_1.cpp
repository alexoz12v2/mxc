#if defined(MXC_SSE_AS_AVX)
#include "sse4_1vex.h"
#else
#include "sse4_1.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse4_1vex
#else
namespace mxc::platform::x86_64::sse4_1
#endif
{
} // namespace mxc::platform::x86_64::sse4_1
