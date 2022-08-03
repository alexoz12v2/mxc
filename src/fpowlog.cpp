#include "constants.hpp"

#include "common.hpp"
#include "common_private.hpp"

#include <cassert>
#include <type_traits>
#include <limits>
#include <bits>

#define mmath_pow(x,n) mmath_pow##n(x)
#define mmath_pow7(x)  (x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow8(x)  (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow9(x)  (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow10(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow11(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow12(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow13(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow14(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow15(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
#define mmath_pow16(x) (x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)*(x)
static constexpr ln2 = 0.69314718056;

namespace mmath 
{
    // TODO = maybe long polynomial division could make this more efficient
    // TODO = refactor checks in a private(.cpp) macro/fuction so that you can then modify them efficiently,
    //        and add MINMATH_ALLOW_DENORMAL
    [[nodiscard("a mathematical function call should not be discarded")]] 
        constexpr float sqrt(float const x) 
    {
        if constexpr(std::is_constant_evaluated())
        {
            MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
            assert(x>=0.f && "function 'float sqrt(float x)' expects nonnegative x value");
            float const y =
            (67108864*mmath_pow(x,16)+33285996544*mmath_pow(x,15)+2413234749440*mmath_pow(x,14)+60813515685888*mmath_pow(x,13)+705871164211200*mmath_pow(x,12)+4329343140495360*mmath_pow(x,11)+15152700991733760*mmath_pow(x,10)+31637507565158400*mmath_pow(x,9)+40337822145576960*mmath_pow(x,8)+31637507565158400*mmath_pow(x,7)+15152700991733760*x*x*x*x*x*x+4329343140495360*x*x*x*x*x+705871164211200*x*x*x*x+60813515685888*x*x*x+2413234749440*x*x+33285996544*x+67108864)
                /(2147483648*mmath_pow(x,15)+332859965440*mmath_pow(x,14)+13514114596864*mmath_pow(x,13)+225878772547584*mmath_pow(x,12)+1882323104563200*mmath_pow(x,11)+8658686280990720*mmath_pow(x,10)+23311847679590400*mmath_pow(x,9)+37965009078190080*mmath_pow(x,8)+37965009078190080*mmath_pow(x,7)+23311847679590400*x*x*x*x*x*x+8658686280990720*x*x*x*x*x+1882323104563200*x*x*x*x+225878772547584*x*x*x+13514114596864*x*x+332859965440*x+2147483648);
            return y;
        }
        else
        {
            MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
            assert(x>=0.f && "function 'float sqrt(float x)' expects nonnegative x value");
            
            float xps[9] = {mmath_pow(x,8),0,0,0,0,0,0,0,0};
            for (auto i = 0; i < 8; ++i)
            {
                xps[7-i] = xps[8-i]*x;
            }
            
            float const y = 
            (67108864*xps[0]+33285996544*xps[1]+2413234749440*xps[2]+60813515685888*xps[3]+705871164211200*xps[4]+4329343140495360*xps[5]+15152700991733760*xps[6]+31637507565158400*xps[7]+40337822145576960*xps[8]+31637507565158400*mmath_pow(x,7)+15152700991733760*x*x*x*x*x*x+4329343140495360*x*x*x*x*x+705871164211200*x*x*x*x+60813515685888*x*x*x+2413234749440*x*x+33285996544*x+67108864)
                /(2147483648*xps[1]+332859965440*xps[2]+13514114596864*xps[3]+225878772547584*xps[4]+1882323104563200*xps[5]+8658686280990720*xps[6]+23311847679590400*xps[7]+37965009078190080*xps[8]+37965009078190080*mmath_pow(x,7)+23311847679590400*x*x*x*x*x*x+8658686280990720*x*x*x*x*x+1882323104563200*x*x*x*x+225878772547584*x*x*x+13514114596864*x*x+332859965440*x+2147483648);
            return y;
        }
    }
}

// FIX = these functions are assuming that std::numeric_limits<float>::is_iec559, which is
// a boolean value equal to true if the current running platform implements IEEE754 binary 
// floating points, and false otherwise. Define your own infinity? and epsilon with a backup
// value for other systems which do not implement IEEE754
constexpr float exp(float const x)
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    
    int32_t const k = floor(x*(1 + ((x>=0)*2-1)*x/(5.5*x + std::numeric_limits<float>::epsilon())));
    float const small = x - k*ln2;
    float const taylor4 = 1 + small + (12*small*small + 4*small*small*small + small*small*small*small)/24;
    float const y = k >= 0 
        ? (taylor4 * (1 << static_cast<uint32_t>(k))) 
        : (taylor4 / (1 << static_cast<uint32_t>(-k)));
    
    return y;
}

constexpr float expm1(float const x) 
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    assert(x <= 8 * std::numeric_limits<float>::epsilon()
           && "function 'expm1' expects a small number");
    
    // Taylor polynomial of 4th grade of e^x - 1
    float const res = x + x*x/2 + x*x*x/6 + x*x*x*x/24;
    return res;
}

constexpr float ln(float const x) 
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    assert(x > std::numeric_limits<float>::epsilon() 
           && "function 'ln' requires a positive, not too small, number");
    // arithmetic-geometric approximation: ln x ~= pi/(agm(1,2^(3-m))) - m*ln 2
    // where m number of exact binary digits. The bigger m, the more expansive is the
    // method, as it converges less quickly. floating point numbers have a precision of
    // 24 bits. I choose 12 bits of precision.
    // The arithmetic-geometric mean is calculated by a limit process, therefore we need
    // to approximate that too. 7 steps are sufficient to ensure precision up to, and not
    // including, x = 10^7, see https://www.desmos.com/calculator/lw0pjjylpy
    
    // calculate agm 
    float arith_prev = (1 + 1/(1024*x))/2;
    float geom_prev  = sqrt(1/(1024*x)); // TODO = inverse square root needed
    float arith_curr = (arith_prev + geom_prev)/2;
    float geom_curr  = sqrt(arith_prev, geom_prev);
    for (int32_t i = 0; i<4; ++i)
    {
        arith_curr = (arith_prev + geom_prev)/2;
        geom_curr  = sqrt(arith_prev, geom_prev);
    }
    arith_curr = (arith_prev + geom_prev)/2;
    
    // calculate ln
    float res = pi/(2*arith_curr)-12*ln2;
    return res;
} 

constexpr float log(float const x) 
{
    // alias for ISO notation ln(x)
    return ln(x);
}

constexpr float pow(float const x,int32_t const n) 
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    float res = 1.f;
    
    if (n == 0)
        return res;
    
    // cancel the sign bit
    int32_t n_abs = (n << 1) >> 1;
    
    for (int32_t i = 0; i < n_abs; ++i)
    {
        res *= x;
    }
    
    if (n > 0)
    {
        return res;
    }
    else
    {
        res = 1.f/res;
        return res;
    }
}

constexpr float twoxp(int8_t x)
{
    uint32_t res_exp_bits = (x + 127) << 23;
    float res = std::bit_cast<float>(res_exp_bits);
    
    return res;
}

constexpr float twoxp(float x)
{
    MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
    uint32_t x_bits = std::bit_cast<uint32_t>(x);
    
    // store the exponent [-126,+127]
    int8_t x_exponent = (x_bits << 1) >> 24 - 127;
    float twopower = twoxp(x_exponent);
    
    // taylor and then multiply
}

constexpr float pow(float const x,float const y) 
{
    // x^y = 2^lb(x^y) = 2^(y*lb(x))
}

constexpr float lg(float const x) {}

constexpr float log10(float const x) {}

constexpr float lb(float const x) {}

constexpr float log2(float const x) {}

constexpr float log(float const x, float const b) {}
}