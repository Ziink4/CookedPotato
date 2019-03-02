#pragma once

namespace engine
{

enum class Symbol : char
{
    white  = 'O', // white diamond "\xE2\x97\x86"
    black  = '@', // black diamond "\xE2\x97\x87"
    square = '#', // white diamond containing black small diamond "\xE2\x97\x88"
    split  = 'X', // black diamond minus white x "\xE2\x9D\x96"
    dot    = '%', // white diamond with centred dot "\xE2\x9F\x90"
};

inline std::ostream & operator<<(std::ostream & out, Symbol s) noexcept
{
    return out << static_cast<char>(s);
}

} // namespace engine
