#pragma once

namespace engine::Symbol
{
	constexpr char white = 'O';  // white diamond "\xE2\x97\x86"
	constexpr char black = '@';  // black diamond "\xE2\x97\x87"
	constexpr char square = '#'; // white diamond containing black small diamond "\xE2\x97\x88"
	constexpr char split = 'X';  // black diamond minus white x "\xE2\x9D\x96"
	constexpr char dot = '%';    // white diamond with centred dot "\xE2\x9F\x90"
} // namespace engine::Symbol