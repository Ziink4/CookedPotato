#include <engine/terrain.h>

#include <engine/symbol.h>

namespace engine
{

std::ostream & operator<<(std::ostream & out, const Terrain & t) noexcept
{
    point pt;

    for (pt.y = 0; pt.y < t.height(); ++pt.y)
    {
        out << " ";

        if (pt.y % 2 == 1) out << "  ";

        for (pt.x = 0; pt.x < t.width(); ++pt.x)
        {
            const Entity * const entity = t.at(pt);

            if (entity)
                entity->print_symbol(out);
            else
                out << symbol::black;

            out << "   ";
        }

        out << "\n";
    }

    return out << "\n";
}

} // namespace engine
