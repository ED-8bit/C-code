#include "WORLD.h"
#include <iostream>
#include <vector>
#include <random>
using namespace std;

tile::tile(){}
tile::~tile(){}

void tile::setSubject(std::unique_ptr<SUBJECT> s) { subject = std::move(s); }
void tile::setFloor(std::unique_ptr<FLOOR> f) { floor = std::move(f); }
SUBJECT* tile::getSubject() const { return subject.get(); }
FLOOR* tile::getFloor() const { return floor.get(); }

bool tile::DamageToSubject(int dmg) {
	if (!getSubject())
		return false;
	else
	{
		getSubject()->DecreaseToughness(dmg);
		return true;
	}

}

LEVEL::LEVEL(std::string n, int size, CA_gen_settings level) : Name(n), Seed(level.seed), Size(size)
{
	cout << "LEVEL" << ID << ": " << Name << " with SEED: " << Seed << " GENERATED\n";
}
LEVEL::~LEVEL()
{
	cout << "LEVEL" << ID << ": " << Name << " with SEED: " << Seed << " DELETED\n";
}

int LEVEL::getID() { return ID; } 
int LEVEL::getSeed() { return Seed; }
void LEVEL::setName(std::string NewName) { Name = NewName; }
string LEVEL::getName() { return Name; }
size_t LEVEL::getSize() { return Size; } 
vector<vector<tile>>& LEVEL::getGrid() { return Grid; } 
point_int LEVEL::getSpawn() { return Spawn; }
point_int LEVEL::getExit() { return Exit; }

bool LEVEL::DamageSubject(point_int sub, int dmg)
{
	return Grid[sub.x][sub.y].DamageToSubject(dmg);
}

LEVEL_CAVE::LEVEL_CAVE(string n, int size, CA_gen_settings cave): LEVEL(n, size, cave)
{
	ID = ++MAPs;
	Grid.resize(Size, vector<tile>(Size, tile())); // пусты
	seed_fill_CAVE(Grid, cave.seed, cave.initial_population_percent);
	for (int i = 0; i < cave.iterations; i++)
	{
		iteration_CAVE(Grid, cave.required_neighbors);
	}
	border_fill_CAVE(Grid, cave.wall_level);
	fill_holes_CAVE(Grid, cave.area_minzone);
	for (int i = 0; i < cave.debris_destruction_level; i++)
	{
		destroy_debris_CAVE(Grid);
	}
	for (int i = 0; i < cave.aliasing_level; i++)
	{
		build_smoothing_CAVE(Grid);
	}
	set_ore(Grid, cave.seed, cave.ore_richness_level, true);
	Spawn = set_player_spawn(Grid, cave.seed);
	Exit = set_LEVEL_escape(Grid, cave.seed);
	init_subs(Grid);

	cout << "CAVE " << ID << ": " << Name << " with SEED: " << Seed << " GENERATED\n";
}
LEVEL_CAVE::~LEVEL_CAVE()
{
	cout << "CAVE " << ID << ": " << Name << " with SEED: " << Seed << " DELETED\n";
}