#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

struct tile {
	int floor;
	int subject;
	int air;
	float temp;
	int biome;

	tile(int f = 0, int s = 0, int a = 0, float t = 0, int b = 0) : floor(f), subject(s), air(a), temp(t), biome(b) {}
};
struct point {
	int x;
	int y;

	point(int x = 0, int y = 0) : x(x), y(y) {}
};
bool onBorder(vector<vector<tile>>& game, point dot)
{
	int size = game.size();
	if (dot.x == 0 || dot.y == 0 || dot.x == size - 1 || dot.y == size - 1)
		return true;
	else
		return false;
}
bool outBorder(vector<vector<tile>>& game, point dot)
{
	int size = game.size();
	if (dot.x < 0 || dot.y < 0 || dot.x >= size || dot.y >= size)
		return true;
	else
		return false;
}

void seed_fill_CAVE(vector<vector<tile>>& game, int seed, int fill = 0)
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
void fill_holes_CAVE(vector<vector<tile>>& game, int minzone = 0)
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
			if (!onBorder(game, {x, y}))
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
void border_fill_CAVE(vector<vector<tile>>& game, int wall = 0)
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
point find_LEVEL_escape(vector<vector<tile>>& game, int R, int seed)
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

	case 0: // Снизу вверх, справа налево
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point(x, y);
			}
		}
		break;

	case 1: // Сверху вниз, справа налево
		for (int x = R; x < size - R; x++) {
			for (int y = size - 1 - R; y >= R; y--) {
				if (is_safe(x, y)) return point(x, y);
			}
		}
		break;

	case 2: // Снизу вверх, слева направо
		for (int x = size - 1 - R; x >= R; x--) {
			for (int y = R; y < size - R; y++) {
				if (is_safe(x, y)) return point(x, y);
			}
		}
		break;

	case 3: // Сверху вниз, слева направо (стандартный порядок)
		for (int x = R; x < size - R; x++) {
			for (int y = R; y < size - R; y++) {
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
	case 3:
		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	case 2:
		for (int x = size - 1; x >= 0; x--)
			for (int y = 0; y < size; y++)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	case 1:
		for (int x = 0; x < size; x++)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	case 0:
		for (int x = size - 1; x >= 0; x--)
			for (int y = size - 1; y >= 0; y--)
				if (game[x][y].subject == 0) return point(x, y);
		break;
	}

	// Если карта абсолютно монолитна и пустых мест нет вообще
	return point(0, 0);
}

point set_LEVEL_escape(vector<vector<tile>>& game, int seed)
{
	point ESC = find_player_spawn(game, 1, seed);
	game[ESC.x][ESC.y].floor = 4;
	return ESC;
}
point set_player_spawn(vector<vector<tile>>& game, int seed)
{
	point SP = find_player_spawn(game, 1, seed);
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
void set_ore(vector<vector<tile>>& game, int seed, int level = 0, bool grow = 0)
{
	random_ore_spawn(game, seed, level);
	if (grow)
		random_ore_grow(game, seed);
}


static int MAPs = 0;
enum level_type { cave };
class LEVEL
{
protected:
	int ID; 
	int Seed;
	string Name;
	vector<vector<tile>> Grid;
	point Spawn;
	point Escape;
	level_type Type;

public:
	LEVEL(string n = "", level_type t = cave, int seed = 23, int size = 32) : Name(n), Type(t), Seed(seed)
	{
		ID = ++MAPs;
		Grid.resize(size, vector<tile>(size, tile(1)));
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
				cout << "CAVE: ";
				break;
			default:
				cout << "LEVEL: ";
				break;
			}
			cout << Name << " with SEED: " << Seed << " GENERATED\n";
		}
	}
	int getID() { return ID; }
	int getSeed() { return Seed; }
	string getName() { return Name; }
	int getSize() { return Grid.size(); }
	vector<vector<tile>>& getGrid() { return Grid; }
	point getSpawn() { return Spawn; }

	void setName(string NewName) { Name = NewName; }
	bool destroy_sub(point sub)
	{
		if (!outBorder(Grid, sub) && Grid[sub.x][sub.y].subject != 2)
		{
			Grid[sub.x][sub.y].subject = 0;
			return true;
		}
		else
		{
			cout << "cant break " << sub.x << ',' << sub.y << '\n';
			return false;
		}
			
	}

	~LEVEL()
	{
		switch (Type)
		{
		case cave:
			cout << "CAVE: ";
			break;
		default:
			cout << "LEVEL: ";
			break;
		}
		cout << Name << " with SEED: " << Seed << " DELETED\n";
	}

};
//    0     1     2     3     4     5     6     7
//  {"  ", "`.", "LV", "SP", "EN", "PL", "  ", "  "},   // Пол (floor)
//  {"  ", "[]", "WA", "OR", "  ", "  ", "  ", "  "},   // Стены/объекты (subject)
//  {"  ", "@@", "  ", "  ", "  ", "  ", "  ", "  "},   // Воздух (air)

static int ENTs = 0;
enum Dir { north, south, west, east };
enum AI_type { None };
class ENTITY
{
protected:
	int ID;
	string Name;
	LEVEL& Map;
	point Pos;
public:
	ENTITY(LEVEL& game, point pos, string name) : Name(name), Pos(pos), Map(game)
	{
		ID = ++ENTs;
		//cout << "ENTITY: " << Name << " CREATED\n";
	}

	virtual int getID() const { return ID; }
	virtual string getName() const { return Name; }
	virtual point getPos() const { return Pos; }
	virtual LEVEL& getMAP() const { return Map; }
	virtual void setName(string NewName) { Name = NewName; }
	virtual void setPos(point NewPos) { Pos = NewPos; }
	virtual void setMAP(LEVEL& NewMap) { Map = NewMap; }

	virtual ~ENTITY()
	{
		//cout << "ENTITY: " << Name << " DELETED\n";
	}
};
class CHARACTER : public ENTITY
{
protected:
	int HP;
	int DMG;
	Dir FACE = south;
	AI_type AI = None;
public:
	CHARACTER(LEVEL& game, point pos, string name, int hp = 10, int dmg = 0, AI_type ai = None) : ENTITY(game, pos, name), HP(hp), DMG(dmg), AI(ai)
	{
		// cout << "CHARACTER: " << Name << " CREATED\n";
	}

	virtual int getID() const override { return ID; }
	virtual string getName() const override { return Name; }
	virtual point getPos() const override { return Pos; }
	virtual LEVEL& getMAP() const override { return Map; }
	virtual void setName(string NewName) override { Name = NewName; }
	virtual void setPos(point NewPos) override
	{
		if (NewPos.x >= 0 && NewPos.x < getMAP().getSize() && NewPos.y >= 0 && NewPos.y < getMAP().getSize())
		{
			Pos = NewPos;
		}
	}
	virtual void setMAP(LEVEL& NewMap) override { Map = NewMap; }

	virtual bool isALive() const
	{
		return HP > 0;
	}
	virtual int getHP() const { return HP; }
	virtual int getDMG() const { return DMG; }
	virtual AI_type getAI() const { return AI; }
	virtual void setHP(int NewHP) { HP = NewHP; }
	virtual void setDMG(int NewDMG) { DMG = NewDMG; }
	virtual void setAI(AI_type NewAI) { AI = NewAI; }
	virtual Dir getFacing() const { return FACE; }
	virtual void setFacing(Dir NewFACE) { FACE = NewFACE;}

	virtual void move(Dir dir)
	{
		if (!isALive())
			return;
		int newX = Pos.x;
		int newY = Pos.y;
		int mapSize = getMAP().getSize();

		switch (dir)
		{
		case north: newY = (Pos.y < mapSize - 1) ? Pos.y + 1 : Pos.y; break;
		case south: newY = (Pos.y > 0) ? Pos.y - 1 : Pos.y; break;
		case west:  newX = (Pos.x < mapSize - 1) ? Pos.x + 1 : Pos.x; break;
		case east:  newX = (Pos.x > 0) ? Pos.x - 1 : Pos.x; break;
		}

		if (newX != Pos.x || newY != Pos.y) {
			Pos.x = newX;
			Pos.y = newY;
			cout << Name << " MOVED to (" << Pos.x << ", " << Pos.y << ")" << endl;
		}
		else {
			cout << Name << " CANT MOVE" << endl;
		}
	}
	virtual void takeDamage(int dmg)
	{
		if (dmg < 0)
			return;
		HP -= dmg;
		if (HP < 0)
			HP = 0;
	}
	virtual void giveDamage(CHARACTER& enemy)
	{
		if ((DMG < 0) || (!isALive()))
			return;
		else
			enemy.takeDamage(DMG);
	}


	virtual ~CHARACTER() override
	{
		// cout << "CHARACTER: " << Name << " DELETED\n";
	}
};
class PLAYER : public CHARACTER
{
protected:


public:
	PLAYER(LEVEL& game, point pos, string name, int hp = 100, int dmg = 10, AI_type ai = None) : CHARACTER(game, pos, name, hp, dmg, ai)
	{
		cout << "PLAYER: " << Name << " CREATED\n";
	}

	virtual int getID() const override { return ID; }
	virtual string getName() const override { return Name; }
	virtual point getPos() const override { return Pos; }
	virtual LEVEL& getMAP() const override { return Map; }
	virtual void setName(string NewName) override { Name = NewName; }
	virtual void setPos(point NewPos) override
	{
		if (NewPos.x >= 0 && NewPos.x < getMAP().getSize() && NewPos.y >= 0 && NewPos.y < getMAP().getSize())
		{
			Pos = NewPos;
		}
	}
	virtual void setMAP(LEVEL& NewMap) override { Map = NewMap; }

	virtual bool isALive() const
	{
		return HP > 0;
	}
	virtual int getHP() const { return HP; }
	virtual int getDMG() const { return DMG; }
	virtual AI_type getAI() const { return AI; }
	virtual void setHP(int NewHP) { HP = NewHP; }
	virtual void setDMG(int NewDMG) { DMG = NewDMG; }
	virtual void setAI(AI_type NewAI) { AI = NewAI; }
	virtual Dir getFacing() const { return FACE; }
	virtual void setFacing(Dir NewFACE) { FACE = NewFACE; }

	virtual void move(Dir dir) override
	{
		if (!isALive())
			return;
		int newX = Pos.x;
		int newY = Pos.y;
		int mapSize = getMAP().getSize();

		switch (dir)
		{
		case south: 
			FACE = south;
			newY = (Pos.y < mapSize - 1 && !Map.getGrid()[newX][Pos.y + 1].subject) ? Pos.y + 1 : Pos.y;
			break;
		case north: 
			FACE = north;
			newY = (Pos.y > 0 && !Map.getGrid()[newX][Pos.y - 1].subject) ? Pos.y - 1 : Pos.y; 
			break;
		case east:  
			FACE = east;
			newX = (Pos.x < mapSize - 1 && !Map.getGrid()[Pos.x + 1][newY].subject) ? Pos.x + 1 : Pos.x; 
			break;
		case west:  
			FACE = west;
			newX = (Pos.x > 0 && !Map.getGrid()[Pos.x - 1][newY].subject) ? Pos.x - 1 : Pos.x; 
			break;
		}

		if (newX != Pos.x || newY != Pos.y) {
			Pos.x = newX;
			Pos.y = newY;
			//cout << Name << " MOVED to (" << Pos.x << ", " << Pos.y << ")" << endl;
		}
		else {
			cout << Name << " cant be moved to ";
			switch (dir)
			{
			case 0:
				cout << "NORTH\n";
				break;
			case 1:
				cout << "SOUTH\n";
				break;
			case 2:
				cout << "WEST\n";
				break;
			case 3:
				cout << "EAST\n";
				break;
			}
		}
	}
	virtual void takeDamage(int dmg) override
	{
		if (dmg < 0)
			return;
		HP -= dmg;
		if (HP < 0)
			HP = 0;
	}
	virtual void giveDamage(CHARACTER& enemy) override
	{
		if ((DMG < 0) || (!isALive()))
			return;
		else
			enemy.takeDamage(DMG);
	}
	virtual bool destroy_on_facing()
	{
		if (!isALive())
			return false;
		int mapSize = getMAP().getSize();
		switch (FACE)
		{
		case south:
			return Map.destroy_sub({ Pos.x, Pos.y + 1 });
			break;
		case north:
			return Map.destroy_sub({ Pos.x, Pos.y - 1 });
			break;
		case east:
			return Map.destroy_sub({ Pos.x + 1, Pos.y });
			break;
		case west:
			return Map.destroy_sub({ Pos.x - 1, Pos.y });
			break;
		}
	}

	virtual ~PLAYER() override
	{
		cout << "PLAYER: " << Name << " DELETED\n";
	}

};
//           ||   
//optimized	_||_ 
//   shit   \  /
//           \/
void SET_GRID_TILES(vector<vector<tile>>& map, vector<vector<sf::RectangleShape>>& tiles)
{
	const int MAP_WIDTH = map.size();
	const int MAP_HEIGHT = map.size();
	const int TILE_SIZE = 1024 / map.size();
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			sf::RectangleShape rect({ (float)TILE_SIZE, (float)TILE_SIZE });

			rect.setPosition({ (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) });

			sf::Color color;
			if (!map[x][y].subject)
			{
				if (map[x][y].floor == 1) {
					color = sf::Color(61, 56, 56);      //stone
				}
				else if (map[x][y].floor == 2) {
					color = sf::Color(209, 83, 10); //lava
				}
				else if (map[x][y].floor == 3) {
					color = sf::Color::Green; // SP
				}
				else if (map[x][y].floor == 4) {
					color = sf::Color::Black; // ESC
				}
				else {
					color = sf::Color::Black;     // По умолчанию
				}
			}
			else
			{
				if (map[x][y].subject == 1) {
					color = sf::Color(44, 40, 43);
				}
				else if (map[x][y].subject == 2) {
					color = sf::Color(31, 31, 31);
				}
				else if (map[x][y].subject == 3) {
					color = sf::Color(115, 83, 64);
				}
			}


			rect.setFillColor(color);

			rect.setOutlineColor(sf::Color::Black);
			rect.setOutlineThickness(1.0f);

			tiles[x][y] = rect;
		}
	}
}
void UPDATE_GRID_TILE(vector<vector<tile>>& map, vector<vector<sf::RectangleShape>>& tiles, point dot)
{
	int x = dot.x;
	int y = dot.y;
	sf::Color color;
	if (!map[x][y].subject)
	{
		if (map[x][y].floor == 1) {
			color = sf::Color(61, 56, 56);      //stone
		}
		else if (map[x][y].floor == 2) {
			color = sf::Color(209, 83, 10); //lava
		}
		else if (map[x][y].floor == 3) {
			color = sf::Color::Green; // SP
		}
		else if (map[x][y].floor == 4) {
			color = sf::Color::Black; // ESC
		}
		else {
			color = sf::Color::Black;     // По умолчанию
		}
	}
	else
	{
		if (map[x][y].subject == 1) {
			color = sf::Color(44, 40, 43);
		}
		else if (map[x][y].subject == 2) {
			color = sf::Color(31, 31, 31);
		}
		else if (map[x][y].subject == 3) {
			color = sf::Color(115, 83, 64);
		}
	}
	tiles[x][y].setFillColor(color);

}
void DRAW_GRID(sf::RenderWindow& w, vector<vector<sf::RectangleShape>>& tiles)
{
	int size = tiles.size();
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			w.draw(tiles[x][y]);
}

void SET_PLAYER_TILE(PLAYER& p, sf::RectangleShape& tile)
{
	const int TILE_SIZE = 1024 / p.getMAP().getSize();
	sf::RectangleShape rect({ (float)TILE_SIZE, (float)TILE_SIZE });
	rect.setPosition({ (float)(p.getPos().x * TILE_SIZE), (float)(p.getPos().y * TILE_SIZE) });
	sf::Color color(180, 32, 32);
	rect.setFillColor(color);
	tile = rect;
}
void UPDATE_PLAYER_TILE(PLAYER& p, sf::RenderWindow& w, sf::RectangleShape& tile)
{
	const int TILE_SIZE = 1024 / p.getMAP().getSize();
	tile.setPosition({ (float)(p.getPos().x * TILE_SIZE), (float)(p.getPos().y * TILE_SIZE) });
}
void DRAW_PLAYER(sf::RenderWindow& w, sf::RectangleShape& tile)
{
	w.draw(tile);
}

void REFRESH_DISPLAY(sf::RenderWindow& w, vector<vector<sf::RectangleShape>>& tiles, sf::RectangleShape& player)
{
	w.clear();
	DRAW_GRID(w, tiles);
	DRAW_PLAYER(w, player);
	w.display();
}

void GAME()
{
	const int MAP_SIZE = 48; // for gen
	const int MAP_WIDTH = MAP_SIZE;  
	const int MAP_HEIGHT = MAP_SIZE; 
	const int TILE_SIZE = 1024 / MAP_SIZE;
	sf::RenderWindow window(sf::VideoMode({ MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE }), "Game");
	window.setFramerateLimit(0);

	sf::Clock moveClock;
	sf::Clock breakClock;
	const float moveDelay = 0.16f; // задержка передвижения
	const float breakDelay = 1.97f; // задержка копания

	LEVEL game("Пещера", cave, rand(), MAP_SIZE);
	PLAYER p1(game, game.getSpawn(), "HELLBOUND");

	vector<vector<sf::RectangleShape>> tiles(MAP_SIZE, vector<sf::RectangleShape>(MAP_SIZE, sf::RectangleShape()));
	sf::RectangleShape player_tile;
	SET_GRID_TILES(game.getGrid(), tiles);
	SET_PLAYER_TILE(p1, player_tile);

	while (window.isOpen()) 
	{
		// event checker
		while (const optional<sf::Event> p_event = window.pollEvent()) 
		{ 
			//closing
			if (p_event->is<sf::Event::Closed>())
			{
				window.close();
			}

			// digging button check
			if (breakClock.getElapsedTime().asSeconds() >= breakDelay)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					if (p1.destroy_on_facing())
					{
						switch (p1.getFacing())
						{
						case 0: //north
							UPDATE_GRID_TILE(game.getGrid(), tiles, { p1.getPos().x, p1.getPos().y - 1 });
							break;
						case 1: //south
							UPDATE_GRID_TILE(game.getGrid(), tiles, { p1.getPos().x, p1.getPos().y + 1 });
							break;
						case 2: //west
							UPDATE_GRID_TILE(game.getGrid(), tiles, { p1.getPos().x - 1, p1.getPos().y  });
							break;
						case 3: //east
							UPDATE_GRID_TILE(game.getGrid(), tiles, { p1.getPos().x + 1, p1.getPos().y });
							break;

						}
					}
				}
			}

			// movement control
			if (moveClock.getElapsedTime().asSeconds() >= moveDelay) 
			{ 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
					p1.move(north);
					UPDATE_PLAYER_TILE(p1, window, player_tile);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
					p1.move(south);
					UPDATE_PLAYER_TILE(p1, window, player_tile);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
					p1.move(west);
					UPDATE_PLAYER_TILE(p1, window, player_tile);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
					p1.move(east);
					UPDATE_PLAYER_TILE(p1, window, player_tile);
				}
					moveClock.restart();
			}
		}
		// screen updater
		REFRESH_DISPLAY(window, tiles, player_tile); 
	}

}

int main() {
	system("chcp 1251");
	srand(time(0));
	GAME();

	return 0;
}
