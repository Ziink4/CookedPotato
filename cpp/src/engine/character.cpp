#include <engine/character.h>
#include <engine/symbol.h>

namespace engine
{

std::ostream& Character::print_symbol(std::ostream& out) const noexcept
{
	switch (m_type)
	{
		case type::player:
			return out << white_symbol;
		case type::npc:
			return out << square_symbol;
	}
}

std::ostream& Character::print_summary(std::ostream& out) const noexcept
{
	out << " [" << this << "] ";
	out << "Character(";
	out << "type = ";
	print_symbol(out);
	out << ", ";
	out << "health = " << m_stats.health;
	out << ", ";
	out << "shield = " << m_stats.shield;
	out << ")";
	return  out;
}

void Character::receive_damage(int raw_damage)
{
    int remaining_damage = raw_damage;

    std::cout << " [" << this << "] " << "Receiving " << raw_damage << " damage" << std::endl;

    int absorbed_by_shield = std::min(m_stats.shield, static_cast<int>(remaining_damage * shield_damage_resistance));

    m_stats.shield -= absorbed_by_shield;
    remaining_damage -= static_cast<int>(absorbed_by_shield / shield_damage_resistance);

    std::cout << " [" << this << "] " << absorbed_by_shield << " Absorbed by shield" << std::endl;

    m_stats.health -= remaining_damage;

    std::cout << " [" << this << "] " << remaining_damage << " Health lost" << std::endl;
}

void Character::use_weapon(std::size_t item_id, Character& target)
{
	auto selected_weapon = m_inventory.at(item_id);

	std::cout << " [" << this << "] " << "Using item " << item_id << " on" << " [" << &target << "] " <<  std::endl;

	target.receive_damage(selected_weapon.strength + m_stats.strength);
}

}
