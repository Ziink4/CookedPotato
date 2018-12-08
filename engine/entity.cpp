#include "entity.h"

namespace engine
{

std::ostream& operator<<(std::ostream& out, const Entity& e) noexcept
{
	e.print_summary(out);
	return out;
}

} // namespace engine
