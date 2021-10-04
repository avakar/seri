#include <concepts>

#ifdef _MSC_VER
#include <stdlib.h>
#elif __GNUC__
#include <cstdint>
#endif

namespace avakar::seri {

template <std::unsigned_integral T>
requires (sizeof(T) == 1)
T _intrinsic_byte_swap(T x)
{
	return x;
}

#ifdef _MSC_VER

template <std::unsigned_integral T>
requires (sizeof(T) == 2)
T _intrinsic_byte_swap(T x)
{
	return (T)_byteswap_ushort((unsigned short)x);
}

template <std::unsigned_integral T>
requires (sizeof(T) == 4)
T _intrinsic_byte_swap(T x)
{
	return (T)_byteswap_ulong((unsigned long)x);
}

template <std::unsigned_integral T>
requires (sizeof(T) == 8)
T _intrinsic_byte_swap(T x)
{
	return (T)_byteswap_uint64((unsigned long long)x);
}

#elif defined(__GNUC__)

template <std::unsigned_integral T>
requires (sizeof(T) == 2)
T _intrinsic_byte_swap(T x)
{
	return (T)__builtin_bswap16((std::uint16_t)x);
}

template <std::unsigned_integral T>
requires (sizeof(T) == 4)
T _intrinsic_byte_swap(T x)
{
	return (T)__builtin_bswap32((std::uint32_t)x);
}

template <std::unsigned_integral T>
requires (sizeof(T) == 8)
T _intrinsic_byte_swap(T x)
{
	return (T)__builtin_bswap64((std::uint64_t)x);
}

template <std::unsigned_integral T>
requires (sizeof(T) == 16)
T _intrinsic_byte_swap(T x)
{
	return (T)__builtin_bswap128((std::uint128_t)x);
}

#endif

template <std::size_t... idxn>
constexpr void _reorder(std::byte * dest, std::byte const * src, std::index_sequence<idxn...>) noexcept
{
	std::size_t i = 0;
	(dest[i++] = src[idxn], ...);
}

template <typename Dest, typename Src>
struct _reverse_sequence;

template <typename Dest>
struct _reverse_sequence<Dest, std::index_sequence<>>
{
	using type = Dest;
};

template <std::size_t... dn, std::size_t s0, std::size_t... sn>
struct _reverse_sequence<std::index_sequence<dn...>, std::index_sequence<s0, sn...>>
	: _reverse_sequence<std::index_sequence<dn..., s0>, std::index_sequence<sn...>>
{
};

template <std::size_t n>
using make_reverse_index_sequence = typename _reverse_sequence<std::index_sequence<>, std::make_index_sequence<n>>::type;

template <std::unsigned_integral T>
constexpr T byte_swap(T x) noexcept
{
	T r;
	_reorder((std::byte *)&r, (std::byte const *)&x, make_reverse_index_sequence<sizeof(T)>);
	return r;
}

template <std::unsigned_integral T>
constexpr T byte_swap(T x) noexcept
requires requires { seri::_intrinsic_byte_swap(x); }
{
	return _intrinsic_byte_swap(x);
}

#pragma once
