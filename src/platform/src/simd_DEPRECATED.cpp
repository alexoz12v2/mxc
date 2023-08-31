#include "mplatform/simd_DEPRECATED.h"

#include <cmath>

// WARNING: DO NOT USE. THIS USES THE HOST (Compiling machine) ARCHITECTURE ONLY, and is dependent on -march | /arch flag to generate appropriate code
// checks for architecture should be done at runtime
namespace mxc::simd
{
    MXC_INLINE /*static*/ MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::load(float const* MXC_RESTRICT farr) -> V256f
    {
        V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			checkAlignment_dbg(farr, 32u);
			res.v = _mm256_load_ps(farr);
			//#elif
			//...
		}
    	#else 
		{
            memcpy(res.v.farr, farr, V256f::size);
        }
		#endif

        return res;
    }
    
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::storeTo(float* MXC_RESTRICT farr) -> void
    {
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
            _mm256_store_ps(farr, v);
		}
        #else
		{
            memcpy(farr, v.farr, V256f::size);
		}
		#endif
    }

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator<=(V256f other) const -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_cmp_ps(v, other.v, _CMP_LE_OQ);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				res.v.u32arr[i] = v.farr[i] <= other.v.farr[i] ? 0x1111'1111u : 0;
			}
		}
		#endif
		
		return res;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator>=(V256f other) const -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_cmp_ps(v, other.v, _CMP_GE_OQ);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				res.v.u32arr[i] = v.farr[i] >= other.v.farr[i] ? 0x1111'1111u : 0;
			}
		}
		#endif

		return res;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator<(V256f other) const -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_cmp_ps(v, other.v, _CMP_LT_OQ);
		}
		#else
		{	
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				res.v.u32arr[i] = v.farr[i] < other.v.farr[i] ? 0x1111'1111u : 0;
			}
		}
		#endif

		return res;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator>(V256f other) const -> V256f
	{
		V256f res;
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_cmp_ps(v, other.v, _CMP_GT_OQ);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				res.v.u32arr[i] = v.farr[i] > other.v.farr[i] ? 0x1111'1111u : 0;
			}
		}
		#endif
		
		return res;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator==(V256f other) const -> bool
	{
		V256f memberwise = equalMemberwise(*this, other);
		
		bool res = true;
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			union alignas(32) {
				float farr[V256f::count];
				uint32_t u32arr[V256f::count];
			};

			_mm256_store_ps(farr, memberwise.v);
			for (uint32_t u32 : u32arr)
				res &= u32;
		}
		#else
		{
			for (uint32_t u32 : v.u32arr)
				res &= u32;
		}
		#endif

		return res;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator+=(V256f other) -> V256f&
	{
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			v = _mm256_add_ps(v, other.v);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				v.farr[i] += other.v.farr[i];
			}
		}
		#endif

		return *this;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator-=(V256f other) -> V256f&
	{
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			v = _mm256_sub_ps(v, other.v);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				v.farr[i] -= other.v.farr[i];
			}
		}
		#endif

		return *this;
	}

	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator*=(V256f other) -> V256f&
	{
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			v = _mm256_mul_ps(v, other.v);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				v.farr[i] *= other.v.farr[i];
			}
		}
		#endif

		return *this;
	}

	// TODO put warning on division and hsum
	MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto V256f::operator/=(V256f other) -> V256f&
	{
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			v = _mm256_div_ps(v, other.v);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				v.farr[i] /= other.v.farr[i];
			}
		}
		#endif

		return *this;
	}

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto equalMemberwise(V256f v1, V256f v2) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_cmp_ps(v1.v, v2.v, _CMP_EQ_OQ);
		}
		#else
		{
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				res.v.u32arr[i] = v.farr[i] == other.v.farr[i] ? 0x1111'1111u : 0;
			}
		}
		#endif

		return res;
	}

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator+(V256f v1, V256f v2) -> V256f
    {
        V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
            res.v = _mm256_add_ps(v1.v, v2.v);
        }
		#else
        {
            for (uint32_t i = 0; i != V256f::count; ++i)
                res.v.farr[i] = v1.v.farr[i] + v2.v.farr[i];
        }
		#endif

        return res;
    }
	

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator-(V256f v1, V256f v2) -> V256f
	{
        V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
            res.v = _mm256_sub_ps(v1.v, v2.v);
        }
		#else
        {
            for (uint32_t i = 0; i != V256f::count; ++i)
                res.v.farr[i] = v1.v.farr[i] - v2.v.farr[i];
        }
		#endif

		return res;
	}

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator*(V256f v1, V256f v2) -> V256f
	{
        V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
            res.v = _mm256_mul_ps(v1.v, v2.v);
        }
		#else
        {
            for (uint32_t i = 0; i != V256f::count; ++i)
                res.v.farr[i] = v1.v.farr[i] * v2.v.farr[i];
        }
		#endif

		return res;
	}

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto operator/(V256f v1, V256f v2) -> V256f
	{
        V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
            res.v = _mm256_div_ps(v1.v, v2.v);
        }
		#else
        {
            for (uint32_t i = 0; i != V256f::count; ++i)
                res.v.farr[i] = v1.v.farr[i] / v2.v.farr[i];
        }
		#endif

		return res;
	}

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fma(V256f v1, V256f v2, V256f v3) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX && MXC_X86_64_SUPPORTED_FMA3
		{
			res.v = _mm256_fmadd_ps(v1.v,v2.v,v3.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = v1.v.farr[i] * v2.v.farr[i] + v1.v.farr[i];
        }
		#endif

		return res;
	}

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fmsub(V256f v1, V256f v2, V256f v3) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX && MXC_X86_64_SUPPORTED_FMA3
		{
			res.v = _mm256_fmsub_ps(v1.v,v2.v,v3.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = v1.v.farr[i] * v2.v.farr[i] - v1.v.farr[i];
        }
		#endif

		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fnma(V256f v1, V256f v2, V256f v3) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX && MXC_X86_64_SUPPORTED_FMA3
		{
			res.v = _mm256_fnmadd_ps(v1.v,v2.v,v3.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = - v1.v.farr[i] * v2.v.farr[i] + v1.v.farr[i];
        }
		#endif

		return res;
	}	

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto fnmsub(V256f v1, V256f v2, V256f v3) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX && MXC_X86_64_SUPPORTED_FMA3
		{
			res.v = _mm256_fnmadd_ps(v1.v,v2.v,v3.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = - v1.v.farr[i] * v2.v.farr[i] - v1.v.farr[i];
        }
		#endif

		return res;
	}
	

    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto abs(V256f v1) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			alignas(32) float const minusOne[V256f::count] { -1.f };
			alignas(32) float const zero[V256f::count] { 0.f };
			__m256 minusOneV = _mm256_load_ps(minusOne);
			__m256 zeroV 	 = _mm256_load_ps(zero);
			__m256 mask		 = _mm256_cmp_ps(v1.v, zeroV, _CMP_GT_OQ);

			//(v[i] & maskGT0) | (-v[i] & ~maskGT0);
			res.v = _mm256_mul_ps(v1.v, minusOneV);
			res.v = _mm256_or_ps(_mm256_and_ps(mask, v1.v), _mm256_andnot_ps(mask, res.v));
        }
		#else
        {
			// TODO check if this is slower than "normal" way
			for (uint32_t i = 0; i != V256f::count; ++i)
			{
				res.v.u32arr[i] = v1.v.u32arr[i] & 0x7fff'ffff;
			}
        }
		#endif

		return res;
	}
	
	// TODO for ceil, round, floor: emit warning when using with numbers beyond MAX_SAFE_INTEGER, (2^precision - 1)
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto ceil(V256f v1) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_ceil_ps(v1.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)			
				res.v.farr[i] = std::ceil(v1.v.farr[i]);
        }
		#endif

		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto floor(V256f v1) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_floor_ps(v1.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)			
				res.v.farr[i] = std::floor(v1.v.farr[i]);
        }
		#endif

		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto round(V256f v1) -> V256f
	{
		V256f res;
	
		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_round_ps(v1.v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)			
				res.v.farr[i] = std::floor(v1.v.farr[i]);
        }
		#endif

		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto lerp(float t, V256f v0, V256f v1) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX && MXC_X86_64_SUPPORTED_FMA3
		{
			alignas(32) float const tarr[V256f::count] { t };
			__m256 tv = _mm256_load_ps(tarr);

			// fmadd(t, b, fnmadd(t, a, a)) = (t*b+(-t*a+a)) = (1-t)*a+t*b
			res.v = _mm256_fmadd_ps(tv, v1.v, _mm256_fnmadd_ps(tv, v0.v, v0.v));
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = std::lerp(v0.v.farr[i], v1.v.farr[i], t);
        }
		#endif
	
		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto sqrt(V256f v1) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_sqrt_ps(v1.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = std::sqrt(v1.v.farr[i]);
        }
		#endif
		
		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto rsqrt(V256f v1) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_rsqrt_ps(v1.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = 1.f / std::sqrt(v1.v.farr[i]);
        }
		#endif

		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto reciprocal(V256f v1) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_rcp_ps(v1.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = 1.f / v1.v.farr[i];
        }
		#endif
		
		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto max(V256f v1, V256f v2) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_max_ps(v1.v, v2.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = std::max(v1.v.farr[i], v2.v.farr[i]);
        }
		#endif
		
		return res;
	}
	
    MXC_INLINE MXC_NOT_VECTORIZED_CONSTEXPR auto min(V256f v1, V256f v2) -> V256f
	{
		V256f res;

		#if defined(__x86_64__) && MXC_X86_64_SUPPORTED_AVX
		{
			res.v = _mm256_min_ps(v1.v, v2.v);
        }
		#else
        {
			for (uint32_t i = 0; i != V256f::count; ++i)
				res.v.farr[i] = std::min(v1.v.farr[i], v2.v.farr[i]);
        }
		#endif
		
		return res;
	}

}
