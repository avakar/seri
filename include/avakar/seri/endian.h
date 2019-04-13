#ifndef AVAKAR_SERI_ENDIAN_h
#define AVAKAR_SERI_ENDIAN_h

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

#endif // _h
