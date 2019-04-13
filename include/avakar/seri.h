#ifndef AVAKAR_AVAKAR_SERI_h
#define AVAKAR_AVAKAR_SERI_h

#include <algorithm>
#include <iterator>
#include <stdint.h>
#include <string.h>
#include <type_traits>

namespace avakar {

enum class endian
{
#ifdef _WIN32
	little = 0,
	big = 1,
	native = little,
	reverse = big,
#else
	little = __ORDER_LITTLE_ENDIAN__,
	big = __ORDER_BIG_ENDIAN__,
	native = __BYTE_ORDER__,

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	reverse = big,
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	reverse = little,
#endif
#endif
};

template <typename T>
struct native
{
	operator T() const
	{
		T r;
		memcpy(&r, _bytes, sizeof(T));
		return r;
	}

	native & operator=(T v)
	{
		memcpy(_bytes, &v, sizeof(T));
		return *this;
	}

private:
	uint8_t _bytes[sizeof(T)];
};

template <typename T>
struct reverse
{
	operator T() const
	{
		T r;
		std::reverse_copy(_bytes, std::end(_bytes), reinterpret_cast<uint8_t *>(&r));
		return r;
	}

	reverse & operator=(T v)
	{
		memcpy(_bytes, &v, sizeof(T));
		std::reverse(_bytes, std::end(_bytes));
		return *this;
	}

private:
	uint8_t _bytes[sizeof(T)];
};

template <typename T>
struct _little
{
	using type = std::conditional_t<endian::little == endian::native, native<T>,
		std::conditional_t<endian::little == endian::reverse, reverse<T>, void>>;
};

template <typename T>
struct _big
{
	using type = std::conditional_t<endian::big == endian::native, native<T>,
		std::conditional_t<endian::big == endian::reverse, reverse<T>, void>>;
};

template <typename T>
using little_t = typename _little<T>::type;

template <typename T>
using big_t = typename _big<T>::type;

using u16_ne_t = native<uint16_t>;
using u32_ne_t = native<uint32_t>;
using u64_ne_t = native<uint64_t>;

using u16_le_t = little_t<uint16_t>;
using u32_le_t = little_t<uint32_t>;
using u64_le_t = little_t<uint64_t>;

using u16_be_t = big_t<uint16_t>;
using u32_be_t = big_t<uint32_t>;
using u64_be_t = big_t<uint64_t>;

}

#endif // _h
