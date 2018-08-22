#pragma once

#include <potato-engine/entity.h>
#include <potato-engine/engine.h>
#include <potato-engine/point.h>
#include <potato-engine/rng.h>

#include <cstddef> // For std::size_t
#include <array> // For std::array
#include <ostream> // For operator<<
#include <memory>

namespace engine
{

class Terrain
{
public:
	using size_type = std::size_t;
	static constexpr size_type width = 10;
	static constexpr size_type height = 20;
	static constexpr size_type area = width * height;

	using value_type = std::unique_ptr<Entity>;
	using storage_type = std::array<value_type, area>;

	constexpr storage_type& data() noexcept
	{
		return m_data;
	}

	constexpr const storage_type& data() const noexcept
	{
		return m_data;
	}

	friend std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept;

private:
	storage_type m_data;
};

constexpr bool is_valid(cell_type cell) noexcept
{
	return cell < Terrain::area;
}

constexpr bool is_valid(const point_type& pt) noexcept
{
	return pt.x < Terrain::width && pt.y < Terrain::height;
}

constexpr point_type::value_type get_x(cell_type cell) noexcept
{
	return cell % Terrain::width;
}

constexpr point_type::value_type get_y(cell_type cell) noexcept
{
	return cell / Terrain::width;
}

constexpr point_type get_pt(cell_type cell) noexcept
{
	return {get_x(cell), get_y(cell)};
}

constexpr cell_type get_cell(const point_type& pt) noexcept
{
	return pt.x + pt.y * Terrain::width;
}

Terrain generate_terrain(RandomNumberGenerator& rng) noexcept;

void split_field(Terrain& t, std::size_t parts) noexcept;

} // namespace engine
