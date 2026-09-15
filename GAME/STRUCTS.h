#pragma once


struct Tile {
	int floor;
	int subject;

	Tile(int f = 0, int s = 0) : floor(f), subject(s){}
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