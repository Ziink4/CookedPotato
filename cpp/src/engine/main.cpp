#include <potato-engine/engine.h>
#include <potato-engine/terrain.h>

#include "main.h"

namespace engine
{

void print_fancy()
{
	std::cerr << "WOOO" << std::endl;
	std::cerr << terrain::width << std::endl;
	print();
}

}
