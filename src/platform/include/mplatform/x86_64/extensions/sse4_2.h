#ifndef MXC_PLATFORM_X86_64_SSE4_2_H
#define MXC_PLATFORM_X86_64_SSE4_2_H

#include "common_types.h"
#include <cstdint>

namespace mxc::platform::x86_64::sse4_2
{

// The function works only on fixed length encoding of either 
// (U|S)BYTE (8-bit character, eg ASCII) or (U|S)WORD (16-bit character, eg UCS)

// aggregation operations
// EQUAL_EACH    == compare the two strings and produces a bitmask
// EQUAL_ANY     == first operand is an alphabet, second is the string
// RANGES        == the first operand is a set of 2 char ranges, eg "az", and bit is set if char 
// 			 	    belongs to any of the ranges
// EQUAL_ORDERED == the first string is a substring to search for in the second string
//
// aggregation operations once a string is invalidated (see below)
// EQUAL_EACH    == if one string is invalid, then false, if both are invalid, then true
// EQUAL_ANY     == bit is always set to always false
// RANGES        == bit is always set to always false
// EQUAL_ORDERED == if the second string is invalid, then false, otherwise true

// the string equality functions are arranged as "2D overloads", specifically
// - explicit vs implicit length = if both strings fit exactly in an SSE register, then there is 
// 	 	no need to specify a length, and the function performs significantly faster
// - return type = the primary result of the aggregation operation is a bitmask where the i-th
// 		bit is set only if the operation had positive outcome for the i-th character of the 
// 		string being operated on. Note: The following results can be inverted.
// 		Such bitmask can be
// 			- ANDed and returned as a boolean 					 -> _mm_cmp*strc 
// 			- AND the bitmask, and AND the result with (lb > up) -> _mm_cmpestra
//					lb = length of second string
//					up = biggest representable index in a SIMD register
//			- AND the bitmask, and AND the result with bi   	 -> _mm_cmpistra
//					bi = boolean indicating whether the second string is an 
//						 invalid implicit length string, ie a '\0' was encountered (*2)
//			- return the index of the first(LEAST) (or last(MOST)) positive result (match)
//																 -> _mm_cmp*stri
//			- return the index of the first encountered '\0' in the first string. Useless on
//				explicit string, strlen for implicit, nul terminated ones (*3)
//																 -> _mm_cmp*strs
//			- return the index of the first encountered '\0' in the second string. Useless on
//				explicit string, strlen for implicit, nul terminated ones (*3)
//																 -> _mm_cmp*strz
//			- return the first (least) bit of the mask			 -> _mm_cmp*stro
// 			(*  == either "e" or "i", depending on whether you use explicit or implicit lengths)
// 			(*2 == an explicit length string is invalidated when processing characters past the
// 				   specified length. It will affect the performed comparisons depending on the 
// 				   aggregation operation)
// 			(*3 == strlen from C++ requires a call to both _mm_cmpistri and _mm_cmpistrz, but 
// 				   the compiler SHOULD be able to optimize this to a single pcmpstri call. If not,
// 				   then rewrite the function with assembly)

inline int32_t constexpr detail_pcmpestri_allctrls = _SIDD_UBYTE_OPS | _SIDD_UWORD_OPS 
	| _SIDD_SBYTE_OPS | _SIDD_SWORD_OPS | _SIDD_CMP_EQUAL_ANY | _SIDD_CMP_RANGES 
	| _SIDD_CMP_EQUAL_EACH | _SIDD_CMP_EQUAL_ORDERED | _SIDD_NEGATIVE_POLARITY 
	| _SIDD_MASKED_NEGATIVE_POLARITY | _SIDD_LEAST_SIGNIFICANT | _SIDD_MOST_SIGNIFICANT 
	| _SIDD_BIT_MASK | _SIDD_UNIT_MASK;

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnd_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> bool;

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAndBi_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> bool;

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateIdx_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> uint32_t;

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateFstLst_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> uint32_t;

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateMask_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> v128ix;

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnd_stri(v128ix astr, v128ix bstr) -> bool;
template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAndBi_stri(v128ix astr, v128ix bstr) -> bool;
template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateFstLst_stri(v128ix astr, v128ix bstr) -> uint32_t;
template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnyZeroFst_stri(v128ix astr, v128ix bstr) -> bool;
template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnyZeroSnd_stri(v128ix astr, v128ix bstr) -> bool;
template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateMask_stri(v128ix astr, v128ix bstr) -> v128ix;

MXC_VECTOR_ABI auto cmpgt_i64(v128i64 v0, v128i64 v1) -> v128i64;

MXC_VECTOR_ABI auto crc32cStep_u8(uint32_t currcrc, uint8_t nextpacket) -> uint32_t;
MXC_VECTOR_ABI auto crc32cStep_u16(uint32_t currcrc, uint16_t nextpacket) -> uint32_t;
MXC_VECTOR_ABI auto crc32cStep_u32(uint32_t currcrc, uint32_t nextpacket) -> uint32_t;
MXC_VECTOR_ABI auto crc32cStep_u64(uint64_t currcrc, uint64_t nextpacket) -> uint64_t;

} // namespace mxc::platform::x86_64::sse4_2

#endif // MXC_PLATFORM_X86_64_SSE4_2_H
