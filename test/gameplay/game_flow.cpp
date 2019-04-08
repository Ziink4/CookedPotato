#include <engine/rng.h>
#include <engine/symbol.h>
#include <engine/terrain.h>
#include <engine/character.h>

#include <gameplay/split_terrain.h>
#include <gameplay/random_terrain.h>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

#include <iostream>

std::ostream & print_spawn_points(std::ostream & out, const std::vector<std::vector<engine::point>> & spawns, const engine::Terrain & t) noexcept
{
    engine::point pt;

    for (pt.y = 0; pt.y < t.height(); ++pt.y)
    {
        out << " ";

        if (pt.y % 2 == 1) out << "  ";

        for (pt.x = 0; pt.x < t.width(); ++pt.x)
        {
            const engine::Entity * const entity = t.at(pt);

            if (entity)
                entity->print_symbol(out);
            else if (std::find(spawns[0].begin(), spawns[0].end(), pt) != spawns[0].end())
                out << engine::symbol::square;
            else if (std::find(spawns[1].begin(), spawns[1].end(), pt) != spawns[1].end())
                out << engine::symbol::dot;
            else
                out << engine::symbol::black;

            out << "   ";
        }

        out << "\n";
    }

    return out << "\n";
}

TEST(Game, BasicFlow)
{
    // Create rng
    engine::random_number_engine rng{ engine::random_number_engine::default_seed };

    // Create random terrain
    engine::Terrain terrain = gameplay::generate_terrain(rng);

    // Print generated terrain
    std::cout << terrain << "\n";

    // Get spawn positions
    const auto spawn_points = gameplay::split_field(terrain, 2);

    // Print nice spawn positions
    print_spawn_points(std::cout, spawn_points, terrain);

    // Select spawn points
    std::array<engine::point, 2> selected_spawn_points;
    std::sample(std::begin(spawn_points[0]), std::end(spawn_points[0]), std::begin(selected_spawn_points), 1, rng);
    std::sample(std::begin(spawn_points[1]), std::end(spawn_points[1]), std::next(std::begin(selected_spawn_points)), 1, rng);
    
    // Print selected spawn points
    std::cout << selected_spawn_points[0] << "\n";
    std::cout << selected_spawn_points[1] << "\n";

    // Create players
    auto player_one = std::make_unique<engine::Character>(engine::Character::type::player);
    auto player_two = std::make_unique<engine::Character>(engine::Character::type::player);

	engine::Character * const player_one_ref = player_one.get();
	engine::Character * const player_two_ref = player_two.get();

    // Place players on the terrain
    terrain.place_entity(move(player_one), selected_spawn_points[0]);
    terrain.place_entity(move(player_two), selected_spawn_points[1]);

    // Print terrain
    std::cout << terrain << "\n";

	bool stop = false;
	while (!stop)
	{
		std::cout << "Pre-turn :" << "\n";
		player_one_ref->print_summary(std::cout);
		player_two_ref->print_summary(std::cout);
		std::cout << terrain << "\n";

		player_one_ref->use_weapon(0, *player_two_ref);

		std::cout << "Post-turn :" << "\n";
		player_one_ref->print_summary(std::cout);
		player_two_ref->print_summary(std::cout);
		std::cout << terrain << "\n";

		// TODO : player movement
		// Get neighbors of player
		// Spend one movement point
		// Move to random neighbor ?

		if (!player_one_ref->alive() || !player_two_ref->alive())
			stop = true;
	}

	std::cout << "End-of-game :" << "\n";
	player_one_ref->print_summary(std::cout);
	player_two_ref->print_summary(std::cout);
	std::cout << terrain << "\n";
}
