#ifndef AVAKAR_SERI_STORE_h
#define AVAKAR_SERI_STORE_h

#include "endian.h"
#include "serialize.h"
#include <stdint.h>
#include <type_traits>

namespace avakar::seri {

template <endian e, typename T>
auto load(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T>, T>
{
	if constexpr (e == endian::native)
		return deserialize_ne<T>(bytes);
	else if constexpr (e == endian::reverse)
		return deserialize_re<T>(bytes);
	else if constexpr (e == endian::little)
		return deserialize_le<T>(bytes);
	else if constexpr (e == endian::big)
		return deserialize_be<T>(bytes);
	else
		static_assert(false, "unsuported endianity");
}

template <endian e, typename T>
auto store(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	if constexpr (e == endian::native)
		serialize_ne<T>(bytes, value);
	else if constexpr (e == endian::reverse)
		serialize_re<T>(bytes, value);
	else if constexpr (e == endian::little)
		serialize_le<T>(bytes, value);
	else if constexpr (e == endian::big)
		serialize_be<T>(bytes, value);
	else
		static_assert(false, "unsuported endianity");
}

}

#endif // _h
