#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <queue>
#include <utility> 
using namespace std;

string tileset[2][8] = {
//    0     1     2     3     4     5     6     7
	{"  ", "`.", "^,", "SP", "EN", "  ", "  ", "  "},  // Пол (floor)
	{"  ", "@@", "[]", "OR", "  ", "  ", "  ", "  "}   // Стены/объекты (subject)
};

struct tilemap {
	int floor;
	int subject;
	int air;
	float temp;
	int biome;

	tilemap(int f = 0, int s = 0, int a = 0, double t = 0, int b = 0): floor(f), subject(s), air(a), temp(t), biome(b){}
};

struct coords {
	int x;
	int y;

	coords(int x, int y) : x(x), y(y) {}
};


void seed_fill_CAVE(vector<vector<tilemap>>& game, int seed, int fill = 0)
{
	int size = game.size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, 99);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (dist(rng) < fill)
				game[i][j].subject = 1;
		}
	}

}
void iteration_CAVE(vector<vector<tilemap>>& game, int need)
{
	int i, j;
	int size = game.size();
	vector<vector<tilemap>> newGame = game;
	for (i = 0; size > i; i++)
	{
		for (j = 0; size > j; j++)
		{
			int neighbors = 0;

			if (i > 0 && j > 0 && game[i - 1][j - 1].subject)
				neighbors++;

			if (i > 0 && game[i - 1][j].subject)
				neighbors++;

			if (i > 0 && j < size - 1 && game[i - 1][j + 1].subject)
				neighbors++;

			if (j > 0 && game[i][j - 1].subject)
				neighbors++;

			if (j < size - 1 && game[i][j + 1].subject)
				neighbors++;

			if (i < size - 1 && j > 0 && game[i + 1][j - 1].subject)
				neighbors++;

			if (i < size - 1 && game[i + 1][j].subject)
				neighbors++;

			if (i < size - 1 && j < size - 1 && game[i + 1][j + 1].subject)
				neighbors++;

			if (neighbors > need + 1 || neighbors < need - 1)
				newGame[i][j].subject = 0;
			else if (neighbors == need || neighbors == need - 1)
				newGame[i][j].subject = 1;

		}
	}
	game = newGame;
}
void fill_holes_CAVE(vector<vector<tilemap>>& game, int minzone = 0)
{
	int size = game.size();
	vector<vector<bool>> visited(size, vector<bool>(size, false));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!game[i][j].subject && !visited[i][j])
			{
				// Find connected component
				vector<pair<int, int>> component;
				queue<pair<int, int>> q;
				q.push({ i, j });
				visited[i][j] = true;
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

				// Fill if it's a hole (doesn't touch border) and small enough
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
void destroy_debris_CAVE(vector<vector<tilemap>>& game)
{
	int i, j, size = game.size();
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			bool onBorder = true;
			if ((i != 0 && j != 0) && (i + 1 != size && j + 1 != size))
			{
				onBorder = false;
			}
			if (!onBorder)
			{
				int dx[] = { -1, 0, 1, 1, };
				int dy[] = { -1, -1, -1, 0, };

				for (int d = 0; d < 4; d++)
				{
					int x = i + dx[d];
					int y = j + dy[d];
					int nx = i - dx[d];
					int ny = j - dy[d];
					if (!game[x][y].subject && !game[nx][ny].subject)
						game[i][j].subject = 0;
				}
			}
		}
	}
}
void build_smoothing_CAVE(vector<vector<tilemap>>& game)
{
	int i, j, size = game.size();
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			bool onBorder = true;
			if ((i != 0 && j != 0) && (i + 1 != size && j + 1 != size))
			{
				onBorder = false;
			}
			if (!onBorder)
			{
				int dx[] = { -1, 0, 1, 1, };
				int dy[] = { -1, -1, -1, 0, };

				for (int d = 0; d < 4; d++)
				{
					int x = i + dx[d];
					int y = j + dy[d];
					int nx = i - dx[d];
					int ny = j - dy[d];
					if (game[x][y].subject && game[nx][ny].subject)
						game[i][j].subject = 1;
				}
			}
		}
	}
}
void border_fill_CAVE(vector<vector<tilemap>>& game, int wall = 0)
{
	int i, j, w;
	int size = game.size();
	for (w = 0; w < wall; w++)
	{
		for (i = w; i < size - w; i++)
		{
			for (j = w; j < size - w; j++)
			{
				if ((i == w || i == size - w - 1) || (j == w || j == size - w - 1))
					game[i][j].subject = 2;
			}
		}
	}
}

coords find_player_spawn(vector<vector<tilemap>>& game, int R, int seed)
{
	int size = game.size();
	mt19937 s(seed);
	unsigned int start = s();

	// Направление перебора зависит от остатка деления сида на 4
	int direction = start % 4;

	// Лямбда-функция для проверки, безопасна ли точка (нет ли стен в радиусе R)
	auto is_safe = [&](int x, int y) {
		if (game[x][y].subject != 0) return false;

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
				if (is_safe(x, y)) return coords(x, y);
			}
		}
		break;

	case 1: // Снизу вверх, слева направо
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return coords(x, y);
			}
		}
		break;

	case 2: // Сверху вниз, справа налево
		for (int x = R; x < size - R; x++) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return coords(x, y);
			}
		}
		break;

	case 3: // Снизу вверх, справа налево
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return coords(x, y);
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
				if (game[x][y].subject == 0) return coords(x, y);
		break;
	case 1:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].subject == 0) return coords(x, y);
		break;
	case 2:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return coords(x, y);
		break;
	case 3:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return coords(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return coords(0, 0);
}
void set_player_spawn(vector<vector<tilemap>>& game, int seed)
{
	coords SP = find_player_spawn(game, 1, seed);
	game[SP.x][SP.y].floor = 3;
}

void random_ore_spawn(vector<vector<tilemap>>& game, int seed, int fill)
{
	int size = game.size();
	mt19937 ore(seed);
	for (size_t x = 0; x < size; x++)
	{
		for (size_t y = 0; y < size; y++)
		{
			if (game[x][y].subject == 1) 
				if(ore() % 100 + 1 <= fill)
			{
				game[x][y].subject = 3;
			}
		}
	}
	
}

vector<vector<tilemap>> create_map_CAVE(int size, int iters, int seed = rand(), int fill = 50, int wall = 0, int minzone = 0, int destr = 1, int smooth = 1, int need = 3)
{
	int i;
	vector<vector<tilemap>> game(size, vector<tilemap>(size, tilemap(1,0,0)));
	seed_fill_CAVE(game, seed, fill);
	for (i = 0; i < iters; i++)
	{
		iteration_CAVE(game, need);
	}
	border_fill_CAVE(game, wall);
	fill_holes_CAVE(game, minzone);
	for (i = 0; i < destr; i++)
	{
		destroy_debris_CAVE(game);
	}
	for (i = 0; i < smooth; i++)
	{
		build_smoothing_CAVE(game);
	}
	random_ore_spawn(game, seed, 1);
	return game;
}

void OUT_MAP(vector<vector<tilemap>> game)
{
	size_t i, j;
	int size = game.size();
	for (i = 0; size > i; i++)
	{
		for (j = 0; size > j; j++)
		{
			if (!game[i][j].subject)
				cout << tileset[0][game[i][j].floor];
			else
				cout << tileset[1][game[i][j].subject];
		}
		cout << '\n';
	}
}
void CAVE_gen()
{
	int seed;
	cout << "Enter seed (0 = random): "; cin >> seed;
	if (seed == 0)
		seed = rand();
	system("cls");
	//                                size, iters, seed, fill, wall, minzone, debris, smooth need
	vector<vector<tilemap>> cave = create_map_CAVE(96, 6, seed, 46, 4, 100, 4, 2, 5);
	set_player_spawn(cave, seed);
	cout << "Level: Cave" << " \nSeed: " << seed << '\n' << '\n';
	OUT_MAP(cave);
	system("pause");
}

void OUT_MENU()
{
	cout << "**  MENU  **\n";
	cout << "1. CAVES\n";
	cout << "0. EXIT\n\n";
	cout << "Choice: ";
}

int main() {
	system("chcp 1251");
	system("cls");
	srand(time(0));
	size_t choose;
	do
	{
		system("cls");
		OUT_MENU();
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			system("cls");
			CAVE_gen();
			break;
		}
		case 0:
			break;
		default:
			cout << "ERROR";
			Sleep(1000);
			break;
		}
	} while (choose != 0);
	

	return 0;
}