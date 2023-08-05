#ifndef MMATH_FPOWLOG_HPP
#define MMATH_FPOWLOG_HPP

#include <cstdint>
#include <cassert>
#include <type_traits>
#include <limits>
#include <bit>

#include "constants.h"
#include "common.h"
#include "common_private.h"

/*
 * Outline:
 * 
 * struct sqrt_rsqrt_return_t {float sqrt;float rsqrt;};
 *
 * MMATH_FORCE_INLINE constexpr auto sqrt(float const x) -> float;
 * MMATH_FORCE_INLINE constexpr auto sqrt_rsqrt(auto const x) -> sqrt_rsqrt_return_t;
 * MMATH_FORCE_INLINE constexpr auto rsqrt(float const x) -> float;
 * MMATH_FORCE_INLINE constexpr auto exp(float const x) -> float;
 * MMATH_FORCE_INLINE constexpr auto expm1(float const x) -> float;
 * constexpr auto ln(float const x) -> float; // can't be force inlined
 * constexpr auto log(float const x) -> float;
 * MMATH_FORCE_INLINE constexpr auto powi(float const x, int32_t const i) -> float;
 * MMATH_FORCE_INLINE constexpr auto twoxpi(int8_t x) -> float;
 * MMATH_FORCE_INLINE constexpr auto twoxp(float x) -> float;
 * constexpr auto pow(float const x, float const y) -> float;
 * constexpr auto lg(float const x) -> float;
 * constexpr auto log10(float const x) -> float;
 * MMATH_FORCE_INLINE constexpr auto lb(float const x) -> float;
 * MMATH_FORCE_INLINE constexpr auto lbp1(float const x) -> float;
 * constexpr auto log2(float const x) -> float;
 * constexpr auto log(float const x, float const b) -> float;
 */

namespace mmath
{
    namespace detail
    {
        static constexpr float ln2           = 0.69314718056;
        static constexpr float ln2pow2halved = 0.240226506959;
        static constexpr float ln2pow3div6   = 0.0555041086648;
        static constexpr float ln2pow4div24  = 0.00961812910763;
        static constexpr float onedivln10    = 0.434294481903;
        static constexpr float lb10          = 3.32192809489f;
    }

    struct sqrt_rsqrt_return_t {float sqrt;float rsqrt;};

    MMATH_FORCE_INLINE auto constexpr sqrt(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x>=0.f && "function 'sqrt' takes nonnegative inputs\n");
        
        // calculate rough approximation using least square regression
        uint32_t const x_bits = std::bit_cast<uint32_t>(x);
        float const x_pot     = std::bit_cast<float>(x_bits & 0x7f800000);
        float const x_div_exp = std::bit_cast<float>((x_bits & 0x00ffffff) | 0x3f800000 );
        
        float res = (0.485f + 0.485f * x_div_exp) * x_pot;
        
        // refine approximation using Newton-Rapshon method
        for (uint8_t i = 0u; i < 4u; ++i)
            res = (res + x/res) / 2;

        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(res);
        return res;
    }

    MMATH_FORCE_INLINE auto constexpr sqrt_rsqrt(auto const x) -> sqrt_rsqrt_return_t
    {
        // Goldschmidt's algorithm. Faster convergence than Newton-Raphson! Note: it computes both sqrt and rsqrt
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x>0.f && "function 'sqrt_rsqrt' takes positive inputs\n");

        float rsqrt_approx_curr = 0.1875f*x*x - 0.625f*x + 0.9375f;
        float sqrt_approx_curr  = 2.f*x*rsqrt_approx_curr;
        
        for (uint8_t i = 0; i < 4u; ++i)
        {
            float const common_factor = 1.5f - sqrt_approx_curr*rsqrt_approx_curr;
            rsqrt_approx_curr *= common_factor;
            sqrt_approx_curr  *= common_factor;
        }
        rsqrt_approx_curr *= 2.f;
        
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(sqrt_approx_curr);
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(rsqrt_approx_curr);
        return {sqrt_approx_curr,rsqrt_approx_curr};
    }

    // TODO: implement Q_rsqrt
    MMATH_FORCE_INLINE constexpr auto rsqrt(float const x) -> float
    {
        float res = sqrt_rsqrt(x).sqrt;
        return res;
    }

    MMATH_FORCE_INLINE constexpr auto exp(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= 40.2246053812f && "function 'exp' needs a number less than ln(std::numeric_limits<float>::max())");
        
        int32_t const k = floor(x*(1 + ((x>=0)*2-1)*x/(5.5*x + std::numeric_limits<float>::epsilon())));
        float const small = x - k*detail::ln2;
        float const taylor4 = 1 + small + (12*small*small + 4*small*small*small + small*small*small*small)/24;
        float const y = k >= 0 
            ? (taylor4 * (1 << static_cast<uint32_t>(k))) 
            : (taylor4 / (1 << static_cast<uint32_t>(-k)));
        
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(y);
        return y;
    }

    MMATH_FORCE_INLINE constexpr auto expm1(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= std::numeric_limits<float>::epsilon()
               && "function 'expm1' expects a small number");
        
        // Taylor polynomial of 4th grade of e^x - 1
        float const res = x + x*x/2 /*+ x*x*x/6 + x*x*x*x/24*/;
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(res);
        return res;
    }

    constexpr auto log(float const x) -> float // can't be force inlined
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
        float geom_curr  = sqrt(arith_prev*geom_prev);
        for (int32_t i = 0; i<4; ++i)
        {
            float const temp[2] = {arith_curr, geom_curr};
            arith_curr = (arith_prev + geom_prev)/2;
            geom_curr  = sqrt(arith_prev*geom_prev);
            arith_prev = temp[0];
            geom_prev  = temp[1];
        }
        arith_curr = (arith_prev + geom_prev)/2;
        
        // calculate ln
        float res = pi/(2*arith_curr)-12*detail::ln2;
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(res);
        return res;
    } 

    MMATH_FORCE_INLINE auto constexpr powi(float const x, int32_t const n) -> float
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
        
        if (n <= 0)
            res = 1.f/res;

        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        return res;
    }

    /*
     * OLD VERSION lb
     *struct lb_iteration_data
     *{
     *    float curr_lb_arg;
     *    uint32_t accumulated_exp;
     *    float partial;
     *};
     *
     *constexpr lb_iteration_data lb_iteration_step(lb_iteration_data data)
     *{
     *    uint32_t sqr_iter_num = 0u;
     *    do
     *    {
     *        data.curr_lb_arg *= data.curr_lb_arg;
     *        ++sqr_iter_num;
     *    } while (data.curr_lb_arg <= 2.f || data.curr_lb_arg > 4.f);
     *    
     *    float const twoxpiter = std::bit_cast<float>((127u - sqr_iter_num - data.accumulated_exp) << 23);
     *    data.curr_lb_arg /= 2;
     *    data.accumulated_exp += sqr_iter_num;
     *    data.partial += twoxpiter;
     *    return data;
     *}
     */
    
    auto constexpr log2(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x > 0 && "function 'lb'('log2') requires a positive number");
        
        // lb(b*2^e) = lb(b) + e
        uint32_t const x_bits   = std::bit_cast<uint32_t>(x);
        int8_t const x_exponent = (x_bits >> 23) - 127;
        float const x_div_exp   = std::bit_cast<float>((x_bits & 0x00ffffff) | 0x3f800000 );
        
        // let y be x_div_exp, which lies in the interval [1,2). If it is equal to one, then the algorithm is done...
        float res = 1.f;
        if (close(x_div_exp, 1.f))
        {
            res = static_cast<float>(x_exponent);
        }
        else
        {
            // ...otherwise, square y until it lies in [2,4). Let m be the number of squaring times. We obtain a result 
            // z = y^2^m. --> lb(z) = 2^m*lb(y) -> lb(y) = 2^-m * lb(z) = 2^-m * (1+lb(z/2)) = 2^-m + 2^-m * lb(z/2)
            // where z/2 is again a number in [1,2). The process can be therefore iterated to construct an infinite series
            // which converges to the exact result. We can truncate the process to a fixed number of steps and approximate
            // lb(x) = exp + 2^-m1 + 2^-m1-m2 + ...
            
            /*
             * OLD VERSION, same perf, but more complex
             *  lb_iteration_data const data = {
             *      .curr_lb_arg = x_div_exp, 
             *      .accumulated_exp = 0u, 
             *      .partial = static_cast<float>(x_exponent)
             *  };
             *  float const res = (lb_iteration_step(lb_iteration_step(lb_iteration_step(lb_iteration_step
             *                    (lb_iteration_step(lb_iteration_step(lb_iteration_step(data))))))))
             *                    .partial;
             */
            
            float lb_arg = x_div_exp;
            uint32_t factored_exp = 0;
            res = static_cast<float>(x_exponent);
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
        }
        
        return res;
    }

    MMATH_FORCE_INLINE auto constexpr twoxpi(int8_t x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x >= -128 && x <= 127 && "function 'twoxp': out of expoent range for floats");
        uint32_t res_exp_bits = (x + 127) << 23;
        float res = std::bit_cast<float>(res_exp_bits);
        
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(res);
        return res;
    }

    MMATH_FORCE_INLINE auto constexpr twoxp(float x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x <= 41.2094271514 && "function 'twoxp' needs a number less than lb(std::numeric_limits<float>::max())");
        assert(x > 0 && "function 'twoxp' needs a positive number");

        uint32_t const x_bits        = std::bit_cast<uint32_t>(x);
        int8_t const x_exponent      = ((x_bits << 1) >> 24) - 127;
        int8_t const x_exponent_sign = 2 * (x_exponent >> 7) + 1; // shifts with signed numbers preserves the sign

        // compute 2^floor(x_exponent)
        float const twopower = twoxpi(x_exponent);

        // compute the remainder
        x += -x_exponent_sign * twopower;

        // taylor polynomial of the 3th grade of 2^x, valid in [-2,2]. Computed twice for better pipelining? TODO test
        float taylor_rtaylor[2] = {0};
        taylor_rtaylor[0] = 1.f + x*(detail::ln2 + x*(detail::ln2pow2halved + x*(detail::ln2pow3div6 + x*detail::ln2pow4div24)));
        taylor_rtaylor[1] = 1.f/(1.f + x*(detail::ln2 + x*(detail::ln2pow2halved + x*(detail::ln2pow3div6 + x*detail::ln2pow4div24))));

        float const res = taylor_rtaylor[x_exponent_sign > 0];
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(res);
        return res;
    }

    auto constexpr pow(float const x, float const y) -> float
    {
        // x^y = 2^lb(x^y) = 2^(y*lb(x))
        return twoxp(y*log2(x));
    }

    auto constexpr log10(float const x) -> float
    {
        return log2(x) / detail::lb10;
    }

    MMATH_FORCE_INLINE constexpr auto log2p1(float const x) -> float
    {
        MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x);
        assert(x > 0 && x < std::numeric_limits<float>::epsilon());
        float const res = detail::onedivln10 * x;
        return res;
    }

    constexpr auto log(float const x, float const b) -> float
    {
        return log(x) / log(b);
    }
}

#endif //MMATH_FPOWLOG_HPP
