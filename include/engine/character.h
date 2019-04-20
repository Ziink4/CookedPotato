#pragma once

#include <engine/entity.h>

#include <array>

namespace engine
{

struct Item
{
    int strength = 50;
};

class Spell {};

struct Statistics
{
    int health = 100;
    int shield = 0;
    int strength = 0;
    int defense = 0;
	
	int movement = 3;
	int action = 2;
};

class Character : public Entity
{

public:
    enum class type
    {
        player,
        npc
    };

private:
    static constexpr unsigned max_inventory_size = 8;
    static constexpr unsigned max_spellbook_size = 8;

    static constexpr double shield_damage_resistance = 0.5;

    // type
    type m_type;

    // inventaire
    std::array<Item, max_inventory_size> m_inventory;

    // sorts
    std::array<Spell, max_spellbook_size> m_spellbook;

    // vie
    Statistics m_stats;

public:
    explicit Character(type type) noexcept
        : m_type(type),
          m_inventory(),
          m_spellbook(),
          m_stats()
    { }

    constexpr type type() const noexcept
    {
        return m_type;
    }

    void use_weapon(std::size_t item_id, Character& target);

    void receive_damage(int raw_damage);

    void print_symbol(std::ostream& out) const noexcept override;

    void print_summary(std::ostream& out) const noexcept override;

	constexpr bool alive() const noexcept
	{
		return m_stats.health > 0;
	}

	constexpr bool can_move(int distance = 1) const noexcept
	{
		return distance > 0 && m_stats.movement >= distance;
	}
};

} // namespace engine
