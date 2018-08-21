#include <potato-engine/character.h>

namespace engine
{

std::ostream& Character::print_symbol(std::ostream& out) const noexcept
{
	/* static */ constexpr auto white  = "\xE2\x97\x86"; // white diamond
	/* static */ constexpr auto black  = "\xE2\x97\x87"; // black diamond

	switch (m_type)
	{
		case character_type::player:
			return out << black;
		case character_type::npc:
			return out << white;
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
