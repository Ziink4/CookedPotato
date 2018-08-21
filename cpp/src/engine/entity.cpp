#include <potato-engine/entity.h>

namespace engine
{

std::ostream& operator<<(std::ostream& out, const Entity& e) noexcept
{
    out << "Entity(";
    out << "position = " << e.m_position;
    out << ", ";
    out << "type = " << e.m_type;
    out << ", ";
    out << "id = " << e.m_id;
    out << ", ";
    out << "items = " << e.m_inventory.size();
    out << ", ";
    out << "spells = " << e.m_spellbook.size();
    out << ")";
    return  out;
}

std::ostream& operator<<(std::ostream& out, const Entity::entity_type& e) noexcept
{
    /* static */ constexpr auto white  = "\xE2\x97\x86"; // white diamond
    /* static */ constexpr auto black  = "\xE2\x97\x87"; // black diamond

    switch (e)
    {
        case Entity::entity_type::player: return out << black;
        case Entity::entity_type::npc:    return out << white;
    }

}

} // namespace engine
