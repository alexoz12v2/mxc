#if defined(MXC_SSE_AS_AVX)
#include "sse4_2vex.h"
#else
#include "sse4_2.h"
#endif

#if defined(MXC_SSE_AS_AVX)
namespace mxc::platform::x86_64::sse4_2vex
#else
namespace mxc::platform::x86_64::sse4_2
#endif
{

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnd_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> bool
{
    bool const zeroMask = static_cast<bool>(_mm_cmpestrc(astr, alen, bstr, blen, ctrl));
    return zeroMask;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAndBi_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> bool
{
    bool const zeroMaskBi = static_cast<bool>(_mm_cmpestra(astr, alen, bstr, blen, ctrl));
    return zeroMaskBi;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateIdx_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> uint32_t
{
    uint32_t const fstMatch = static_cast<bool>(_mm_cmpestri(astr, alen, bstr, blen, ctrl));
    return fstMatch;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateFstLst_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> uint32_t
{
    uint32_t const fstMaskBit = static_cast<uint32_t>(_mm_cmpestro(astr, alen, bstr, blen, ctrl));
    return fstMaskBit;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateMask_stre(
	v128ix astr,
	int32_t alen,
	v128ix bstr,
	int32_t blen
) -> v128ix
{
    v128ix const mask = _mm_cmpestrm(astr, alen, bstr, blen, ctrl);
    return mask;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnd_stri(v128ix astr, v128ix bstr) -> bool
{
    bool const zeroMask = static_cast<bool>(_mm_cmpistrc(astr, bstr, ctrl));
    return zeroMask;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAndBi_stri(v128ix astr, v128ix bstr) -> bool
{
    bool const zeroMaskBi = static_cast<bool>(_mm_cmpistra(astr, bstr, ctrl));
    return zeroMaskBi;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateFstLst_stri(v128ix astr, v128ix bstr) -> uint32_t
{
    uint32_t const fstMatch = static_cast<uint32_t>(_mm_cmpistro(astr, bstr, ctrl));
    return fstMatch;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnyZeroFst_stri(v128ix astr, v128ix bstr) -> bool
{
    bool const hasNul = static_cast<bool>(_mm_cmpistrs(astr, bstr, ctrl));
    return hasNul;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateAnyZeroSnd_stri(v128ix astr, v128ix bstr) -> bool
{
    bool const hasNul = static_cast<bool>(_mm_cmpistrz(astr, bstr, ctrl));
    return hasNul;
}

template <int32_t ctrl> requires ((ctrl & detail_pcmpestri_allctrls) == 0)
MXC_VECTOR_ABI auto cmpeqAggregateMask_stri(v128ix astr, v128ix bstr) -> v128ix
{
    v128ix const mask = _mm_cmpistrm(astr, bstr, ctrl);
    return mask;
}

MXC_VECTOR_ABI auto cmpgt_i64(v128i64 v0, v128i64 v1) -> v128i64
{
    v128i64 const vRes = _mm_cmpgt_epi64(v0, v1);
    return vRes;
}

MXC_VECTOR_ABI auto crc32cStep_u8(uint32_t currcrc, uint8_t nextpacket) -> uint32_t
{
    uint32_t const nextcrc = _mm_crc32_u8(currcrc, nextpacket);
    return nextcrc;
}

MXC_VECTOR_ABI auto crc32cStep_u16(uint32_t currcrc, uint16_t nextpacket) -> uint32_t
{
    uint32_t const nextcrc = _mm_crc32_u16(currcrc, nextpacket);
    return nextcrc;
}

MXC_VECTOR_ABI auto crc32cStep_u32(uint32_t currcrc, uint32_t nextpacket) -> uint32_t
{
    uint32_t const nextcrc = _mm_crc32_u32(currcrc, nextpacket);
    return nextcrc;
}

MXC_VECTOR_ABI auto crc32cStep_u64(uint64_t currcrc, uint64_t nextpacket) -> uint64_t
{
    uint64_t const nextcrc = _mm_crc32_u64(currcrc, nextpacket);
    return nextcrc;
}

} // namespace mxc::platform::x86_64::sse4_2
