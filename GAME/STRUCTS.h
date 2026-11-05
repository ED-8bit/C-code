#pragma once
struct point_int {
	int x;
	int y;

	point_int(int x = 0, int y = 0) : x(x), y(y) {}

	bool operator==(point_int other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(point_int other) const {
		return !(*this == other);
	}

};
struct point_double {
	double x;
	double y;

	point_double(double x = 0.0, double y = 0.0) : x(x), y(y) {}
	point_double(point_int dot) : x(double(dot.x)), y(double(dot.y)) {}
};

struct CA_gen_settings {
	int seed; // Зерно
	int iterations = 7; // Количество итераций (повторений "жизненного цикла")
	int initial_population_percent = 75; // Процент начального заполнения сетки
	int required_neighbors = 5; // Идеальное число соседей
	int wall_level = 3; // Дополнительная толщина крайней стены
	int debris_destruction_level = 2; // Количество итераций уничтожения живых клеток вдали от живых соседей
	int area_minzone = 50; // Минимальная площадь свободных зон. (Меньшие заполняются)
	int aliasing_level = 1; // Количество итераций сглаживания углов
	int ore_richness_level = 2; // Уровень богатства рудой

	CA_gen_settings(int s, int iters = 7, int fill = 75, int need = 5, int w = 3, int d = 2, int minzone = 50, int smooth = 1, int ore = 2) :
		seed(s), iterations(iters), initial_population_percent(fill), required_neighbors(need),
		wall_level(w), debris_destruction_level(d), area_minzone(minzone), aliasing_level(smooth),
		ore_richness_level(ore) {
	}
};