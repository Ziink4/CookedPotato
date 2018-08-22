#include <potato-engine/character.h>
#include <potato-engine/symbol.h>

namespace engine
{

std::ostream& Character::print_symbol(std::ostream& out) const noexcept
{
	switch (m_type)
	{
		case character_type::player:
			return out << black_symbol;
		case character_type::npc:
			return out << white_symbol;
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
