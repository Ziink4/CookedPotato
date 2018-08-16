#include <potato-engine/engine.h>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

CATCH_TEST_CASE("Print Test", "[print]")
{
	CATCH_CHECK_NOTHROW(print_fancy());
}
