#pragma once
#include <vector>
#include <string>
#include <memory>
#include "STRUCTS.h"
#include "OBJECTS.h"
// test

class tile
{
private:
	unique_ptr<SUBJECT> subject;
	unique_ptr<FLOOR> floor;
public:
	tile();
	~tile();
	
	void setSubject(std::unique_ptr<SUBJECT> s); // Установливает новый объект в тайл
	void setFloor(std::unique_ptr<FLOOR> f); // Устанавливает новую поверхность в тайл
	SUBJECT* getSubject() const; // Возвращает указатель на объект из тайла
	FLOOR* getFloor() const; // Возвращает указатель на поверхность из тайла

	bool DamageToSubject(int dmg); // Возвращает результат действия. Наносит урон объекту тайла. Удаляет его когда прочность достигает нуля
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
	int Size;
	std::vector<std::vector<tile>> Grid;
	point_int Spawn;
	point_int Exit;
public:
	LEVEL(std::string n = "", int size, CA_gen_settings level); // Генерация уровня по базовому набору параметров
	~LEVEL();

	int getID(); // Возвращает ID уровня
	int getSeed(); // Возвращает зерно генерации уровня
	void setName(std::string NewName); // Устанавливает имя уровня
	std::string getName(); // Возвращает имя уровня
	size_t getSize(); // Возвращает размер сетки уровня
	std::vector<std::vector<tile>>& getGrid(); // Возвращает сетку уровня
	point_int getSpawn(); // Возвращает точку появления на уровне
	point_int getExit(); // Возвращает точку выхода с уровня
	
	bool DamageSubject(point_int sub, int dmg); // Возвращает результат действия. Наносит урон объекту уровня в указанном тайле 
};

class LEVEL_CAVE: public LEVEL
{
public:
	LEVEL_CAVE(std::string n, int size, CA_gen_settings cave);
	~LEVEL_CAVE();

private:

};

