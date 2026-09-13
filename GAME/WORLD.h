#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "STRUCTS.h"

using namespace std;

bool onBorder(std::vector<std::vector<tile>>& game, point_int dot);
bool outBorder(std::vector<std::vector<tile>>& game, point_int dot);
void seed_fill_CAVE(std::vector<std::vector<tile>>& game, int seed, int fill = 0);
void iteration_CAVE(std::vector<std::vector<tile>>& game, int need);
void fill_holes_CAVE(std::vector<std::vector<tile>>& game, int minzone = 0);
void destroy_debris_CAVE(std::vector<std::vector<tile>>& game);
void build_smoothing_CAVE(std::vector<std::vector<tile>>& game);
void border_fill_CAVE(std::vector<std::vector<tile>>& game, int wall = 0);

point_int find_player_spawn(std::vector<std::vector<tile>>& game, int R, int seed);
point_int find_LEVEL_escape(std::vector<std::vector<tile>>& game, int R, int seed);
point_int set_LEVEL_escape(std::vector<std::vector<tile>>& game, int seed);
point_int set_player_spawn(std::vector<std::vector<tile>>& game, int seed);

void random_ore_spawn(std::vector<std::vector<tile>>& game, int seed, int fill);
void random_ore_grow(std::vector<std::vector<tile>>& game, int seed);
void set_ore(std::vector<std::vector<tile>>& game, int seed, int level = 0, bool grow = 0);

enum level_type {cave};
extern int MAPs;
class LEVEL
{
protected:
	int ID;
	int Seed;
	std::string Name;
	std::vector<std::vector<tile>> Grid;
	point_int Spawn;
	point_int Escape;
	level_type Type;

public:
	LEVEL(std::string n = "", level_type t = cave, int seed = 23, int size = 32) : Name(n), Type(t), Seed(seed)
	{
		ID = ++MAPs;
		Grid.resize(size, vector<tile>(size, tile(1)));
		if (Type == cave)
		{
			int i, iters = 7, fill = 75, need = 5, wall = 3, minzone = 50, debris = 2, smooth = 1, ore = 2;
			seed_fill_CAVE(Grid, seed, fill);
			for (i = 0; i < iters; i++)
			{
				iteration_CAVE(Grid, need);
			}
			border_fill_CAVE(Grid, wall);
			fill_holes_CAVE(Grid, minzone);
			for (i = 0; i < debris; i++)
			{
				destroy_debris_CAVE(Grid);
			}
			for (i = 0; i < smooth; i++)
			{
				build_smoothing_CAVE(Grid);
			}
			set_ore(Grid, seed, ore, true);
			Spawn = set_player_spawn(Grid, seed);
			Escape = set_LEVEL_escape(Grid, seed);
			switch (Type)
			{
			case cave:
				std::cout << "CAVE: ";
				break;
			default:
				std::cout << "LEVEL: ";
				break;
			}
			std::cout << Name << " with SEED: " << Seed << " GENERATED\n";
		}
	}
	int getID() { return ID; }
	int getSeed() { return Seed; }
	std::string getName() { return Name; }
	int getSize() { return Grid.size(); }
	std::vector<std::vector<tile>>& getGrid() { return Grid; }
	point_int getSpawn() { return Spawn; }

	void setName(std::string NewName) { Name = NewName; }
	bool destroy_sub(point_int sub)
	{
		if (!outBorder(Grid, sub) && Grid[sub.x][sub.y].subject != 2)
		{
			Grid[sub.x][sub.y].subject = 0;
			return true;
		}
		else
		{
			std::cout << "cant break " << sub.x << ',' << sub.y << '\n';
			return false;
		}

	}

	~LEVEL()
	{
		switch (Type)
		{
		case cave:
			std::cout << "CAVE: ";
			break;
		default:
			std::cout << "LEVEL: ";
			break;
		}
		std::cout << Name << " with SEED: " << Seed << " DELETED\n";
	}
};
//    0     1     2     3     4     5     6     7
//  {"  ", "`.", "LV", "SP", "EN", "PL", "  ", "  "},   // Пол (floor)
//  {"  ", "[]", "WA", "OR", "  ", "  ", "  ", "  "},   // Стены/объекты (subject)
//  {"  ", "@@", "  ", "  ", "  ", "  ", "  ", "  "},   // Воздух (air)
