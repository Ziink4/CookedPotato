#pragma once

namespace engine::symbol
{

constexpr char white[]  = "\033[47;30mO\033[0m"; // white diamond "\xE2\x97\x86"
constexpr char black[]  = "\033[40;37m@\033[0m"; // black diamond "\xE2\x97\x87"
constexpr char square[] = "\033[41;37m#\033[0m"; // white diamond containing black small diamond "\xE2\x97\x88"
constexpr char split[]  = "\033[42;37mX\033[0m"; // black diamond minus white x "\xE2\x9D\x96"
constexpr char dot[]    = "\033[43;37m%\033[0m"; // white diamond with centred dot "\xE2\x9F\x90"

} // namespace engine::symbol