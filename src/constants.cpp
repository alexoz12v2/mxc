#include "constants.hpp"

namespace mmath 
{
    
    float constexpr pi = 3.14159265358979323846264338327950288419716939937510;
    float constexpr e  = 2.71828182845904523536028747135266249775724709369995;
    float constexpr m0 = std::bit_cast<float>(0x80000000);
    float constexpr p0 = std::bit_cast<float>(0x00000000);
    uint32_t constexpr m0_repr = 0x80000000;
    uint32_t constexpr p0_repr = 0x00000000;
}

