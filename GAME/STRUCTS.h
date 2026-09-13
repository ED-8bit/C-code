#pragma once

struct tile {
	int floor;
	int subject;
	int air;
	float temp;
	int biome;

	tile(int f = 0, int s = 0, int a = 0, float t = 0, int b = 0) : floor(f), subject(s), air(a), temp(t), biome(b) {}
};
struct point_int {
	int x;
	int y;

	point_int(int x = 0, int y = 0) : x(x), y(y) {}
};
struct point_double {
	double x;
	double y;

	point_double(double x = 0.0, double y = 0.0) : x(x), y(y) {}
	point_double(point_int dot) : x(double(dot.x)), y(double(dot.y)) {}
};