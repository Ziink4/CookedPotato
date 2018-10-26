#include <engine/obstacle.h>
#include <engine/symbol.h>

namespace engine
{

std::ostream& Obstacle::print_symbol(std::ostream& out) const noexcept
{
	return out << split_symbol;
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
