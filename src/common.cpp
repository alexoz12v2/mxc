#include "minmath/common.h"

#include <limits>
#include <cstdint>

namespace mmath
{
    uint32_t bits(float const f)
    {
        // check for zero. DEFECT: cannot distinguish between negative and positive zero
        // because in C++ 0.f == -0.f
        if (f == 0.f)
            return 0x00000000; // or 0x80000000 for negative zero
        
        // check for infinity
        if (f == std::numeric_limits<float>::infinity())
            return 0x7f800000;
        
        if (f == -std::numeric_limits<float>::infinity())
            return 0xff800000;
        
        // check for NaNs
        if (f != f) // NaN definition
            return 0x7fc00000; // any value with max exp and nonzero mantissa is NaN
        
        // check for float value:
        
        // find and clear sign bit
        bool sign = f < 0.f;
        float abs_f = sign ? -f : f;
        
        // in compile time we cannot reinterpret_cast, but we can static_cast.
        // the static_cast from a float to an integral type, if the number is too 
        // large results in undefined behaviour, else if it is not too large, then
        // any fractional part is truncated from the result. 
        
        // Therefore we need to scale abs_f to a range such that
        // 1. the significand is unchanged
        // 2. it contains no fractional part
        // 3. scaled value is not larger than (2^64-1)
        
        // we will scale our value such that abs_f >= 2^87, using notation 0x_p_f = _*2^_
        // because if abs_f >= 2^87, the least significant bit has value 2^(87-23)=2^64.
        // so that we can then scale down our number by 2^64 to get an integral number
        
        // we will also keep track of the amount of scaling being done, because the
        // exponent + amount added to get past 87 + leading zeros in resulting integer = 
        // = max exponent for normalized floats (127). Of course we account for the 
        // exponent bias of +127 ([-126,127]->[1,254])
        int32_t exponent = 254;
        
        while (abs_f < 0x1p87f)
        {
            // scale in steps of 41 = 127 - 86. This exponent prevents overflow in conversion
            abs_f *= 0x1p41f; 
            exponent -= 41;
        }
        
        uint64_t integerFloat = static_cast<uint64_t>(abs_f * 0x1p-64f);
        
        // remove leading zeroes from exponent
        int32_t lz = detail::countLeadingZeroes(integerFloat);
        exponent -= lz;
        
        // there are cases in which exponent is < 0, in particular if exponent is < 127 after
        // the while loop, which happens in case of Denormal floats [0x1p-149f, 0x1p-127f]
        // which maps to [0x00000001, 0x007fffff], same for negative numbers 
        // [-0x1p-149f,-0x1p-127f]->[0x80000001, 0x807fffff]. As we can see the exponent is 0,
        // while the leading zeroes of the converted mantissa are constant, because in 
        // denormal numbers the gap between adjacent numbers is not logarithmic, but constant,
        // caused by the fact that the exponent is fixed to zero and leading zeroes in the
        // mantissa are allowed. Said constant is 8 - 1 = 7, because there are 8 leading bits
        // in the floating point representation that aren't part of the mantissa.
        // Furthermore, there is no implicit leading 1 for the mantissa, which in the 
        // calculation of the normalized mantissa will be accounted for in the general case,
        // therefore we remove 1 from here
        if (exponent <= 0)
        {
            exponent = 0;
            lz = 7; // 8 - 1
        }
        
        // first remove leading zeroes then scale down by 41 = 64-23, which will place the 
        // significand at the least significant bits
        uint32_t significand = (integerFloat << (lz + 1)) >> 41;
        
        // reconstruct the floating point number
        return (sign << 31) | (exponent << 23) | significand;
    }
}
