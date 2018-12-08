#pragma once

#include "entity.h"

#include <array>
#include <queue>

namespace engine
{

struct Item
{
	int strength = 10;
};

class Spell {};

struct Statistics
{
	int health = 100;
	int shield = 0;
	int strength = 0;
	int defense = 0;
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
	static constexpr auto max_inventory_size = 8;
	static constexpr auto max_spellbook_size = 8;

	static constexpr auto shield_damage_resistance = 0.5f;

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
};

} // namespace engine
