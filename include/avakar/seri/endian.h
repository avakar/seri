#ifndef AVAKAR_SERI_ENDIAN_h
#define AVAKAR_SERI_ENDIAN_h

#if __has_include(<version>)
#include <version>
#endif

#ifdef __cpp_lib_endian

#include <bit>

namespace avakar::seri {
using std::endian;
}

#else

namespace avakar::seri {

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

}

#endif

namespace avakar::seri {

inline constexpr bool is_reverse_endian(endian e) noexcept
{
	if constexpr (endian::little == endian::native)
	{
		return e == endian::big;
	}
	else if constexpr (endian::big == endian::native)
	{
		return e == endian::little;
	}
	else
	{
		return false;
	}
}

}

#endif // _h
