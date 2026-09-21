#include "WORLD.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>

using namespace std;

bool onBorder(vector<vector<tile>>& game, point_int dot)
{
	size_t size = game.size();
	if (dot.x == 0 || dot.y == 0 || dot.x == size - 1 || dot.y == size - 1)
		return true;
	else
		return false;
}
bool outBorder(vector<vector<tile>>& game, point_int dot)
{
	size_t size = game.size();
	if (dot.x < 0 || dot.y < 0 || dot.x >= size || dot.y >= size)
		return true;
	else
		return false;
}

void seed_fill_CAVE(vector<vector<tile>>& game, int seed, int fill)
{
	size_t size = game.size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, 99);

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (dist(rng) < fill)
				game[x][y].getSubject().setType(S_stone);
		}
	}

}
void iteration_CAVE(vector<vector<tile>>& game, int need)
{
	int x, y;
	size_t size = game.size();
	vector<vector<tile>> newGame = game;
	for (x = 0; size > x; x++)
	{
		for (y = 0; size > y; y++)
		{
			int neighbors = 0;

			if (x > 0 && y > 0 && game[x - 1][y - 1].getSubject().getType())
				neighbors++;

			if (x > 0 && game[x - 1][y].getSubject().getType())
				neighbors++;

			if (x > 0 && y < size - 1 && game[x - 1][y + 1].getSubject().getType())
				neighbors++;

			if (y > 0 && game[x][y - 1].getSubject().getType())
				neighbors++;

			if (y < size - 1 && game[x][y + 1].getSubject().getType())
				neighbors++;

			if (x < size - 1 && y > 0 && game[x + 1][y - 1].getSubject().getType())
				neighbors++;

			if (x < size - 1 && game[x + 1][y].getSubject().getType())
				neighbors++;

			if (x < size - 1 && y < size - 1 && game[x + 1][y + 1].getSubject().getType())
				neighbors++;

			if (neighbors > need + 1 || neighbors < need - 1)
				newGame[x][y].getSubject().setType(S_none);
			else if (neighbors == need || neighbors == need - 1)
				newGame[x][y].getSubject().setType(S_stone);

		}
	}
	game = newGame;
}
void fill_holes_CAVE(vector<vector<tile>>& game, int minzone)
{
	size_t size = game.size();
	vector<vector<bool>> visited(size, vector<bool>(size, false));

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (!game[x][y].getSubject().getType() && !visited[x][y])
			{
				// Find connected component
				vector<pair<int, int>> component;
				queue<pair<int, int>> q;
				q.push({ x, y });
				visited[x][y] = true;
				bool touchesBorder = false;

				while (!q.empty())
				{
					auto [x, y] = q.front();
					q.pop();
					component.push_back({ x, y });

					// Check if component touches border
					if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
						touchesBorder = true;

					int dx[] = { -1, 1, 0, 0 };
					int dy[] = { 0, 0, -1, 1 };

					for (int d = 0; d < 4; d++)
					{
						int nx = x + dx[d];
						int ny = y + dy[d];

						if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
							!game[nx][ny].getSubject().getType() && !visited[nx][ny])
						{
							visited[nx][ny] = true;
							q.push({ nx, ny });
						}
					}
				}

				if (!touchesBorder && component.size() <= minzone)
				{
					for (auto [x, y] : component)
					{
						game[x][y].getSubject().setType(subs::S_stone);
					}
				}
			}
		}
	}
}
void destroy_debris_CAVE(vector<vector<tile>>& game)
{
	int x, y;
	size_t size = game.size();
	for (x = 0; x < size; x++)
	{
		for (y = 0; y < size; y++)
		{
			if (!onBorder(game, { x, y }))
			{
				int dx[4] = { -1, 0, 1, 1 };
				int dy[4] = { -1, -1, -1, 0 };

				for (int d = 0; d < 4; d++)
				{
					int ox = x + dx[d];
					int oy = y + dy[d];
					int nx = x - dx[d];
					int ny = y - dy[d];
					if (!game[ox][oy].getSubject().getType() && !game[nx][ny].getSubject().getType())
					{
						game[x][y].getSubject().setType(subs::S_none);
						break;
					}

				}
			}
		}
	}
}
void build_smoothing_CAVE(vector<vector<tile>>& game)
{
	int x, y;
	size_t size = game.size();
	for (x = 0; x < size; x++)
	{
		for (y = 0; y < size; y++)
		{
			if (!onBorder(game, { x, y }))
			{
				int dx[4] = { -1, 0, 1, 1 };
				int dy[4] = { -1, -1, -1, 0 };

				for (int d = 0; d < 4; d++)
				{
					int ox = x + dx[d];
					int oy = y + dy[d];
					int nx = x - dx[d];
					int ny = y - dy[d];
					if (game[ox][oy].getSubject().getType() && game[nx][ny].getSubject().getType())
					{
						game[x][y].getSubject().setType(subs::S_stone);
						break;
					}

				}
			}
		}
	}
}
void border_fill_CAVE(vector<vector<tile>>& game, int wall)
{
	int x, y, thickness;
	size_t size = game.size();
	for (thickness = 0; thickness < wall; thickness++)
	{
		for (x = thickness; x < size - thickness; x++)
		{
			for (y = thickness; y < size - thickness; y++)
			{
				if ((x == thickness || x == size - thickness - 1) || (y == thickness || y == size - thickness - 1))
					game[x][y].getSubject().setType(S_endstone);
			}
		}
	}
}

point_int find_player_spawn(vector<vector<tile>>& game, int R, int seed)
{
	size_t size = game.size();
	mt19937 s(seed);
	unsigned int start = s();

	// Направление перебора зависит от остатка деления сида на 4
	int direction = start % 4;

	// Лямбда-функция для проверки, безопасна ли точка (нет ли стен в радиусе R)
	auto is_safe = [&](int x, int y) {
		if (game[x][y].getSubject().getType() || game[x][y].getFloor().getType() == F_none) return false;

		for (int dx = -R; dx <= R; dx++) {
			for (int dy = -R; dy <= R; dy++) {
				// Если вышли за границы карты или встретили стену/объект
				if (x + dx < 0 || x + dx >= size || y + dy < 0 || y + dy >= size) return false;
				if (game[x + dx][y + dy].getSubject().getType()) return false;
			}
		}
		return true;
		};

	switch (direction)
	{
	case 0: // Сверху вниз, слева направо (стандартный порядок)
		for (int x = R; x < size - R; x++) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;

	case 1: // Снизу вверх, слева направо
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;

	case 2: // Сверху вниз, справа налево
		for (int x = R; x < size - R; x++) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;

	case 3: // Снизу вверх, справа налево
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;
	}

	// Резервный план: если с учетом радиуса R ничего не нашли,
	// ищем самую первую вообще пустую клетку (без учета радиуса безопасности)
	// в том же направлении, которое определил сид
	switch (direction)
	{
	case 0:
		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	case 1:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	case 2:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	case 3:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return point_int(0, 0);
}
point_int find_LEVEL_escape(vector<vector<tile>>& game, int R, int seed)
{
	size_t size = game.size();
	mt19937 s(seed);
	unsigned int start = s();

	// Направление перебора зависит от остатка деления сида на 4
	int direction = (start % 4 + 1);
	if (direction == 3 || direction == 4)
	{
		direction -= 2;
	}

	// Лямбда-функция для проверки, безопасна ли точка (нет ли стен в радиусе R)
	auto is_safe = [&](int x, int y) {
		if (game[x][y].getSubject().getType() || game[x][y].getFloor().getType() == F_none) return false;

		for (int dx = -R; dx <= R; dx++) {
			for (int dy = -R; dy <= R; dy++) {
				// Если вышли за границы карты или встретили стену/объект
				if (x + dx < 0 || x + dx >= size || y + dy < 0 || y + dy >= size) return false;
				if (game[x + dx][y + dy].getSubject().getType()) return false;
			}
		}
		return true;
		};

	switch (direction)
	{
	case 0: // Сверху вниз, слева направо (стандартный порядок)
		for (int x = R; x < size - R; x++) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;

	case 1: // Снизу вверх, слева направо
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;

	case 2: // Сверху вниз, справа налево
		for (int x = R; x < size - R; x++) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;

	case 3: // Снизу вверх, справа налево
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point_int(x, y);
			}
		}
		break;
	}

	// Резервный план: если с учетом радиуса R ничего не нашли,
	// ищем самую первую вообще пустую клетку (без учета радиуса безопасности)
	// в том же направлении, которое определил сид
	switch (direction)
	{
	case 0:
		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	case 1:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	case 2:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	case 3:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].getSubject().getType() == S_none) return point_int(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return point_int(0, 0);
}
point_int set_LEVEL_escape(vector<vector<tile>>& game, int seed)
{
	point_int ESC = find_LEVEL_escape(game, 1, seed);
	game[ESC.x][ESC.y].getFloor().setType(F_stone_exit);
	return ESC;
}
point_int set_player_spawn(vector<vector<tile>>& game, int seed)
{
	point_int SP = find_player_spawn(game, 1, seed);
	game[SP.x][SP.y].getFloor().setType(F_stone_spawn);
	return SP;
}

void random_ore_spawn(vector<vector<tile>>& game, int seed, int fill)
{
	size_t size = game.size();
	mt19937 ore(seed);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (game[x][y].getSubject().getType() == S_stone)
			{
				if ((ore() % 100 + 1) < fill)
				{
					game[x][y].getSubject().setType(subs::S_ore);
				}
			}
		}
	}

}
void random_ore_grow(vector<vector<tile>>& game, int seed)
{
	size_t size = game.size();
	int r;
	vector<vector<tile>> NewGame = game;
	mt19937 ore(seed);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if ((game[x][y].getSubject().getType() == subs::S_ore) && (!onBorder(game, { x, y })))
			{
				do
				{
					r = ore() % 9;
					switch (r)
					{
					case 0:
					{
						if (game[x - 1][y].getSubject().getType() == S_stone)
							NewGame[x - 1][y].getSubject().setType(subs::S_ore);
						break;
					}
					case 1:
					{
						if (game[x + 1][y].getSubject().getType() == S_stone)
							NewGame[x + 1][y].getSubject().setType(subs::S_ore);
						break;
					}
					case 2:
					{
						if (game[x][y - 1].getSubject().getType() == S_stone)
							NewGame[x][y - 1].getSubject().setType(subs::S_ore);
						break;
					}
					case 3:
					{
						if (game[x][y + 1].getSubject().getType() == S_stone)
							NewGame[x][y + 1].getSubject().setType(subs::S_ore);
						break;
					}
					case 4:
					{
						if (game[x - 1][y + 1].getSubject().getType() == S_stone)
							NewGame[x - 1][y + 1].getSubject().setType(subs::S_ore);
						break;
					}
					case 5:
					{
						if (game[x + 1][y - 1].getSubject().getType() == S_stone)
							NewGame[x + 1][y - 1].getSubject().setType(subs::S_ore);
						break;
					}
					case 6:
					{
						if (game[x + 1][y + 1].getSubject().getType() == S_stone)
							NewGame[x + 1][y + 1].getSubject().setType(subs::S_ore);
						break;
					}
					case 7:
					{
						if (game[x - 1][y - 1].getSubject().getType() == S_stone)
							NewGame[x - 1][y - 1].getSubject().setType(subs::S_ore);
						break;
					}
					default:
						break;
					}
				} while (r < 4);


			}
		}
	}
	game = NewGame;
}
void set_ore(vector<vector<tile>>& game, int seed, int level, bool grow)
{
	random_ore_spawn(game, seed, level);
	if (grow)
		random_ore_grow(game, seed);
}

SUBJECT::SUBJECT(){}
SUBJECT::SUBJECT(subs t): type(t)
{
	CalcToughness();
}
SUBJECT::~SUBJECT(){}

void SUBJECT::CalcToughness() {
	switch (type)
	{
	case S_stone:
		toughness = 300;
		break;
	case S_ore:
		toughness = 450;
		break;
	case S_endstone:
		toughness = -1;
		break;
	}
}

FLOOR::FLOOR(){}
FLOOR::FLOOR(floors t): type(t){}
FLOOR::~FLOOR(){}

tile::tile(subs s, floors f): subject(s), floor(f) {}
tile::~tile() {}

LEVEL::LEVEL(std::string n, level_type t, int seed, int size) : Name(n), Type(t), Seed(seed)
{
	ID = ++MAPs;
	Grid.resize(size, vector<tile>(size, tile(subs::S_none, floors::F_stone)));
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
LEVEL::~LEVEL()
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

bool LEVEL::destroy_sub(point_int sub)
{
	if (!outBorder(Grid, sub) && Grid[sub.x][sub.y].getSubject().getType() != S_endstone)
	{
		Grid[sub.x][sub.y].getSubject().setType(subs::S_none);
		return true;
	}
	else
	{
		std::cout << "cant break " << sub.x << ',' << sub.y << '\n';
		return false;
	}

}

