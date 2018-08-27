#include <potato-engine/character.h>
#include <potato-engine/symbol.h>

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
	out << "Character(";
	out << "type = ";
	print_symbol(out);
	out << ", ";
	out << "items = " << m_inventory.size();
	out << ", ";
	out << "spells = " << m_spellbook.size();
	out << ")";
	return  out;
}

}
