#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <queue>
#include <utility> 
using namespace std;

string tileset[3][8] = {
//    0     1     2     3     4     5     6     7
	{"  ", "`.", "LV", "SP", "EN", "PL", "  ", "  "},   // Пол (floor)
	{"  ", "[]", "WA", "OR", "  ", "  ", "  ", "  "},   // Стены/объекты (subject)
	{"  ", "@@", "  ", "  ", "  ", "  ", "  ", "  "},   // Воздух
};
struct tile {
	int floor;
	int subject;
	int air;
	float temp;
	int biome;

	tile(int f = 0, int s = 0, int a = 0, double t = 0, int b = 0): floor(f), subject(s), air(a), temp(t), biome(b){}
};
struct point {
	int x;
	int y;

	point(int x, int y) : x(x), y(y) {}
};
int ent = 0;
class Entity
{
protected:
	int id;
	vector<vector<tile>>& map;
	point local;
	string name;
	float weight;
	int age;
	
public:
	Entity(vector<vector<tile>>& m, point l = { 0, 0 }, string n = " ", float w = 0, int a = 0) : map(m), local(l), name(n), weight(w), age(a) { id = ++ent; }
	
	virtual int getID() const { return id; }
	virtual string getName() const { return name; }
	virtual point getPosition() const { return local; }
	virtual float getWeight() const { return weight; }
	virtual int getAge() const { return age; }

	void setName(const string& newName) { name = newName; }
	void setPosition(int x, int y) {
		if (x >= 0 && x < (int)map.size() && y >= 0 && y < (int)map.size()) {
			local.x = x;
			local.y = y;
		}
	}

	virtual void printInfo() const {
		cout << "📊 " << name << " | Позиция: (" << local.x << ", " << local.y << ")" << endl;
		cout << "   Вес: " << weight << " | Возраст: " << age << endl;
	}

	virtual ~Entity() {}

};

enum Direction { north, south, west, east };

class Character : public Entity
{
protected:

	float HP = 10;
	float DMG = 0;
public:
	Character(vector<vector<tile>>& map, point local, string name, float weight, int age): Entity(map, local, name, weight, age) {}

	
	void move(Direction dir) {
		int size = map.size();
		switch (dir) {
		case north: if (local.y < size - 1) local.y++; break;
		case south: if (local.y > 0) local.y--; break;
		case west:  if (local.x < size - 1) local.x++; break;
		case east:  if (local.x > 0) local.x--; break;
		}
	}
	void take_damage(float dmg)
	{
		if (dmg < 0)
			return;
		HP -= dmg;
		if (HP < 0)
			HP = 0;
	}
	void give_damage(Character& enemy)
	{
		if (DMG <= 0) return;
		enemy.take_damage(DMG);
	}
	bool isAlive() const
	{
		return HP > 0;
	}

	virtual ~Character(){}
};










void seed_fill_CAVE(vector<vector<tile>>& game, int seed, int fill = 0)
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
void iteration_CAVE(vector<vector<tile>>& game, int need)
{
	int i, j;
	int size = game.size();
	vector<vector<tile>> newGame = game;
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
void fill_holes_CAVE(vector<vector<tile>>& game, int minzone = 0)
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
void destroy_debris_CAVE(vector<vector<tile>>& game)
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
void build_smoothing_CAVE(vector<vector<tile>>& game)
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
void border_fill_CAVE(vector<vector<tile>>& game, int wall = 0)
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

point find_player_spawn(vector<vector<tile>>& game, int R, int seed)
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
				if (is_safe(x, y)) return point(x, y);
			}
		}
		break;

	case 1: // Снизу вверх, слева направо
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return point(x, y);
			}
		}
		break;

	case 2: // Сверху вниз, справа налево
		for (int x = R; x < size - R; x++) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point(x, y);
			}
		}
		break;

	case 3: // Снизу вверх, справа налево
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point(x, y);
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
				if (game[x][y].subject == 0) return point(x, y);
		break;
	case 1:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	case 2:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	case 3:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return point(0, 0);
}
void set_player_spawn(vector<vector<tile>>& game, int seed)
{
	point SP = find_player_spawn(game, 1, seed);
	game[SP.x][SP.y].floor = 3;
}

void random_ore_spawn(vector<vector<tile>>& game, int seed, int fill)
{
	int size = game.size();
	mt19937 ore(seed);
	for (size_t x = 0; x < size; x++)
	{
		for (size_t y = 0; y < size; y++)
		{
			if (game[x][y].subject == 1) 
				if((ore() % 100 + 1) <= fill)
			{
				game[x][y].subject = 3;
			}
		}
	}
	
}

vector<vector<tile>> create_map_CAVE(int size, int iters, int seed = rand(), int fill = 50, int wall = 0, int minzone = 0, int destr = 1, int smooth = 1, int need = 3, int ore = 0)
{
	int i;
	vector<vector<tile>> game(size, vector<tile>(size, tile(1)));
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
	random_ore_spawn(game, seed, ore);
	return game;
}

void OUT_MAP(vector<vector<tile>> game)
{
	size_t i, j;
	int size = game.size();
	for (i = 0; size > i; i++)
	{
		for (j = 0; size > j; j++)
		{
			if ((!game[i][j].subject) && (!game[i][j].air))
				cout << tileset[0][game[i][j].floor];
			else if (game[i][j].subject)
				cout << tileset[1][game[i][j].subject];
			else if (game[i][j].air)
				cout << tileset[2][game[i][j].air];
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
	//                                          size, iters, seed, fill, wall, minzone, debris, smooth, need, ore
	vector<vector<tile>> cave = create_map_CAVE(  96,     6, seed,   46,    4,      75,      4,      2,    5,   2);
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