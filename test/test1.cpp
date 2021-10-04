#include <avakar/seri.h>
#include <avakar/mutest.h>
using namespace avakar::seri;

mutest_case("little") {
	static constexpr uint8_t data[] = { 1, 0, 0, 0 };

	u32_le_t x;
	memcpy(&x, data, sizeof x);

	chk(x == 1);
}

mutest_case("big") {
	u32_be_t x = { 1, 0, 0, 0 };

	chk(x == 0x1000000);
}
