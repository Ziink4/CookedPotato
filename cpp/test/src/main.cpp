#include <potato-engine/engine.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Print Test", "[print]")
{
	CHECK_NOTHROW(print_fancy());
}
