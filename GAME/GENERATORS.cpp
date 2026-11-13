#include "GENERATORS.h"
#include "OBJECTS.h"
#include <vector>
#include <random>
#include <queue>
using namespace std;

CA_GEN::CA_GEN(vector<vector<tile>>& GG, int seed, point_int spawn, point_int exit): GEN_Grid(GG), Seed(seed), Spawn(spawn), Exit(exit) { Size = GEN_Grid.size();}
CA_GEN::~CA_GEN(){}

bool CA_GEN::onBorder(point_int Dot) {
	if (Dot.x == 0 || Dot.y == 0 || Dot.x == Size - 1 || Dot.y == Size - 1)
		return true;
	else
		return false;
}
bool CA_GEN::outBorder(point_int Dot) {
	if (Dot.x < 0 || Dot.y < 0 || Dot.x >= Size || Dot.y >= Size)
		return true;
	else
		return false;
}
bool CA_GEN::isPointSafe(point_int Dot, int R) {
	if (GEN_Grid[Dot.x][Dot.y].getSubject() != nullptr || 
		GEN_Grid[Dot.x][Dot.y].getFloor() != nullptr) return false;

	for (int dx = -R; dx <= R; dx++) {
		for (int dy = -R; dy <= R; dy++) {
			if (outBorder({ Dot.x + dx,Dot.y + dy })) return false;
			if (GEN_Grid[Dot.x + dx][Dot.y + dy].getSubject() != nullptr) return false;
		}
	}
	return true;
}

void CA_GEN::GridInit(){
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			GEN_Grid[x][y].setFloor(make_unique<StoneFloor>());
		}
	}
}
void CA_GEN::FillBySeed(int Percent = 50) {
	mt19937 rng(Seed);
	uniform_int_distribution<int> dist(1, 100);
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (dist(rng) < Percent)
			{
				GEN_Grid[x][y].setSubject(make_unique<Stone>());
			}		
		}
	}
}
void CA_GEN::Iteration(int Requiered) {
	vector<vector<tile>> newGrid = GEN_Grid;
	for (int x = 0; Size > x; x++)
	{
		for (int y = 0; Size > y; y++)
		{
			int neighbors = 0;
			int dx[8] = { -1, -1, -1,  0, 0,  1, 1, 1};
			int dy[8] = { -1,  0,  1, -1, 1, -1, 0, 1};
			
			for (int i = 0; i < 8; i++)
			{
				if (x > 0 && y > 0 && typeid(GEN_Grid[dx[i]][dy[i]].getSubject()).name() == "Stone")
					neighbors++;
			}

			if (neighbors > Requiered + 1 || neighbors < Requiered - 1)
				newGrid[x][y].setSubject(nullptr);
			else if (neighbors == Requiered || neighbors == Requiered - 1)
				newGrid[x][y].setSubject(make_unique<Stone>());

		}
	}
	GEN_Grid = newGrid;
}
void CA_GEN::DeleteSmallAreas(int Minzone) {
	vector<vector<bool>> visited(Size, vector<bool>(Size, false));
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (GEN_Grid[x][y].getSubject() == nullptr && !visited[x][y])
			{
				vector<point_int> AreaTile;
				queue<point_int> q;
				q.push({ x, y });
				visited[x][y] = true;

				while (!q.empty())
				{
					point_int({ x, y }) = q.front();
					q.pop();
					AreaTile.push_back({ x,y });

					int dx[] = { -1, 1, 0, 0 };
					int dy[] = { 0, 0, -1, 1 };

					for (int d = 0; d < 4; d++)
					{
						int nx = x + dx[d];
						int ny = y + dy[d];

						if (nx >= 0 && nx < Size && ny >= 0 && ny < Size &&
							GEN_Grid[nx][ny].getSubject() == nullptr && !visited[nx][ny])
						{
							visited[nx][ny] = true;
							q.push({ nx, ny });
						}
					}
				}

				if (!onBorder({ x, y }) && AreaTile.size() <= Minzone)
					for (point_int ForFill : AreaTile)
					{
						GEN_Grid[ForFill.x][ForFill.y].setSubject(make_unique<Stone>());
					}
			}
		}
	}
}
void CA_GEN::DestroyDebris() {
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (!onBorder({ x, y }))
			{
				int dx[4] = { -1, 0, 1, 1 };
				int dy[4] = { -1, -1, -1, 0 };

				for (int d = 0; d < 4; d++)
				{
					int ox = x + dx[d];
					int oy = y + dy[d];
					int nx = x - dx[d];
					int ny = y - dy[d];

					if (GEN_Grid[ox][oy].getSubject() == nullptr && GEN_Grid[nx][ny].getSubject() == nullptr)
					{
						GEN_Grid[x][y].setSubject(nullptr);
						break;
					}

				}
			}
		}
	}
}
void CA_GEN::Antialiasing() {
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (!onBorder({ x, y }))
			{
				int dx[4] = { -1, 0, 1, 1 };
				int dy[4] = { -1, -1, -1, 0 };

				for (int d = 0; d < 4; d++)
				{
					int ox = x + dx[d];
					int oy = y + dy[d];
					int nx = x - dx[d];
					int ny = y - dy[d];

					if (GEN_Grid[ox][oy].getSubject() != nullptr && GEN_Grid[nx][ny].getSubject() != nullptr)
					{
						GEN_Grid[x][y].setSubject(make_unique<Stone>());
						break;
					}

				}
			}
		}
	}
}
void CA_GEN::WallExpansion(int Additional) {
	for (int thick = 0; thick < Additional; thick++)
	{
		for (int x = thick; x < Size - thick; x++)
		{
			for (int y = thick; y << Size - thick; y++)
			{
				if ((x == thick || x == Size - thick - 1) || (y == thick || y == Size - thick - 1))
					GEN_Grid[x][y].setSubject(make_unique<EndStone>());
			}
		}
	}
}
void CA_GEN::SetSpawn(int Radius) {
	mt19937 s(Seed);
	unsigned int start = s();
	dir Dir = dir(start % 4 + 4);
	// Основной обход
	switch (Dir)
	{
	case south_east:
		for (int x = Radius; x < Size - Radius; x++)
		{
			for (int y = Radius; y < Size - Radius; y++)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	case north_east:
		for (int x = Radius; x < Size - Radius; x++)
		{
			for (int y = Size - 1 - Radius; y >= Radius; y--)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	case north_west:
		for (int x = Size - 1 - Radius; x >= Radius; x--)
		{
			for (int y = Radius; y < Size - Radius; y++)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	case south_west:
		for (int x = Size - 1 - Radius; x >= Radius; x--)
		{
			for (int y = Size - 1 - Radius; y >=  Radius; y--)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	}
	// Упрощенный обход
	switch (Dir)
	{
	case south_east:
		for (int x = 0; x < Size; x++)
		{
			for (int y = 0; y < Size; y++)
			{
				if (isPointSafe({ x, y }))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	case north_east:
		for (int x = 0; x < Size; x++)
		{
			for (int y = Size - 1; y >= 0; y--)
			{
				if (isPointSafe({ x, y }))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	case north_west:
		for (int x = Size - 1; x >= 0; x--)
		{
			for (int y = 0; y < Size; y++)
			{
				if (isPointSafe({ x, y }))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	case south_west:
		for (int x = Size - 1; x >= 0; x--)
		{
			for (int y = Size - 1; y >= 0; y--)
			{
				if (isPointSafe({ x, y }))
				{
					Spawn = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorSPWN>());
					return;
				}
			}
		}
		break;
	}
	// По умолчанию
	Spawn = { 0, 0 };
	GEN_Grid[0][0].setFloor(make_unique<StoneFloorSPWN>());
	return;
}
void CA_GEN::SetExit(int Radius) {
	mt19937 s(Seed);
	unsigned int start = s();
	dir Dir = dir(start % 4 + 4);
	// Основной обход
	switch (Dir)
	{
	case north_west:
		for (int x = Radius; x < Size - Radius; x++)
		{
			for (int y = Radius; y < Size - Radius; y++)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	case south_west:
		for (int x = Radius; x < Size - Radius; x++)
		{
			for (int y = Size - 1 - Radius; y >= Radius; y--)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	case south_east:
		for (int x = Size - 1 - Radius; x >= Radius; x--)
		{
			for (int y = Radius; y < Size - Radius; y++)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	case north_east:
		for (int x = Size - 1 - Radius; x >= Radius; x--)
		{
			for (int y = Size - 1 - Radius; y >= Radius; y--)
			{
				if (isPointSafe({ x, y }, Radius))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	}
	// Упрощенный обход
	switch (Dir)
	{
	case north_west:
		for (int x = 0; x < Size; x++)
		{
			for (int y = 0; y < Size; y++)
			{
				if (isPointSafe({ x, y }))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	case south_west:
		for (int x = 0; x < Size; x++)
		{
			for (int y = Size - 1; y >= 0; y--)
			{
				if (isPointSafe({ x, y }))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	case south_east:
		for (int x = Size - 1; x >= 0; x--)
		{
			for (int y = 0; y < Size; y++)
			{
				if (isPointSafe({ x, y }))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	case north_east:
		for (int x = Size - 1; x >= 0; x--)
		{
			for (int y = Size - 1; y >= 0; y--)
			{
				if (isPointSafe({ x, y }))
				{
					Exit = { x, y };
					GEN_Grid[x][y].setFloor(make_unique<StoneFloorEXT>());
					return;
				}
			}
		}
		break;
	}
	// По умолчанию
	Spawn = { 0, 0 };
	GEN_Grid[0][0].setFloor(make_unique<StoneFloorEXT>());
	return;
}
void CA_GEN::SetOre(int BaseRichness, bool Growing) {
	mt19937 ore(Seed);
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			if (typeid(GEN_Grid[x][y].getSubject()).name() == "Stone")
			{
				if ((ore() % 100 + 1) < BaseRichness)
				{
					GEN_Grid[x][y].setSubject(make_unique<OreInStone>());
				}
			}
		}
	}
	if (Growing)
	{
		vector<vector<tile>> newGrid = GEN_Grid;
		mt19937 growing(Seed);

		int dg;
		int dx[9] = { -1, -1, 0, 1, 1, 1, 0, -1 };
		int dy[9] = { 0, -1, -1, -1, 0, 1, 1, 1 };

		for (int x = 0; x < Size; x++)
		{
			for (int y = 0; y < Size; y++)
			{
				if ((typeid(GEN_Grid[x][y].getSubject()).name() == "OreInStone") && (!onBorder({x, y})))
				{
					do
					{
						dg = growing() % 8;
						if (typeid(GEN_Grid[x + dx[dg]][y + dy[dg]].getSubject()).name() == "Stone")
							newGrid[x + dx[dg]][y + dy[dg]].setSubject(make_unique<OreInStone>());


					} while(growing() % 5 != 3);
				}
			}
		}
		GEN_Grid = newGrid;
	}
}