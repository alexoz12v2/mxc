#ifndef MINMATH_COMMON_PRIVATE_HPP
#define MINMATH_COMMON_PRIVATE_HPP

#include <cassert>
#include <limits>

#ifndef MMATH_ALLOW_DENORMAL

#define MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x)\
do {\
assert(!isDenormal((x)) && (x) != std::numeric_limits<float>::infinity()\
&& (x) != -std::numeric_limits<float>::infinity() && (x)==(x)/*not NaN*/\
&& "float input is not a finite normalized number");\
}while(false)

#else

// naming of this macro is awkward, because it's not checking if number is normalized
#define MMATH_ASSERT_FINITE_NORMALIZED_FLOAT(x)\
do {\
assert((x) != std::numeric_limits<float>::infinity()\
&& (x) != -std::numeric_limits<float>::infinity() && (x)==(x)/*not NaN*/\
&& "float input is not a finite normalized number");\
}while(false)

#endif // defined(MMATH_ALLOW_DENORMAL)

#if defined(_WIN32 && _MSC_VER)
#define MMATH_FORCE_INLINE __forceinline
#elseif defined(__linux__) || defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined (__MACH__) || defined(__GNUC__) || defined(__clang__)
#define MMATH_FORCE_INLINE __attribute__((always_inline))
#endif


#if std::numeric_limits<float>::is_iec559 == false
#error "minmath requires IEEE754 floating point"
#endif

#endif // MINMATH_COMMON_PRIVATE_HPP