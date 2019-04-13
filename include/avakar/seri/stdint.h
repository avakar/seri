#ifndef AVAKAR_SERI_STDINT_h
#define AVAKAR_SERI_STDINT_h

#include "packed_int.h"

namespace avakar::seri {

using u16_ne_t = ne<uint16_t>;
using u32_ne_t = ne<uint32_t>;
using u64_ne_t = ne<uint64_t>;

using u16_le_t = le<uint16_t>;
using u32_le_t = le<uint32_t>;
using u64_le_t = le<uint64_t>;

using u16_be_t = be<uint16_t>;
using u32_be_t = be<uint32_t>;
using u64_be_t = be<uint64_t>;

}

#endif // _h
	