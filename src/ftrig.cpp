#include "constants.hpp"
#include "numfunctions.hpp"

#include <cassert>

// TODO = comments with doxygen?
namespace mmath {
    
    // ------------------------ BASIC ------------------------
    
    constexpr float sin(float x) 
    {
        assert(/*normalized form, notnan, notinf, see later*/ && "");
        
        // sign of function (x%2 == x&1, x&-2 != x&1)
        constexpr int8_t sf = -2 * ( floor( floor((x/pi) & 1)) + 1 ) + 3;
        
        // sign of argument
        constexpr int8_t sa = -2 * ( floor( floor((-2*x/pi) & 1)) + 1 ) + 3;
        
        // scale parameter, used to offset our approximation
        constexpr float k = floor( (x + 0.5*pi)/pi );
        
        // argument to give to our lagrange polynomial approximation, guaranteed to
        // be 0 <= arg <= pi/2
        constexpr float arg = sa * (k * pi - x);
        
        // lagrange polynomial for sin with (0,0),(pi/6,1/2),(pi/4,sqrt(2)/2),
        // (pi/3,sqrt(3)/2),(pi/2,1)
        return sf*(0.028797*arg*arg*arg*arg-0.204340696022*arg*arg*arg+0.0213730075289*arg*arg+0.995626*arg);
    }
    constexpr float cos(float x) 
    {
        // asserts already in sin function
        return sin(pi/2 - x);
    }
    constexpr float tan(double x) 
    {
        // taylor(more efficient?) vs sin/cos(more precise)
    }
    
    // ----------------------- INVERSE -----------------------
    
    constexpr float asin() {}
    constexpr float acos() {}
    constexpr float atan() {}
    constexpr float atan2() {}
    
    // TODO = requires exponential
    // --------------------- HYPERBOLIC ----------------------
    
    constexpr float sinh() {}
    constexpr float cosh() {}
    constexpr float tanh() {}
    
    // ----------------- INVERSE HYPERBOLIC ------------------
    
    constexpr float asinh() {}
    constexpr float acosh() {}
    constexpr float atanh() {}
    
    //----------------- ANGULAR CONVERSIONS ------------------
    
    constexpr float deg2rad() {}
    constexpr float rad2deg() {}
}