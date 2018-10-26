#pragma once

#include <iostream>

namespace engine
{

class Entity
{
public:
	virtual std::ostream& print_summary(std::ostream& out) const noexcept = 0;

	virtual std::ostream& print_symbol(std::ostream& out) const noexcept = 0;

	virtual ~Entity() = default;
};

std::ostream& operator<<(std::ostream& out, const Entity& e) noexcept;

} // namespace engine
