#include <engine/terrain.h>

#include <engine/symbol.h>
#include <engine/directions.h>

namespace engine
{

std::ostream & operator<<(std::ostream & out, const Terrain & t) noexcept
{
    point pt;

    for (pt.y = 0; pt.y < terrain_height; ++pt.y)
    {
        out << " ";

        if (pt.y % 2 == 1) out << "  ";

        for (pt.x = 0; pt.x < terrain_width; ++pt.x)
        {
            const Entity * const entity = t.at(pt);

            if (entity)
                entity->print_symbol(out);
            else
                out << Symbol::black;

            out << "   ";
        }

        out << "\n";
    }

    return out << "\n";
}

std::ostream & operator<<(std::ostream & out, const CardinalDirections & d) noexcept
{
    out << "Directions(";
    if (d.north) out << "north = " << *d.north;
    out << ", ";
    if (d.east) out << "east = " << *d.east;
    out << ", ";
    if (d.south) out << "south = " << *d.south;
    out << ", ";
    if (d.west) out << "west = " << *d.west;
    out << ")";
    return out;
}

} // namespace engine
