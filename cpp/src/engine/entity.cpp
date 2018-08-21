#include <potato-engine/entity.h>

namespace engine
{

std::ostream& operator<<(std::ostream& out, const Entity& e) noexcept
{
	return e.print_summary(out);
}

} // namespace engine
