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
	size_t size = game.size();
	if (dot.x == 0 || dot.y == 0 || dot.x == size - 1 || dot.y == size - 1)
		return true;
	else
		return false;
}

void seed_fill_CAVE(vector<vector<tile>>& game, int seed, int fill = 0)
{
	size_t size = game.size();
	mt19937 rng(seed);
	uniform_int_distribution<int> dist(0, 99);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (dist(rng) < fill)
				game[y][x].subject = 1;
		}
	}

}
void iteration_CAVE(vector<vector<tile>>& game, int need)
{
	int y, x;
	int size = game.size();
	vector<vector<tile>> newGame = game;
	for (y = 0; size > y; y++)
	{
		for (x = 0; size > x; x++)
		{
			int neighbors = 0;

			if (y > 0 && x > 0 && game[y - 1][x - 1].subject)
				neighbors++;

			if (y > 0 && game[y - 1][x].subject)
				neighbors++;

			if (y > 0 && x < size - 1 && game[y - 1][x + 1].subject)
				neighbors++;

			if (x > 0 && game[y][x - 1].subject)
				neighbors++;

			if (x < size - 1 && game[y][x + 1].subject)
				neighbors++;

			if (y < size - 1 && x > 0 && game[y + 1][x - 1].subject)
				neighbors++;

			if (y < size - 1 && game[y + 1][x].subject)
				neighbors++;

			if (y < size - 1 && x < size - 1 && game[y + 1][x + 1].subject)
				neighbors++;

			if (neighbors > need + 1 || neighbors < need - 1)
				newGame[y][x].subject = 0;
			else if (neighbors == need || neighbors == need - 1)
				newGame[y][x].subject = 1;

		}
	}
	game = newGame;
}
void fill_holes_CAVE(vector<vector<tile>>& game, int minzone = 0)
{
	int size = game.size();
	vector<vector<bool>> visited(size, vector<bool>(size, false));

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (!game[y][x].subject && !visited[y][x])
			{
				// Find connected component
				vector<pair<int, int>> component;
				queue<pair<int, int>> q;
				q.push({ y, x });
				visited[y][x] = true;
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
	int y, x, size = game.size();
	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			bool onBorder = true;
			if ((y != 0 && x != 0) && (y + 1 != size && x + 1 != size))
			{
				onBorder = false;
			}
			if (!onBorder)
			{
				int dx[] = { -1, 0, 1, 1, };
				int dy[] = { -1, -1, -1, 0, };

				for (int d = 0; d < 4; d++)
				{
					int x = y + dx[d];
					int y = x + dy[d];
					int nx = y - dx[d];
					int ny = x - dy[d];
					if (!game[x][y].subject && !game[nx][ny].subject)
						game[y][x].subject = 0;
				}
			}
		}
	}
}
void build_smoothing_CAVE(vector<vector<tile>>& game)
{
	int y, x, size = game.size();
	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
		{
			bool onBorder = true;
			if ((y != 0 && x != 0) && (y + 1 != size && x + 1 != size))
			{
				onBorder = false;
			}
			if (!onBorder)
			{
				int dx[] = { -1, 0, 1, 1, };
				int dy[] = { -1, -1, -1, 0, };

				for (int d = 0; d < 4; d++)
				{
					int x = y + dx[d];
					int y = x + dy[d];
					int nx = y - dx[d];
					int ny = x - dy[d];
					if (game[x][y].subject && game[nx][ny].subject)
						game[y][x].subject = 1;
				}
			}
		}
	}
}
void border_fill_CAVE(vector<vector<tile>>& game, int wall = 0)
{
	int y, x, thickness;
	int size = game.size();
	for (thickness = 0; thickness < wall; thickness++)
	{
		for (y = thickness; y < size - thickness; y++)
		{
			for (x = thickness; x < size - thickness; x++)
			{
				if ((y == thickness || y == size - thickness - 1) || (x == thickness || x == size - thickness - 1))
					game[y][x].subject = 2;
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
	vector<vector<tile>> grid;
	point Spawn;
	level_type Type;

public:
	LEVEL(string n = "", level_type t = cave, int seed = 23, int size = 32) : Name(n), Type(t), Seed(seed)
	{
		ID = ++MAPs;
		grid.resize(size, vector<tile>(size, tile(1)));
		if (Type == cave)
		{
			int i, iters = 4, fill = 46, need = 5, wall = 4, minzone = 100, debris = 2, smooth = 4, ore = 2;
			seed_fill_CAVE(grid, seed, fill);
			for (i = 0; i < iters; i++)
			{
				iteration_CAVE(grid, need);
			}
			border_fill_CAVE(grid, wall);
			fill_holes_CAVE(grid, minzone);
			for (i = 0; i < debris; i++)
			{
				destroy_debris_CAVE(grid);
			}
			for (i = 0; i < smooth; i++)
			{
				build_smoothing_CAVE(grid);
			}
			set_ore(grid, seed, ore, true);
			Spawn = set_player_spawn(grid, seed);
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
	int getSize() { return grid.size(); }
	vector<vector<tile>>& getGrid() { return grid; }
	point getSpawn() { return Spawn; }

	void setName(string NewName) { Name = NewName; }


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

	virtual void move(Dir dir) override
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

	virtual ~PLAYER() override
	{
		cout << "PLAYER: " << Name << " DELETED\n";
	}

};

void OUT_GRID(vector<vector<tile>>& map, sf::RenderWindow& w)
{
	const int MAP_WIDTH = 128;
	const int MAP_HEIGHT = 128;
	const int TILE_SIZE = 8;
	vector<sf::RectangleShape> tiles;
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			sf::RectangleShape rect({ (float)TILE_SIZE, (float)TILE_SIZE });

			rect.setPosition({ (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) });

			sf::Color color;
			if (!map[y][x].subject)
			{
				if (map[y][x].floor == 1) {
					color = sf::Color(61, 56, 56);      //stone
				}
				else if (map[y][x].floor == 2) {
					color = sf::Color(209, 83, 10); //lava
				}
				else if (map[y][x].floor == 3) {
					color = sf::Color::Green; // SP
				}
				else {
					color = sf::Color::Black;     // По умолчанию
				}
			}
			else
			{
				if (map[y][x].subject == 1) {
					color = sf::Color(44, 40, 43);
				}
				else if (map[y][x].subject == 2) {
					color = sf::Color(31, 31, 31);
				}
				else if (map[y][x].subject == 3) {
					color = sf::Color(115, 83, 64);
				}
			}


			rect.setFillColor(color);

			rect.setOutlineColor(sf::Color::Black);
			rect.setOutlineThickness(1.0f);

			tiles.push_back(rect);
		}
	}
	for (const auto& tile_rect : tiles)
	{
		w.draw(tile_rect);
	}
}
void OUT_PLAYER(PLAYER& p, sf::RenderWindow& w)
{
	const int MAP_WIDTH = 128;
	const int MAP_HEIGHT = 128;
	const int TILE_SIZE = 8;
	sf::RectangleShape rect({ (float)TILE_SIZE, (float)TILE_SIZE });
	rect.setPosition({ (float)(p.getPos().x * TILE_SIZE), (float)(p.getPos().y * TILE_SIZE) });
	sf::Color color(201, 16, 16);
	w.draw(rect);
}
void update_window(sf::RenderWindow& w, vector<vector<tile>>& map, PLAYER& p)
{
	w.clear();
	OUT_GRID(map, w);
	OUT_PLAYER(p, w);
	w.display();
}
void GAME()
{
	const int MAP_WIDTH = 128;
	const int MAP_HEIGHT = 128;
	const int TILE_SIZE = 8;
	sf::RenderWindow window(
		sf::VideoMode({ MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE }), "Game");

	LEVEL game("Пещера", cave, rand(), 128);
	PLAYER p1(game, game.getSpawn(), "HELLBOUND");

	while (window.isOpen()) {

		while (const auto p_event = window.pollEvent()) {

			if (p_event->is<sf::Event::Closed>())
				window.close();

			if (const auto* keyEvent = p_event->getIf<sf::Event::KeyPressed>()) {
				switch (keyEvent->code) {
				case sf::Keyboard::Key::W:
				case sf::Keyboard::Key::Up:
					p1.move(north);
					break;
				case sf::Keyboard::Key::S:
				case sf::Keyboard::Key::Down:
					p1.move(south);
					break;
				case sf::Keyboard::Key::A:
				case sf::Keyboard::Key::Left:
					p1.move(west);
					break;
				case sf::Keyboard::Key::D:
				case sf::Keyboard::Key::Right:
					p1.move(east);
					break;
				default:
					break;
				}
			}
		}
		update_window(window, game.getGrid(), p1);
	}

}


int main() {
	system("chcp 1251");
	srand(time(0));
	GAME();

	return 0;
}
