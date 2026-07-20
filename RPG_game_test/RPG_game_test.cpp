#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
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
void seed_fill_CA(vector<vector<bool>>* game, int seed, int fill = 0)
{
	int i, j;
	int size = game->size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, 99);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			int res = dist(rng);
			if (res < fill)
				(*game)[i][j] = true;
		}
	}
	
}
/*void clean_holes_CA(vector<vector<bool>>* game)
{
	int i, j;
	int size = game->size();
	vector<vector<bool>> newGame = *game;

	for (i = 0; size > i; i++)
	{
		for (j = 0; size > j; j++)
		{
			if (i > 0 && i < size-1 && (*game)[i - 1][j] && (*game)[i + 1][j])
			{
				newGame[i][j] = true;
				continue;
			}
			if (j > 0 && j < size-1 && (*game)[i][j-1] && (*game)[i][j+1])
				newGame[i][j] = true;
		}
	}
	*game = newGame;
}*/
void clean_holes_CA(vector<vector<bool>>* game, int minsize)
{
	int i, j;
	int size = game->size();
	vector<vector<bool>> newGame = *game;

	
}
void iteration_CA(vector<vector<bool>>* game, int need)
{
	int i, j;
	int size = game->size();
	vector<vector<bool>> newGame = *game;
	for (i = 0; size > i; i++)
	{
		for (j = 0; size > j; j++)
		{
			int neighbors = 0;

			if (i > 0 && j > 0 && (*game)[i - 1][j - 1])
				neighbors++;
			
			if (i > 0 && (*game)[i - 1][j])
				neighbors++;
			
			if (i > 0 && j < size - 1 && (*game)[i - 1][j + 1])
				neighbors++;
		
			if (j > 0 && (*game)[i][j - 1])
				neighbors++;
			
			if (j < size - 1 && (*game)[i][j + 1])
				neighbors++;
			
			if (i < size - 1 && j > 0 && (*game)[i + 1][j - 1])
				neighbors++;
		
			if (i < size - 1 && (*game)[i + 1][j])
				neighbors++;
			
			if (i < size - 1 && j < size - 1 && (*game)[i + 1][j + 1])
				neighbors++;

			if (neighbors > need+1 || neighbors < need-1)
				newGame[i][j] = false;
			else if (neighbors == need || neighbors == need - 1)
				newGame[i][j] = true;
			
		}
	}
	*game = newGame;
}
void border_fill_CA(vector<vector<bool>>* game, int width = 1)
{
	int i, j, w;
	int size = game->size();
	for (w = 0; w < width; w++)
	{
		for (i = w; i < size - w; i++)
		{
			for (j = w; j < size - w; j++)
			{
				if ((i == w || i == size - w - 1) || (j == w || j == size - w - 1))
					(*game)[i][j] = true;
			}
		}
	}
}
/*void rand_fill_CA(vector<vector<bool>> *game, int fill = 0)
{
	int i, j;
	srand(time(0));
	for (i = 0; game->size() > i; i++)
	{
		for (j = 0; game->size() > j; j++)
		{
			int res = rand() % 100 + 1;
			if (res <= fill)
				(*game)[i][j] = true;
		}
	}
}*/
vector<vector<bool>> create_map_CA(int size, int iters, int seed = rand(), int fill = 50, int wall = 0, int clean = 0, int need = 3)
{
	int i;
	vector<vector<bool>> game(size, vector<bool>(size, false));
	seed_fill_CA(&game, seed, fill);
	for (i = 0; i < iters; i++)
		iteration_CA(&game, need);
	for (i = 0; i < clean; i++)
		clean_holes_CA(&game, 15);
	border_fill_CA(&game, wall);
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
	for (int i = 0; i < 5; i++)
	{
		int seed = rand();
		system("cls");
		//                                size, iters, seed, fill, wall, clean, need
		vector<vector<bool>> cave = create_map_CA(64, 6, seed, 77, 1, 0, 5);
		cout << "Level: Cave #" << i+1 << " \nSeed:  " << seed << '\n' << '\n';
		OUT_MAP(cave);
		Sleep(1500);
	}

	return 0;
}