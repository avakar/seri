#include <avakar/seri.h>
#include <catch2/catch.hpp>
using namespace avakar::seri;

TEST_CASE("little") {
	static constexpr uint8_t data[] = { 1, 0, 0, 0 };

	u32_le_t x;
	memcpy(&x, data, sizeof x);

	REQUIRE(x == 1);
}

TEST_CASE("big") {
	u32_be_t x = { 1, 0, 0, 0 };

	REQUIRE(x == 0x1000000);
}
