#pragma once

#include <potato-engine/point.h>

#include <array>

#include <iostream> // For std::cerr, std::endl

namespace engine
{

class Item {};

class Spell {};

struct Statistics
{
    std::size_t level;
    std::size_t health;
};

class Entity
{

public:
    enum class entity_type { player, npc };

private:
    static constexpr auto max_inventory_size = 8;
    static constexpr auto max_spellbook_size = 8;

    using position_type = Point<std::size_t>; //TODO: Point or Cell ?
    using id_type = std::size_t;

    // position
    position_type m_position;

    // type
    entity_type m_type;

    // nom/id
    id_type m_id;

    // inventaire
    std::array<Item, max_inventory_size> m_inventory;

    // sorts
    std::array<Spell, max_spellbook_size> m_spellbook;

    // vie
    Statistics m_stats;

public:
    constexpr explicit Entity(position_type pt, entity_type type, id_type id) noexcept
        : m_position(pt),
          m_type(type),
          m_id(id),
          m_inventory(),
          m_spellbook(),
          m_stats()
    { }

    constexpr Entity() noexcept = delete;

    constexpr Entity(const Entity&) noexcept = delete;
    constexpr Entity(Entity&&) noexcept = delete;
    constexpr Entity& operator=(const Entity&) noexcept = delete;
    constexpr Entity& operator=(Entity&&) noexcept = delete;

    constexpr const entity_type& type() const noexcept
    {
        return m_type;
    }

    friend std::ostream& operator<<(std::ostream& out, const Entity& e) noexcept;

    friend std::ostream& operator<<(std::ostream& out, const entity_type& e) noexcept;
};

} // namespace engine
