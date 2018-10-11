#pragma once

#include <engine/entity.h>

namespace engine
{

class Obstacle : public Entity
{
	std::ostream& print_summary(std::ostream& out) const noexcept override;

	std::ostream& print_symbol(std::ostream& out) const noexcept override;
};

} // namespace engine
