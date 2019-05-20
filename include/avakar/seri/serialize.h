#ifndef AVAKAR_SERI_SERIALIZE_h
#define AVAKAR_SERI_SERIALIZE_h

#include <algorithm>
#include <cstring>
#include <stdint.h>
#include <type_traits>

namespace avakar::seri {

template <typename T>
auto deserialize_ne(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>, T>
{
	T r;
	std::memcpy(&r, bytes, sizeof(T));
	return r;
}

template <typename T>
auto deserialize_re(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>, T>
{
	T r;
	std::reverse_copy(bytes, bytes + sizeof(T), reinterpret_cast<uint8_t *>(&r));
	return r;
}

template <typename T>
auto deserialize_le(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T>, T>
{
	T r = bytes[sizeof(T)-1];
	for (size_t i = sizeof(T) - 1; i != 0; --i)
		r = (r << 8) | bytes[i-1];
	return r;
}

template <typename T>
auto deserialize_be(uint8_t const * bytes)
	-> std::enable_if_t<std::is_integral_v<T>, T>
{
	T r = bytes[0];
	for (size_t i = 1; i != sizeof(T); ++i)
		r = (r << 8) | bytes[i];
	return r;
}

template <typename T>
auto deserialize_le(uint8_t const * bytes)
	-> std::enable_if_t<std::is_enum_v<T>, T>
{
	std::underlying_type_t<T> r = bytes[sizeof(T)-1];
	for (size_t i = sizeof(T) - 1; i != 0; --i)
		r = (r << 8) | bytes[i-1];
	return static_cast<T>(r);
}

template <typename T>
auto deserialize_be(uint8_t const * bytes)
	-> std::enable_if_t<std::is_enum_v<T>, T>
{
	std::underlying_type_t<T> r = bytes[0];
	for (size_t i = 1; i != sizeof(T); ++i)
		r = (r << 8) | bytes[i];
	return static_cast<T>(r);
}

template <typename T>
auto serialize_ne(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>
{
	std::memcpy(bytes, &value, sizeof(T));
}

template <typename T>
auto serialize_re(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>
{
	uint8_t const * p = reinterpret_cast<uint8_t const *>(&value);
	std::reverse_copy(p, p + sizeof(T), bytes);
}

template <typename T>
auto serialize_le(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	for (size_t i = 0; i != sizeof(T); ++i)
	{
		bytes[i] = (uint8_t)value;
		value = value >> 8;
	}
}

template <typename T>
auto serialize_be(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_integral_v<T>>
{
	for (size_t i = sizeof(T); i != 0; --i)
	{
		bytes[i-1] = (uint8_t)value;
		value = value >> 8;
	}
}

template <typename T>
auto serialize_le(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_enum_v<T>>
{
	std::underlying_type_t<T> v = static_cast<std::underlying_type_t<T>>(value);
	for (size_t i = 0; i != sizeof(T); ++i)
	{
		bytes[i] = (uint8_t)v;
		v = v >> 8;
	}
}

template <typename T>
auto serialize_be(uint8_t * bytes, T value)
	-> std::enable_if_t<std::is_enum_v<T>>
{
	std::underlying_type_t<T> v = static_cast<std::underlying_type_t<T>>(value);
	for (size_t i = sizeof(T); i != 0; --i)
	{
		bytes[i-1] = (uint8_t)v;
		v = v >> 8;
	}
}

}

#endif // _h
