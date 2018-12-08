#pragma once

#include <ostream>

namespace engine
{

class Entity
{
public:
	virtual void print_summary(std::ostream& out) const noexcept = 0;

	virtual void print_symbol(std::ostream& out) const noexcept = 0;

	virtual ~Entity() = default;
};

std::ostream& operator<<(std::ostream& out, const Entity& e) noexcept;

} // namespace engine
