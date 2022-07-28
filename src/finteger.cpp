#include "finteger.hpp"

#include <cassert>
#include <cstdint>

namespace mmath
{
    
    float constexpr floor(float x)
    {
        assert(true/*notnan, notinf*/ && "");
        
        return static_cast<float>(static_cast<int64_t>(x));
    }
    
}