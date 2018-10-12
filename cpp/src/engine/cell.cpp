#include <engine/cell.h>

namespace engine
{

bool Cell::occupied() const noexcept
{
    return bool(entity);
}

void Cell::swap_entities(Cell& other) noexcept
{
    entity.swap(other.entity);
}

void Cell::remove_entity() noexcept
{
    entity.reset();
}

void Cell::set_entity(std::unique_ptr<Entity>&& other) noexcept
{
    entity = std::move(other);
}

std::ostream& operator<<(std::ostream& out, const Cell& e) noexcept
{
    if (e.occupied())
    {
        return (e.entity)->print_symbol(out);
    }
    else
    {
        return out << black_symbol;
    }
}

}
