#include "WORLD.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>

using namespace std;

bool onBorder(vector<vector<tile>>& game, point_int dot)
{
	int size = game.size();
	if (dot.x == 0 || dot.y == 0 || dot.x == size - 1 || dot.y == size - 1)
		return true;
	else
		return false;
}
bool outBorder(vector<vector<tile>>& game, point_int dot)
{
	int size = game.size();
	if (dot.x < 0 || dot.y < 0 || dot.x >= size || dot.y >= size)
		return true;
	else
		return false;
}

void seed_fill_CAVE(vector<vector<tile>>& game, int seed, int fill)
{
	int size = game.size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, 99);

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (dist(rng) < fill)
				game[x][y].subject = 1;
		}
	}

}
void iteration_CAVE(vector<vector<tile>>& game, int need)
{
	int x, y;
	int size = game.size();
	vector<vector<tile>> newGame = game;
	for (x = 0; size > x; x++)
	{
		for (y = 0; size > y; y++)
		{
			int neighbors = 0;

			if (x > 0 && y > 0 && game[x - 1][y - 1].subject)
				neighbors++;

			if (x > 0 && game[x - 1][y].subject)
				neighbors++;

			if (x > 0 && y < size - 1 && game[x - 1][y + 1].subject)
				neighbors++;

			if (y > 0 && game[x][y - 1].subject)
				neighbors++;

			if (y < size - 1 && game[x][y + 1].subject)
				neighbors++;

			if (x < size - 1 && y > 0 && game[x + 1][y - 1].subject)
				neighbors++;

			if (x < size - 1 && game[x + 1][y].subject)
				neighbors++;

			if (x < size - 1 && y < size - 1 && game[x + 1][y + 1].subject)
				neighbors++;

			if (neighbors > need + 1 || neighbors < need - 1)
				newGame[x][y].subject = 0;
			else if (neighbors == need || neighbors == need - 1)
				newGame[x][y].subject = 1;

		}
	}
	game = newGame;
}
void fill_holes_CAVE(vector<vector<tile>>& game, int minzone)
{
	int size = game.size();
	vector<vector<bool>> visited(size, vector<bool>(size, false));

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (!game[x][y].subject && !visited[x][y])
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
							!game[nx][ny].subject && !visited[nx][ny])
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
						game[x][y].subject = 1;
					}
				}
			}
		}
	}
}
void destroy_debris_CAVE(vector<vector<tile>>& game)
{
	int x, y, size = game.size();
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
					if (!game[ox][oy].subject && !game[nx][ny].subject)
					{
						game[x][y].subject = 0;
						break;
					}

				}
			}
		}
	}
}
void build_smoothing_CAVE(vector<vector<tile>>& game)
{
	int x, y, size = game.size();
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
					if (game[ox][oy].subject && game[nx][ny].subject)
					{
						game[x][y].subject = 1;
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
	int size = game.size();
	for (thickness = 0; thickness < wall; thickness++)
	{
		for (x = thickness; x < size - thickness; x++)
		{
			for (y = thickness; y < size - thickness; y++)
			{
				if ((x == thickness || x == size - thickness - 1) || (y == thickness || y == size - thickness - 1))
					game[x][y].subject = 2;
			}
		}
	}
}

point_int find_player_spawn(vector<vector<tile>>& game, int R, int seed)
{
	int size = game.size();
	mt19937 s(seed);
	unsigned int start = s();

	// Направление перебора зависит от остатка деления сида на 4
	int direction = start % 4;

	// Лямбда-функция для проверки, безопасна ли точка (нет ли стен в радиусе R)
	auto is_safe = [&](int x, int y) {
		if (game[x][y].subject != 0 || game[x][y].floor < 0) return false;

		for (int dx = -R; dx <= R; dx++) {
			for (int dy = -R; dy <= R; dy++) {
				// Если вышли за границы карты или встретили стену/объект
				if (x + dx < 0 || x + dx >= size || y + dy < 0 || y + dy >= size) return false;
				if (game[x + dx][y + dy].subject != 0) return false;
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
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	case 1:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	case 2:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	case 3:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return point_int(0, 0);
}
point_int find_LEVEL_escape(vector<vector<tile>>& game, int R, int seed)
{
	int size = game.size();
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
		if (game[x][y].subject != 0 || game[x][y].floor < 1) return false;

		for (int dx = -R; dx <= R; dx++) {
			for (int dy = -R; dy <= R; dy++) {
				// Если вышли за границы карты или встретили стену/объект
				if (x + dx < 0 || x + dx >= size || y + dy < 0 || y + dy >= size) return false;
				if (game[x + dx][y + dy].subject != 0) return false;
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
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	case 1:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	case 2:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	case 3:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point_int(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return point_int(0, 0);
}
point_int set_LEVEL_escape(vector<vector<tile>>& game, int seed)
{
	point_int ESC = find_LEVEL_escape(game, 1, seed);
	game[ESC.x][ESC.y].floor = 4;
	return ESC;
}
point_int set_player_spawn(vector<vector<tile>>& game, int seed)
{
	point_int SP = find_player_spawn(game, 1, seed);
	game[SP.x][SP.y].floor = 3;
	return SP;
}

void random_ore_spawn(vector<vector<tile>>& game, int seed, int fill)
{
	int size = game.size();
	mt19937 ore(seed);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (game[x][y].subject == 1)
			{
				if ((ore() % 100 + 1) <= fill)
				{
					game[x][y].subject = 3;
				}
			}
		}
	}

}
void random_ore_grow(vector<vector<tile>>& game, int seed)
{
	int size = game.size();
	int r;
	vector<vector<tile>> NewGame = game;
	mt19937 ore(seed);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if ((game[x][y].subject == 3) && (!onBorder(game, { x, y })))
			{
				do
				{
					r = ore() % 9;
					switch (r)
					{
					case 0:
					{
						if (game[x - 1][y].subject == 1)
							NewGame[x - 1][y].subject = 3;
						break;
					}
					case 1:
					{
						if (game[x + 1][y].subject == 1)
							NewGame[x + 1][y].subject = 3;
						break;
					}
					case 2:
					{
						if (game[x][y - 1].subject == 1)
							NewGame[x][y - 1].subject = 3;
						break;
					}
					case 3:
					{
						if (game[x][y + 1].subject == 1)
							NewGame[x][y + 1].subject = 3;
						break;
					}
					case 4:
					{
						if (game[x - 1][y + 1].subject == 1)
							NewGame[x - 1][y + 1].subject = 3;
						break;
					}
					case 5:
					{
						if (game[x + 1][y - 1].subject == 1)
							NewGame[x + 1][y - 1].subject = 3;
						break;
					}
					case 6:
					{
						if (game[x + 1][y + 1].subject == 1)
							NewGame[x + 1][y + 1].subject = 3;
						break;
					}
					case 7:
					{
						if (game[x - 1][y - 1].subject == 1)
							NewGame[x - 1][y - 1].subject = 3;
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
