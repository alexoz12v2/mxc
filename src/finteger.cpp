#include "finteger.hpp"

#include "common.hpp"

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <limits>

namespace mmath
{
    [[nodiscard("a mathematical function should not be discarded")]]
        float constexpr floor(float const x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const x_truncated = static_cast<float>(static_cast<int64_t>(x));
        
        return x_truncated;
    }
    
}