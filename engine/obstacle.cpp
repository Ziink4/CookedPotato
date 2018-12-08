#include "obstacle.h"
#include "symbol.h"

#include <ostream>

namespace engine
{

void Obstacle::print_symbol(std::ostream& out) const noexcept
{
	out << split_symbol;
}

void Obstacle::print_summary(std::ostream& out) const noexcept
{
	out << "Obstacle(";
	out << "symbol = ";
	print_symbol(out);
	out << ")";
}

}
