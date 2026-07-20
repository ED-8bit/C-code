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
pair<int, int> spawn_away_from_walls(vector<vector<bool>>& game, int minDistance = 2) {
	int size = game.size();
	vector<pair<int, int>> candidates;

	
	for (int i = minDistance; i < size - minDistance; i++) {
		for (int j = minDistance; j < size - minDistance; j++) {
			if (!game[i][j]) {
				bool isClear = true;

				
				for (int di = -minDistance; di <= minDistance; di++) {
					for (int dj = -minDistance; dj <= minDistance; dj++) {
						if (i + di >= 0 && i + di < size &&
							j + dj >= 0 && j + dj < size &&
							game[i + di][j + dj]) {
							isClear = false;
							break;
						}
					}
					if (!isClear) break;
				}

				if (isClear) {
					candidates.push_back({ i, j });
				}
			}
		}
	}

	if (!candidates.empty()) {
		
		return candidates[0];
	}

	return { size / 2, size / 2 }; 
}
void fill_holes_CA(vector<vector<bool>>& game, int minzone = 0)
{
	int size = game.size();
	vector<vector<bool>> visited(size, vector<bool>(size, false));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!game[i][j] && !visited[i][j])
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
							!game[nx][ny] && !visited[nx][ny])
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
						game[x][y] = true;
					}
				}
			}
		}
	}
}
void seed_fill_CA(vector<vector<bool>>& game, int seed, int fill = 0)
{
	int size = game.size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, 99);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (dist(rng) < fill)
				game[i][j] = true;
		}
	}
	
}
void iteration_CA(vector<vector<bool>>& game, int need)
{
	int i, j;
	int size = game.size();
	vector<vector<bool>> newGame = game;
	for (i = 0; size > i; i++)
	{
		for (j = 0; size > j; j++)
		{
			int neighbors = 0;

			if (i > 0 && j > 0 && game[i - 1][j - 1])
				neighbors++;
			
			if (i > 0 && game[i - 1][j])
				neighbors++;
			
			if (i > 0 && j < size - 1 && game[i - 1][j + 1])
				neighbors++;
		
			if (j > 0 && game[i][j - 1])
				neighbors++;
			
			if (j < size - 1 && game[i][j + 1])
				neighbors++;
			
			if (i < size - 1 && j > 0 && game[i + 1][j - 1])
				neighbors++;
		
			if (i < size - 1 && game[i + 1][j])
				neighbors++;
			
			if (i < size - 1 && j < size - 1 && game[i + 1][j + 1])
				neighbors++;

			if (neighbors > need+1 || neighbors < need-1)
				newGame[i][j] = false;
			else if (neighbors == need || neighbors == need - 1)
				newGame[i][j] = true;
			
		}
	}
	game = newGame;
}
void border_fill_CA(vector<vector<bool>>& game, int wall = 0)
{
	int i, j, w;
	int size = game.size();
	for (w = 0; w < wall+1; w++)
	{
		for (i = w; i < size - w; i++)
		{
			for (j = w; j < size - w; j++)
			{
				if ((i == w || i == size - w - 1) || (j == w || j == size - w - 1))
					game[i][j] = true;
			}
		}
	}
}
vector<vector<bool>> create_map_CA(int size, int iters, int seed = rand(), int fill = 50, int wall = 0, int minzone = 0, int need = 3)
{
	int i;
	vector<vector<bool>> game(size, vector<bool>(size, false));
	seed_fill_CA(game, seed, fill);
	for (i = 0; i < iters; i++)
		iteration_CA(game, need);
	border_fill_CA(game, wall);
	fill_holes_CA(game, minzone);
	return game;
}
void OUT_MAP(vector<vector<bool>> game)
{
	int i, j;
	for (i = 0; game.size() > i; i++)
	{
		for (j = 0; game.size() > j; j++)
		{
			if (game[i][j])
				cout << "[]";
			if (!game[i][j])
				cout << "  ";
		}
		cout << '\n';
	}
}


int main() {
	system("chcp 1251");
	system("cls");
	srand(time(0));
	for (int i = 0; i < 1; i++)
	{
		system("cls");
		int seed = rand();
		//                                size, iters, seed, fill, wall, need
		vector<vector<bool>> cave = create_map_CA(128, 7, seed, 55, 1, 3, 5);
		cout << "Level: Cave #" << i+1 << " \nSeed:  " << seed << '\n' << '\n';
		OUT_MAP(cave);
		Sleep(2000);
	}

	return 0;
}