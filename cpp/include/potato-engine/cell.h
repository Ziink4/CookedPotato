#pragma once

#include <potato-engine/symbol.h>
#include <potato-engine/entity.h>

#include <memory>

namespace engine
{

class Cell
{
    std::unique_ptr<Entity> entity;

public:
    bool occupied() const noexcept
    {
        return bool(entity);
    }

    void reset(Entity* e) noexcept
    {
        return entity.reset(e);
    }

    void clear() noexcept
    {
        return entity.reset(nullptr);
    }

    inline friend std::ostream& operator<<(std::ostream& out, const Cell& e) noexcept
    {
        if (e.occupied())
        {
            return e.entity->print_symbol(out);
        }
        else
        {
            return out << black_symbol;
        }
    }
};

}
