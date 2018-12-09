#pragma once

#include "entity.h"

namespace engine
{

class Obstacle : public Entity
{
    void print_summary(std::ostream& out) const noexcept override;

    void print_symbol(std::ostream& out) const noexcept override;
};

} // namespace engine
