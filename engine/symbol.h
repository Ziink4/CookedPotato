#pragma once

namespace engine
{

struct Symbol
{
    static constexpr auto white  = 'O'; // white diamond "\xE2\x97\x86"
    static constexpr auto black  = '@'; // black diamond "\xE2\x97\x87"
    static constexpr auto square = '#'; // white diamond containing black small diamond "\xE2\x97\x88"
    static constexpr auto split  = 'X'; // black diamond minus white x "\xE2\x9D\x96"
    static constexpr auto dot    = '¤';  // white diamond with centred dot "\xE2\x9F\x90"
};

} // namespace engine
