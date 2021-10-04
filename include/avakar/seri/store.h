#ifndef AVAKAR_SERI_STORE_h
#define AVAKAR_SERI_STORE_h

#include "endian.h"
#include "serialize.h"
#include <stdint.h>
#include <type_traits>

namespace avakar::seri {

template <endian e, typename T>
auto load(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>, T>
{
	if constexpr (e == endian::native)
		return deserialize_ne<T>(bytes);
	else if constexpr (is_reverse_endian(e))
		return deserialize_re<T>(bytes);
	else if constexpr (e == endian::little)
		return deserialize_le<T>(bytes);
	else if constexpr (e == endian::big)
		return deserialize_be<T>(bytes);
}

template <typename T>
auto load_ne(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T>, T>
{
	return load<endian::native, T>(bytes);
}

template <typename T>
auto load_le(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T>, T>
{
	return load<endian::little, T>(bytes);
}

template <typename T>
auto load_be(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T>, T>
{
	return load<endian::big, T>(bytes);
}

template <endian e, typename T>
auto store(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	if constexpr (e == endian::native)
		serialize_ne<T>(bytes, value);
	else if constexpr (is_reverse_endian(e))
		serialize_re<T>(bytes, value);
	else if constexpr (e == endian::little)
		serialize_le<T>(bytes, value);
	else if constexpr (e == endian::big)
		serialize_be<T>(bytes, value);
}

template <typename T>
auto store_ne(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	store<endian::native>(bytes, value);
}

template <typename T>
auto store_le(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	store<endian::little>(bytes, value);
}

template <typename T>
auto store_be(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	store<endian::big>(bytes, value);
}

}

#endif // _h
