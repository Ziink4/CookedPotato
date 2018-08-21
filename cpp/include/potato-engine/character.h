#pragma once

#include <potato-engine/entity.h>

#include <array>

namespace engine
{

class Item {};

class Spell {};

class Statistics {};

class Character : public Entity
{

public:
	enum class character_type
	{
		player,
		npc
	};

private:
	static constexpr auto max_inventory_size = 8;
	static constexpr auto max_spellbook_size = 8;

	// type
	character_type m_type;

	// inventaire
	std::array<Item, max_inventory_size> m_inventory;

	// sorts
	std::array<Spell, max_spellbook_size> m_spellbook;

	// vie
	Statistics m_stats;

public:
	constexpr explicit Character(character_type type) noexcept
	    : m_type(type),
	      m_inventory(),
	      m_spellbook(),
	      m_stats()
	{ }

	constexpr const auto& type() const noexcept
	{
		return m_type;
	}

	std::ostream& print_symbol(std::ostream& out) const noexcept override;

	std::ostream& print_summary(std::ostream& out) const noexcept override;
};

} // namespace engine
