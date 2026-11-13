#pragma once
#include <vector>
#include <string>
#include <memory>
#include "STRUCTS.h"
#include "OBJECTS.h"
#include "GENERATORS.h"
extern int MAPs;

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
class LEVEL_CAVE: public LEVEL, public CA_GEN
{
public:
	LEVEL_CAVE(std::string n, int size, CA_gen_settings cave);
	~LEVEL_CAVE();

private:

};

