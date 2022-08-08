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
inline constexpr float ln2 = 0.69314718056;
inline constexpr float ln2pow2halved = 0.240226506959;
inline constexpr float ln2pow3div6 = 0.0555041086648;
inline constexpr float ln2pow4div24 = 0.00961812910763;
inline constexpr float onedivln10 = 0.434294481903;

namespace mmath 
{
    constexpr float sqrt(float const x) 
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x>=0.f && "function 'sqrt' takes nonnegative inputs\n");
        
        // calculate rough approximation using least square regression
        uint32_t const x_bits = std::bit_cast<uint32_t>(x);
        float const x_pot = std::bit_cast<float>(x_bits & 0x7f800000);
        float const x_div_exp = std::bit_cast<float>((x_bits & 0x00ffffff) | 0x3f800000 );
        
        float res = (0.485f + 0.485f * x_div_exp) * x_pot;
        
        // refine approximation using Newton-Rapshon method
        for (uint8_t i = 0u; i < 4u; ++i)
            res = (res + x/res) / 2;
        return res;
    }
    
    constexpr struct{float sqrt;float rsqrt} sqrt_rsqrt(float const x)
    {
        // Goldschmidt's algorithm. Faster convergence than Newton-Raphson! Note: it computes both sqrt and rsqrt
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x>0.f && "function 'rsqrt' takes positive inputs\n");
        float rsqrt_approx_curr  = 0.1875f*x*x - 0.625f*x + 0.9375f;
        float sqrt_approx_curr   = 2.f*x*h0;
        
        for (uint8_t i = 0; i < 4u; ++i)
        {
            float const common_factor = 1.5f - sqrt_approx_curr*rsqrt_approx_curr;
            rsqrt_approx_curr *= common_factor;
            sqrt_approx_curr  *= common_factor;
        }
        
        return {sqrt_approx_curr,rsqrt_approx_curr};
    }
    
    constexpr float rsqrt(float const x) 
    {
        float res = sqrt_rsqrt.sqrt;
        return res;
    }
    
    // FIX = these functions are assuming that std::numeric_limits<float>::is_iec559, which is
    // a boolean value equal to true if the current running platform implements IEEE754 binary 
    // floating points, and false otherwise. Define your own infinity? and epsilon with a backup
    // value for other systems which do not implement IEEE754
    constexpr float exp(float const x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= 40.2246053812f && "function 'exp' needs a number less than ln(std::numeric_limits<float>::max())");
        
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
        assert(x <= std::numeric_limits<float>::epsilon()
               && "function 'expm1' expects a small number");
        
        // Taylor polynomial of 4th grade of e^x - 1
        float const res = x + x*x/2 /*+ x*x*x/6 + x*x*x*x/24*/;
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
            float const temp[2] = {arith_curr, geom_curr};
            arith_curr = (arith_prev + geom_prev)/2;
            geom_curr  = sqrt(arith_prev, geom_prev);
            arith_prev = temp[0];
            geom_prev  = temp[1];
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
    
    constexpr float powi(float const x,int32_t const n) 
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
    
    constexpr float twoxpi(int8_t x)
    {
        assert(x >= -127 && x < 128 && "function 'twoxp': out of expoent range for floats");
        uint32_t res_exp_bits = (x + 127) << 23;
        float res = std::bit_cast<float>(res_exp_bits);
        
        return res;
    }
    
    // TODO = add max assertion for all functions which tend to infinity
    // TODO = branching can be minimized
    constexpr float twoxp(float x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= 41.2094271514 && "function 'twoxp' needs a number less than lb(std::numeric_limits<float>::max())");
        uint32_t const x_bits = std::bit_cast<uint32_t>(x);
        int8_t const x_sign = -2 * (x_bits >> 31);
        // store the exponent [-126,+127], compute 
        // taylor at 0 4th grade, valid in [-2,2] and then multiply by 
        int8_t const x_exponent = ((x_bits << 1) >> 24) - 127;
        float const twopower = twoxpi(x_exponent);
        if (x > 0) 
        {
            x -= twopower;
            float const taylor = 1 + x*(ln2 + x*(ln2pow2halved + x*(ln2pow3div6 + x*ln2pow4div24)));
            float const res = taylor * twoxpi(static_cast<int8_t>(twopower));
            return res;
        }
        else
        {
            x += twopower;
            float const taylor = 1 + x*(ln2 + x*(ln2pow2halved + x*(ln2pow3div6 + x*ln2pow4div24)));
            float const res = taylor / twoxpi(static_cast<int8_t>(twopower));
            return res;
        }
    }
    
    constexpr float pow(float const x,float const y) 
    {
        // x^y = 2^lb(x^y) = 2^(y*lb(x))
        return twoxp(y*lb(x));
    }
    
    constexpr float lg(float const x) 
    {
        constexpr float lb10 = 3.32192809489f;
        return lb(x) / lb10;
    }
    
    constexpr float log10(float const x) 
    {
        return lg(x);
    }
    
    /** OLD VERSION lb
    struct lb_iteration_data
    {
        float curr_lb_arg;
        uint32_t accumulated_exp;
        float partial;
    };
    
    constexpr lb_iteration_data lb_iteration_step(lb_iteration_data data)
    {
        uint32_t sqr_iter_num = 0u;
        do
        {
            data.curr_lb_arg *= data.curr_lb_arg;
            ++sqr_iter_num;
        } while (data.curr_lb_arg <= 2.f || data.curr_lb_arg > 4.f);
        
        float const twoxpiter = std::bit_cast<float>((127u - sqr_iter_num - data.accumulated_exp) << 23);
        data.curr_lb_arg /= 2;
        data.accumulated_exp += sqr_iter_num;
        data.partial += twoxpiter;
        return data;
    }
    */
    
    constexpr float lb(float const x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x > 0 && "function 'lb'('log2') requires a positive number");
        
        // lb(b*2^e) = lb(b) + e
        uint32_t const x_bits = std::bit_cast<uint32_t>(x);
        int8_t const x_exponent = (x_bits >> 23) - 127;
        float const x_div_exp = std::bit_cast<float>((x_bits & 0x00ffffff) | 0x3f800000 );
        
        // let y be x_div_exp, which lies in the interval [1,2). If it is equal to one, then the algorithm is done...
        if ((x_div_exp > 1.f && ((x_div_exp - 1.f) < 4.f*std::numeric_limits<float>::epsilon()))
            || (x_div_exp < 1.f && (1.f - x_div_exp) < 4.f*std::numeric_limits<float>::epsilon()))
        {
            float const res = static_cast<float>(x_exponent);
            return res;
        }
        
        // ...otherwise, square y until it lies in [2,4). Let m be the number of squaring times. We obtain a result 
        // z = y^2^m. --> lb(z) = 2^m*lb(y) -> lb(y) = 2^-m * lb(z) = 2^-m * (1+lb(z/2)) = 2^-m + 2^-m * lb(z/2)
        // where z/2 is again a number in [1,2). The process can be therefore iterated to construct an infinite series
        // which converges to the exact result. We can truncate the process to a fixed number of steps and approximate
        // lb(x) = exp + 2^-m1 + 2^-m1-m2 + ...
        
        /** OLD VERSION, same perf, but more complex
            lb_iteration_data const data = {
                .curr_lb_arg = x_div_exp, 
                .accumulated_exp = 0u, 
                .partial = static_cast<float>(x_exponent)
            };
            float const res = (lb_iteration_step(lb_iteration_step(lb_iteration_step(lb_iteration_step(lb_iteration_step(lb_iteration_step(lb_iteration_step(data)))))))).partial;
        */
        
        float lb_arg = x_div_exp;
        uint32_t factored_exp = 0;
        float res = static_cast<float>(x_exponent);
        for (uint8_t i = 0; i < 7u; ++i)
        {
            do
            {
                lb_arg *= lb_arg;
                ++factored_exp;
            } while (lb_arg < 2.f);
            
            // check if POT (power of two) is lower than smallest normalized POT in float
            if (factored_exp > 126)
                break;
            
            res += std::bit_cast<float>((127u - factored_exp) << 23);
            lb_arg /= 2;
        }
        
        return res;
    }
    
    constexpr float lbp1(float const x)
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x > 0 && x < std::numeric_limits<float>::epsilon());
        float const res = onedivln10 * x;
        return res;
    }
    
    constexpr float log2(float const x) 
    {
        return lb(x);
    }
    
    constexpr float log(float const x, float const b) 
    {
        return ln(x) / ln(b);
    }
    
}