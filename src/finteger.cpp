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
        if constexpr (std::is_constant_evaluated())
        {
            static_assert(x == x/*not NaN*/ && !isDenormal(x) && x != std::numeric_limits<float>::infinity()
                          && x != -std::numeric_limits<float>::infinity()
                          , "float input is not a finite normalized number");
        }
        else
        {
            assert(x == x/*not NaN*/ && !isDenormal(x) && x != std::numeric_limits<float>::infinity()
                   && x != -std::numeric_limits<float>::infinity()
                   && "float input is not a finite normalized number");
        }
        
        return static_cast<float>(static_cast<int64_t>(x));
    }
    
}