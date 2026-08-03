#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <queue>
#include <utility> 
using namespace std;
//
//class Entity {
//private:
//    string name;
//    double strength;
//    double weight;
//    double health;
//    double beat;
//public:
//    double getBeat() const { return beat; }
//
//    Entity(string n, double s, double w) : name(n), strength(s), weight(w), health(weight*strength), beat(strength*weight/10) {
//        cout << "Created Entity " << "'" << name << "'" << " with:\n" << health << " HP\n" << beat << " DP\n";
//    }
//
//    void take_damage(Entity* beater, double beat) {
//        health -= beat;
//        cout << "Entity " << "'" << name << "'" << "take " << beat << " damage " << "from " << &beater->name  << '\n' << "Entity HP -> " << health;
//    }
//
//    ~Entity() {
//        cout << "Entity " << "'" << name << "'" << " deleted";
//    }
//};
//
//int main() {
//    system("chcp 1251");
//    Entity p1("player1", 10, 65);
//    Entity p2("player2", 10, 75);
//    system("pause");
//    p1.take_damage(&p2, &p2->getBeat());
//    
//}

string tileset[2][8] = {
	// Индексы: 0    1    2    3    4    5    6    7
	{"  ", "`.", "^,", "YY", "NN", "  ", "  ", "  "},  // Пол (floor)
	{"  ", "@@", "[]", "  ", "  ", "  ", "  ", "  "}   // Стены/объекты (subject)
};

struct tilemap {
	int floor;
	int subject;
	int biome;

	tilemap(int f = 0, int s = 0, int b = 0): floor(f), subject(s), biome(b){}
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

coords find_player_spawn(vector<vector<tilemap>>& game, int minrange, int seed)
{
	int size = game.size();
	mt19937 s(seed);
	int start = s();
	switch (start % 4)
	{
	case 3:
		for (size_t x = 0; x < size; x++)
		{
			for (size_t y = 0; y < size; y++)
			{

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
	return game;
}

bool can_set_house_VILLAGE(vector<vector<tilemap>>& game, int x, int y, int width, int height)
{
	int size = game.size();
	if (x + width > size || y + height > size)
		return false;
	else
		return true;
}
void seed_set_VILLAGE(vector<vector<tilemap>>& game, int seed)
{
	int size = game.size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, size*size);
	int M =  dist(rng);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i + j * size != 3002)
				game[i][j].floor = 2;
			else
			{
				if (can_set_house_VILLAGE(game, i, j, 7, 5))
					game[i][j].floor = 3; // YY
				else
					game[i][j].floor = 4; // NN
			}
				
		}
	}
	


}
vector<vector<tilemap>> create_map_VILLAGE(int seed, int size)
{
	vector<vector<tilemap>> game(size, vector<tilemap>(size, tilemap(2, 0, 1)));
	seed_set_VILLAGE(game, seed);
	return game;
}

void OUT_MAP(vector<vector<tilemap>> game)
{
	size_t i, j;
	for (i = 0; game.size() > i; i++)
	{
		for (j = 0; game.size() > j; j++)
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
	vector<vector<tilemap>> cave = create_map_CAVE(64, 6, seed, 47, 3, 100, 4, 3, 5);
	cout << "Level: Cave" << " \nSeed: " << seed << '\n' << '\n';
	OUT_MAP(cave);
	system("pause");
}
void VILLAGE_gen()
{
	int seed;
	cout << "Enter seed (0 = random): "; cin >> seed;
	if (seed == 0)
		seed = rand();
	system("cls");
	vector<vector<tilemap>> village = create_map_VILLAGE(seed, 64);
	cout << "Level: Village" << " \nSeed: " << seed << '\n' << '\n';
	OUT_MAP(village);
	system("pause");

}
void DUNGEON_gen()
{
	int seed;
	cout << "Enter seed (0 = random): "; cin >> seed;
	if (seed == 0)
		seed = rand();
	system("cls");

}
void CASTLE_gen()
{
	int seed;
	cout << "Enter seed (0 = random): "; cin >> seed;
	if (seed == 0)
		seed = rand();
	system("cls");

}
void OUT_MENU()
{
	cout << "**  MENU  **\n";
	cout << "1. CAVES_gen\n";
	cout << "2. VILLAGE_gen\n";
	cout << "3. DUNGEON_gen\n";
	cout << "4. CASTLE_gen\n";
	cout << "0. EXIT\n\n";
	cout << "Choice: ";
}

int main() {
	system("chcp 1251");
	system("cls");
	srand(time(0));
	int choose;
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
		case 2:
		{
			system("cls");
			VILLAGE_gen();
			break;
		}
			
		case 3:
		{
			system("cls");
			DUNGEON_gen();
			break;
		}
		case 4:
		{
			system("cls");
			CASTLE_gen();
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