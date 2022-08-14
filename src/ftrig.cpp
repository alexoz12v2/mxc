#include "ftrig.hpp"

#include "constants.hpp"
#include "numfunctions.hpp"
#include "common_private.hpp"
#include "fpowlog.hpp"

#include <cassert>
#include <bit>

// TODO = comments with doxygen?
namespace mmath 
{
    
    constexpr float oneoverpi = 1.f/pi;
    constexpr float pihalved = pi/2.f;
    constexpr float twooverpi = 1.f/pihalved;
    constexpr float pifourths = pi/4.f;
    
    // ------------------------ BASIC ------------------------
    
    constexpr float sin(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        // sign of function (x%2 == x&1, x&-2 != x&1)
        int8_t const sf = -2 * ( floor( floor((x/pi) & 1)) + 1 ) + 3;
        
        // sign of argument
        int8_t const sa = -2 * ( floor( floor((-2*x/pi) & 1)) + 1 ) + 3;
        
        // scale parameter, used to offset our approximation
        float const k = floor( (x + 0.5*pi)/pi );
        
        // argument to give to our lagrange polynomial approximation, guaranteed to
        // be 0 <= arg <= pi/2
        float const arg = sa * (k * pi - x);
        
        // lagrange polynomial for sin with (0,0),(pi/6,1/2),(pi/4,sqrt(2)/2),
        // (pi/3,sqrt(3)/2),(pi/2,1)
        return sf*(0.028797*arg*arg*arg*arg
                   -0.204340696022*arg*arg*arg
                   +0.0213730075289*arg*arg
                   +0.995626*arg);
    }
    
    constexpr float cos(float const x) 
    {
        return sin(pi/2 - x);
    }
    
    constexpr float tan(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        // compile time constants
        constexpr float c[4] = {0.58873f,-0.222615f,0.0907791f,-0.0148931f}; 
        // a tangent approximation in [0,pi/2] can be derived by taking an transformed 
        // hyperbola branch with its pole in pihalved, offset by a polynomial approximation 
        // of the error. hyp(x) = -1/(x-pi/2)-2/pi
        // repetition can be achieved with modular arithmetic in(x)=mod(x+pi/2, pi)-pi/2
        // https://www.desmos.com/calculator/xrkvpwljyl
        // DISADVANTAGE = 1 mod + 2 division operations + evaluation of 4th deg polynomial
        float in = (x+pihalved-pi*static_cast<int64_t>((x+pihalved)*oneoverpi))-pihalved;
        
        // faster than using -2*static_cast<int32_t>(in > 0.f)+1. Proof:
        // https://www.quick-bench.com/q/gBLxxnYgEEKMI4cygqs0MzI4Rbk
        int8_t const in_sign = -2*static_cast<int8_t>(std::bit_cast<uint32_t>(in)>>31u)+1;
        
        // cancel sign
        in = std::bit_cast<float>(std::bit_cast<uint32_t>(in) & 0x7fffffff);
        float const res = in_sign*( -1.f/(in-pihalved)-twooverpi
                                   +c[3]*in*in*in*in+c[2]*in*in*in+c[1]*in*in+c[0]*in );
        return res;
    }
    
    // ----------------------- INVERSE -----------------------
    
    constexpr float asin(float const x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= 1.f && x >= -1.f && "function 'asin' takes a number between -1 and 1");
        
        // asin function has two points of singularity at both its extremes, where its 
        // derivative->infty, and such high frequency causes imprecision when trying polynomial 
        // interpolation, and Runge's phenomenon if we would try to use higher degree polynomials.
        // Therefore we can calculate instead a polynomial interpolation of asin(x)+sqrt(1-x^2)
        // and then subtract it back
        
        // compile time constants
        constexpr float c[4] {1.0f, 0.954066f, -0.310098f, -0.0731713f};
        
        // to reflect the functon we need to evaluate the approximation with the absolute value of x
        // and multiply the result by its signum
        int8_t const x_sign = -2*static_cast<int8_t>(std::bit_cast<uint32_t>(x) >> 31u)+1;
        x = std::bit_cast<float>(std::bit_cast<uint32_t>(x) & 0x7fffffff);
        
        float const res = c[3]*x*x*x+c[2]*x*x+c[1]*x+c[0]-sqrt(1-x*x);
        return res;
    }
    
    constexpr float acos(float x) 
    {
        float const res = asin(-x)+pihalved;
        return res;
    }
    
    constexpr float atan(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        // https://www.desmos.com/calculator/gzmsinxkad
        int8_t const x_sign = -2*static_cast<int8_t>(std::bit_cast<uint32_t>(x) >> 31u)+1;
        if (x <= 1.081f)
        {
            float const res = pifourths*x+0.186982f*x-0.191942f*x*x*x;
            return res;
        }
        else
        {
            float const res = pihalved*x_sign−4x/(4x*x+1.f);
            return res;
        }
    }
    
    constexpr float atan2(float const x, float const y) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(y);
        
        // LSB = x > 0 second LSB = y == 0, third LSB = x == 0
        uint8_t const conditions = 0 + static_cast<uint8_t>(std::bit_cast<uint32_t>(x)>>31u) 
            + static_cast<uint8_t>(y < std::numeric_limits<float>::epsilon()
                                   || y > -std::numeric_limits<float>::epsilon()) >> 1
            + static_cast<uint8_t>(x < std::numeric_limits<float>::epsilon()
                                   || x > -std::numeric_limits<float>::epsilon()) >> 2;
        switch (conditions)
        {
            case 4 /*x>0,y!=0*/:
            case 6 /*x>0,y==0*/:
            {
                float const res = 2.f*atan(y/(sqrt(x*x*(1.f+y*y/(x*x)))+x));
                return res;
            }
            
            case 1/*x==0,y!=0*/:
            case 0 /*x<0,y!=0*/:
            {
                float const res = 2.f*atan((sqrt(x*x(1.f+y*y/(x*x)))-x)/y);
                return res;
            }
            
            case 2 /*x<0,y==0*/:
            {
                return pi;
            }
            
            case 3/*x==0,y==0*/:
            default:
            {
                assert(false && "function 'atan2': undefined or error\n");
                // danger zone if release mode. To be defensive, return an impossible value
                return std::numeric_limits<float>::nan();
            }
        }
    }
    
    // TODO = now they all have naive implementations, upgrade them
    // --------------------- HYPERBOLIC ----------------------
    
    constexpr float sinh(float const x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        if (x > -0.5f*std::numeric_limits<float>::epsilon() 
            || x < 0.5f*std::numeric_limits<float>::epsilon())
        {
            float const res = 0.5f*expm1(2.f*x)/exp(x);
            return res;
        }
        else
        {
            float const res = 0.5f*(exp(x)-exp(-x));
            return res;
        }
    }
    
    constexpr float cosh(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        
        float const res = 0.5f*(exp(x)+exp(-x));
        return res;
    }
    
    constexpr float tanh(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        float const inv_exp2x_p1 = 1.f/(exp(2.f*x)+1.f);
        
        if (x > -0.5f*std::numeric_limits<float>::epsilon() 
            || x < 0.5f*std::numeric_limits<float>::epsilon())
        {
            float const res = expm1(2.f*x)*inv_exp2x_p1;
            return res;
        }
        else
        {
            float const res = (exp(2.f*x)-1.f)*inv_exp2x_p1;
            return res;
        }
    }
    
    // ----------------- INVERSE HYPERBOLIC ------------------
    
    constexpr float asinh(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x < std::bit_cast<float>(0x7f7fffff)
               && "function 'asinh' would get Inf as a partial result with "
               "given input\n");
        
        float const res = ln(x+sqrt(x*x+1.f));
        return res;
    }
    
    constexpr float acosh(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x>=1.f && "function 'acosh' is defined for values greater than 1.f\n");
        assert(x*x != std::numeric_limits<float>::infinity() 
               && 1.f/x*x >= std::numeric_limits<float>::epsilon()
               && "function 'acosh' is getting a too small input\n");
        
        float const res = ln(x+x*sqrt(1.f-1.f/x*x));
        return res;
    }
    
    constexpr float atanh(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= 1.f && x >= -1.f 
               && "function 'atanh' input does not belong to function domain\n");
        assert(x >= std::numeric_limits<float>::epsilon() 
               || x <= -std::numeric_limits<float>::epsilon());
        
        // artanh(x) = 0.5 ln((1+x)/(1-x)) = 0.5 ln(-1 + 2/(1-x))
        // or artanh(x) = 0.5 (ln(1+x) - ln(1-x))
        // first is faster because my ln implementation uses more divisions
        
        float const res = 0.5f*ln(-1.f + 2.f/(1.f-x));
        return res;
    }
    
    //----------------- ANGULAR CONVERSIONS ------------------
    
    constexpr float deg2rad(float const x) 
    {
        constexpr float factor = pi/180.f;
        float const res = factor*x;
        return x;
    }
    
    constexpr float rad2deg(float const x) 
    {
        constexpr float factor = 180.f/pi;
        float const res = factor*x;
        return x;
    }
}