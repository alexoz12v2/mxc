#include "constants.hpp"

#include "common.hpp"

#include <cassert>
#include <type_traits>
#include <limits>

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

namespace mmath 
{
    // TODO = maybe long polynomial division could make this more efficient
    [[nodiscard("a mathematical function call should not be discarded")]] 
        constexpr float sqrt(float const x) 
    {
        if constexpr(std::is_constant_evaluated())
        {
            static_assert(!isDenormal(x) && x != std::numeric_limits<float>::infinity()
                          && x != -std::numeric_limits<float>::infinity() && x==x/*not NaN*/,
                          "float input is not a finite normalized number");
            static_assert(x >= 0.f, "function 'float sqrt(float x)' expects nonnegative x value");
            
            float const y =
            (67108864*mmath_pow(x,16)+33285996544*mmath_pow(x,15)+2413234749440*mmath_pow(x,14)+60813515685888*mmath_pow(x,13)+705871164211200*mmath_pow(x,12)+4329343140495360*mmath_pow(x,11)+15152700991733760*mmath_pow(x,10)+31637507565158400*mmath_pow(x,9)+40337822145576960*mmath_pow(x,8)+31637507565158400*mmath_pow(x,7)+15152700991733760*x*x*x*x*x*x+4329343140495360*x*x*x*x*x+705871164211200*x*x*x*x+60813515685888*x*x*x+2413234749440*x*x+33285996544*x+67108864)
                /(2147483648*mmath_pow(x,15)+332859965440*mmath_pow(x,14)+13514114596864*mmath_pow(x,13)+225878772547584*mmath_pow(x,12)+1882323104563200*mmath_pow(x,11)+8658686280990720*mmath_pow(x,10)+23311847679590400*mmath_pow(x,9)+37965009078190080*mmath_pow(x,8)+37965009078190080*mmath_pow(x,7)+23311847679590400*x*x*x*x*x*x+8658686280990720*x*x*x*x*x+1882323104563200*x*x*x*x+225878772547584*x*x*x+13514114596864*x*x+332859965440*x+2147483648);
            return y;
        }
        else
        {
            assert(!isDenormal(x) && x != std::numeric_limits<float>::infinity() 
                   && x != -std::numeric_limits<float>::infinity() && x==x/*not NaN*/
                   && "float input is not a finite normalized number");
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

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float exp(float const x)
{
    static constexpr ln2 = 0.69314718056;
    
    if constexpr (std::is_constant_evaluated())
    {
        static_assert(x == x/*not NaN*/ && !isDenormal(x) && x != std::numerical_limits<float>::infinity() 
                      && x != -std::numerical_limits<float>::infinity()
                      , "float input is not a finite normalized number");
    }
    else
    {
        assert(x == x/*not NaN*/ && !isDenormal(x) && x != std::numerical_limits<float>::infinity() 
               && x != -std::numerical_limits<float>::infinity()
               &&"float input is not a finite normalized number");
    }
    
    int32_t const k = floor(x*(1 + ((x>=0)*2-1)*x/(5.5*x)));
    float const small = x - k*ln2;
    float const taylor4 = 1 + small + (12*small*small + 4*small*small*small + small*small*small*small)/24;
    float const y = k >= 0 
        ?     (taylor4 * (1 << static_cast<uint32_t>(k))) 
    /**/: (taylor4 / (1 << static_cast<uint32_t>(-k)));
    
    return y;
}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float expm1(float const x) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float ln(float const x) {} 

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float log(float const x) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float pow(float const x,int const n) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float pow(float const x,float const y) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float lg(float const x) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float log10(float const x) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float lb(float const x) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float log2(float const x) {}

[[nodiscard("a mathematical function call should not be discarded")]] 
constexpr float log(float const x, float const b) {}
}