#ifndef AVAKAR_SERI_PACKED_INT_h
#define AVAKAR_SERI_PACKED_INT_h

#include "endian.h"
#include "store.h"
#include <type_traits>

namespace avakar::seri {

template <typename... An>
struct _is_byte_pack;

template <>
struct _is_byte_pack<>
	: std::true_type
{
};

template <typename A0, typename... An>
struct _is_byte_pack<A0, An...>
	: std::integral_constant<bool, std::is_convertible_v<A0, uint8_t> && _is_byte_pack<An...>::value>
{
};

template <endian e, typename T>
struct packed_int
{
	packed_int()
	{
	}

	packed_int(T v)
	{
		*this = v;
	}

	template <typename... An,
		std::enable_if_t<sizeof...(An) == sizeof(T) && _is_byte_pack<An...>::value, int> = 1>
	packed_int(An... an)
		: bytes{ (uint8_t)an... }
	{
	}

	operator T() const
	{
		return load<e, T>(bytes);
	}

	packed_int & operator=(T v)
	{
		store<e>(bytes, v);
		return *this;
	}

	uint8_t bytes[sizeof(T)];
};

template <typename T>
using ne = packed_int<endian::native, T>;

template <typename T>
using le = packed_int<endian::little, T>;

template <typename T>
using be = packed_int<endian::big, T>;

}

#endif // _h
