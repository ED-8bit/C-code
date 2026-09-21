#pragma once
#include <vector>
#include <string>
#include "STRUCTS.h"
enum subs
{
	S_none, S_stone, S_ore, S_endstone 
};
enum floors {
	F_none, F_stone, F_stone_exit, F_stone_spawn
};
class SUBJECT {
private:
	subs type;
	int toughness;
public:
	SUBJECT();
	SUBJECT(subs t);
	~SUBJECT();

	void CalcToughness();

	void setType(subs nt) { type = nt; }
	void setToughness(int nt) { toughness = nt; }
	subs getType() { return type; }
	int getToughness() { return toughness; }
};
class FLOOR
{
private:
	floors type;
public:
	FLOOR();
	FLOOR(floors t);
	~FLOOR();

	void setType(floors nt) { type = nt; }
	floors getType() { return type; }

};

class tile
{
private:
	SUBJECT subject;
	FLOOR floor;

public:
	tile(subs s, floors f);
	~tile();

	void setSubject(SUBJECT NewSub) { subject = NewSub; }
	void setFloor(FLOOR NewFloor) { floor = NewFloor; }
	SUBJECT& getSubject() { return subject; }
	FLOOR& getFloor() { return floor; }

};

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
//    0     1     2     3     4     5     6     7
//  {"  ", "`.", "LV", "SP", "EN", "PL", "  ", "  "},   // Пол (floor)
//  {"  ", "[]", "WA", "OR", "  ", "  ", "  ", "  "},   // Стены/объекты (subject)
//  {"  ", "@@", "  ", "  ", "  ", "  ", "  ", "  "},   // Воздух (air)
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
	LEVEL(std::string n = "", level_type t = cave, int seed = 23, int size = 32); // Генерация уровня в конструкторе
	int getID() { return ID; }
	int getSeed() { return Seed; }
	std::string getName() { return Name; }
	size_t getSize() { return Grid.size(); }
	std::vector<std::vector<tile>>& getGrid() { return Grid; }
	point_int getSpawn() { return Spawn; }

	void setName(std::string NewName) { Name = NewName; }
	bool destroy_sub(point_int sub); // Уничтожить объект по координатам

	~LEVEL();
};

