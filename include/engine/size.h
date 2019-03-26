#pragma once

#include <ostream>

namespace engine
{

struct size
{
    unsigned width;
    unsigned height;
};

inline std::ostream & operator<<(std::ostream & out, const size & sz) noexcept
{
    return out << "size(" << sz.width << ", " << sz.height << ")";
}

} // namespace engine
