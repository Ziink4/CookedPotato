#include "character.h"
#include "symbol.h"

#include <iostream>

namespace engine
{

void Character::print_symbol(std::ostream & out) const noexcept
{
    switch (m_type)
    {
        case type::player:
            out << Symbol::white;
            break;
        case type::npc:
            out << Symbol::square;
            break;
    }
}

void Character::print_summary(std::ostream & out) const noexcept
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
}

void Character::receive_damage(int raw_damage)
{
    int remaining_damage = raw_damage;

    std::cout << " [" << this << "] " << "Receiving " << raw_damage << " damage\n";

    int absorbed_by_shield = std::min(m_stats.shield, static_cast<int>(remaining_damage * shield_damage_resistance));

    m_stats.shield -= absorbed_by_shield;
    remaining_damage -= static_cast<int>(absorbed_by_shield / shield_damage_resistance);

    std::cout << " [" << this << "] " << absorbed_by_shield << " Absorbed by shield\n";

    m_stats.health -= remaining_damage;

    std::cout << " [" << this << "] " << remaining_damage << " Health lost\n";
}

void Character::use_weapon(std::size_t item_id, Character & target)
{
    auto selected_weapon = m_inventory.at(item_id);

    std::cout << " [" << this << "] " << "Using item " << item_id << " on" << " [" << &target << "] \n";

    target.receive_damage(selected_weapon.strength + m_stats.strength);
}

} // namespace engine
