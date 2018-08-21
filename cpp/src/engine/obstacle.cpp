#include <potato-engine/obstacle.h>

namespace engine
{

std::ostream& Obstacle::print_symbol(std::ostream& out) const noexcept
{
	/* static */ constexpr auto white  = "\xE2\x97\x86"; // white diamond
	return out << white;
}

std::ostream& Obstacle::print_summary(std::ostream& out) const noexcept
{
	out << "Obstacle(";
	out << "symbol = ";
	print_symbol(out);
	out << ")";
	return out;
}

}
