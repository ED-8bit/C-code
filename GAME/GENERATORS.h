#pragma once
#include "STRUCTS.h"
#include <vector>
#include "WORLD.h"

class CA_GEN
{
protected:
	size_t Size;
	int Seed;
	std::vector<std::vector<tile>>& GEN_Grid;

	bool onBorder(point_int Dot); // Возвращает True если точка на краю сетки, иначе - False
	bool outBorder(point_int Dot); // Возвращает True, если точка за пределами сетки, иначе - False
	bool isPointSafe(point_int Dot, int R); // Проверка безопасности точки на растоянии R в 4 сторонах

	void GridInit(); // Инициализация сетки (выставление полов)
	void FillBySeed(int Percent = 50); // Заполнение сетки по зерну нужным процентом "живых" клеток
	void Iteration(int Requiered); // Запуск итерации клеточного автомата в заданной сетке по упрощенному правилу
	void DeleteSmallAreas(int Minzone); // Заполнение зон с площадью меньше заданной
	void DestroyDebris(); // Уничтожение "живых" клеток без соседей
	void Antialiasing(); // Создание "живых" клеток с соседями (Сглаживание рельефа)
	void WallExpansion(int Additional = 0); // Установка и наращивание слоев стены для сетки
	point_int SetSpawn(int Radius); // Возвращает точку входа на уровень и заменяет этот тайл в сетке на соответствующий
	point_int SetExit(int Radius); // Возвращает точку выхода с уровня и заменяет этот тайл в сетке на соответствующий

	void SetOre(int BaseRichness, bool Growing); // Распределяет "богатые" клетки, среди "живых" 

public:
	CA_GEN(std::vector<std::vector<tile>>& GG, int s);
	~CA_GEN();
	

};

