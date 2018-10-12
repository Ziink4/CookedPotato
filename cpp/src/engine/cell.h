#pragma once

#include <engine/symbol.h>
#include <engine/entity.h>

#include <memory>

namespace engine
{

class Cell
{
    std::unique_ptr<Entity> entity;

public:
    bool occupied() const noexcept;

    void swap_entities(Cell& other) noexcept;

    void remove_entity() noexcept;

    void set_entity(std::unique_ptr<Entity>&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& out, const Cell& e) noexcept;
};

}
