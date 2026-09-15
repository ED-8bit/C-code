#include <iostream>
#include "WORLD.h"
#include "STRUCTS.h"
#include "ENTS.h"
#include <vector>


using namespace std;

ENTITY::ENTITY(LEVEL& game, point_double pos, string name, int size) : Name(name), Pos(pos), Map(game), Size(size)
{
	ID = ++ENTs;
	//cout << "ENTITY: " << Name << " CREATED\n";
}
ENTITY::~ENTITY()
{
	//cout << "ENTITY: " << Name << " DELETED\n";
}

CHARACTER::CHARACTER(LEVEL& game, point_double pos, string name, int size, int hp, int dmg, AI_type ai) : ENTITY(game, pos, name, size), HP(hp), DMG(dmg), AI(ai)
{
	// cout << "CHARACTER: " << Name << " CREATED\n";
}
CHARACTER::~CHARACTER()
{
	// cout << "CHARACTER: " << Name << " DELETED\n";
}

bool CHARACTER::isALive() const
{
	return HP > 0;
}
void CHARACTER::move(Dir dir, int TILE_SIZE)
{
	if (!isALive())
		return;
	double newX = Pos.x;
	double newY = Pos.y;
	double mapSize = double(getMAP().getSize());

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
void CHARACTER::takeDamage(int dmg)
{
	if (dmg < 0)
		return;
	HP -= dmg;
	if (HP < 0)
		HP = 0;
}
void CHARACTER::giveDamage(CHARACTER& enemy)
{
	if ((DMG < 0) || (!isALive()))
		return;
	else
		enemy.takeDamage(DMG);
}

PLAYER::PLAYER(LEVEL& game, point_double pos, string name, int size, int hp, int dmg, AI_type ai) : CHARACTER(game, pos, name, size, hp, dmg, ai)
{
	cout << "PLAYER: " << Name << " CREATED\n";
}
PLAYER::PLAYER(LEVEL& game, point_int pos, string name, int size, int hp, int dmg, AI_type ai) : CHARACTER(game, { double(pos.x) + 0.5, double(pos.y) + 0.5 }, name, size, hp, dmg, ai)
{
	cout << "PLAYER: " << Name << " CREATED\n";
}
PLAYER::~PLAYER()
{
	cout << "PLAYER: " << Name << " DELETED\n";
}

bool PLAYER::isALive() const
{
	return HP > 0;
}
void PLAYER::move(Dir dir, int TILE_SIZE) 
{
	if (!isALive())
		return;
	double newX = Pos.x;
	double newY = Pos.y;
	double mapSize = double(getMAP().getSize());
	double step = 0.04;
	double block = double(getSize()) / double(TILE_SIZE) / 2;
	switch (dir)
	{
	case north_east:
		FACE = north_east;   //                           ':                                                            :'
		newY = (Pos.y > 0 && (!Map.getGrid()[int(newX - block)][int(Pos.y - block - step)].getSubject().getType()) && (!Map.getGrid()[int(newX + block)][int(Pos.y - block - step)].getSubject().getType()))
			? Pos.y - step : Pos.y;
		newX = (Pos.x < mapSize - 1 && (!Map.getGrid()[int(Pos.x + block + step)][int(newY - block)].getSubject().getType()) && (!Map.getGrid()[int(Pos.x + block + step)][int(newY + block)].getSubject().getType()))
			? Pos.x + step : Pos.x;
		break;
	case north_west:
		FACE = north_west;
		newY = (Pos.y > 0 && (!Map.getGrid()[int(newX - block)][int(Pos.y - block - step)].getSubject().getType()) && (!Map.getGrid()[int(newX + block)][int(Pos.y - block - step)].getSubject().getType()))
			? Pos.y - step : Pos.y;
		newX = (Pos.x > 0 && (!Map.getGrid()[int(Pos.x - block - step)][int(newY - block)].getSubject().getType()) && (!Map.getGrid()[int(Pos.x - block - step)][int(newY + block)].getSubject().getType()))
			? Pos.x - step : Pos.x;
		break;
	case south_east:
		FACE = south_east;
		newY = (Pos.y < mapSize - 1 && (!Map.getGrid()[int(newX - block)][int(Pos.y + block + step)].getSubject().getType()) && (!Map.getGrid()[int(newX + block)][int(Pos.y + block + step)].getSubject().getType()))
			? Pos.y + step : Pos.y;
		newX = (Pos.x < mapSize - 1 && (!Map.getGrid()[int(Pos.x + block + step)][int(newY - block)].getSubject().getType()) && (!Map.getGrid()[int(Pos.x + block + step)][int(newY + block)].getSubject().getType()))
			? Pos.x + step : Pos.x;
		break;
	case south_west:
		newY = (Pos.y < mapSize - 1 && (!Map.getGrid()[int(newX - block)][int(Pos.y + block + step)].getSubject().getType()) && (!Map.getGrid()[int(newX + block)][int(Pos.y + block + step)].getSubject().getType()))
			? Pos.y + step : Pos.y;
		newX = (Pos.x > 0 && (!Map.getGrid()[int(Pos.x - block - step)][int(newY - block)].getSubject().getType()) && (!Map.getGrid()[int(Pos.x - block - step)][int(newY + block)].getSubject().getType()))
			? Pos.x - step : Pos.x;
		break;
	case south:
		FACE = south;    //                                       ;:                                                            :;
		newY = (Pos.y < mapSize - 1 && (!Map.getGrid()[int(newX - block)][int(Pos.y + block + step)].getSubject().getType()) && (!Map.getGrid()[int(newX + block)][int(Pos.y + block + step)].getSubject().getType()))
			? Pos.y + step : Pos.y;
		break;
	case north:
		FACE = north;   //                           ':                                                            :'
		newY = (Pos.y > 0 && (!Map.getGrid()[int(newX - block)][int(Pos.y - block - step)].getSubject().getType()) && (!Map.getGrid()[int(newX + block)][int(Pos.y - block - step)].getSubject().getType()))
			? Pos.y - step : Pos.y;
		break;
	case east:
		FACE = east;   //                            :'                                                            :;
		newX = (Pos.x < mapSize - 1 && (!Map.getGrid()[int(Pos.x + block + step)][int(newY - block)].getSubject().getType()) && (!Map.getGrid()[int(Pos.x + block + step)][int(newY + block)].getSubject().getType()))
			? Pos.x + step : Pos.x;
		break;
	case west:
		FACE = west;   //                            ':                                                            ;:
		newX = (Pos.x > 0 && (!Map.getGrid()[int(Pos.x - block - step)][int(newY - block)].getSubject().getType()) && (!Map.getGrid()[int(Pos.x - block - step)][int(newY + block)].getSubject().getType()))
			? Pos.x - step : Pos.x;
		break;
	}

	if (newX != Pos.x || newY != Pos.y) {
		Pos.x = newX;
		Pos.y = newY;
		//cout << Name << " MOVED to (" << Pos.x << ", " << Pos.y << ")" << endl;
	}
	else {
		//cout << Name << " cant be moved to ";
		//switch (dir)
		//{
		//case 0:
		//	cout << "NORTH\n";
		//	break;
		//case 1:
		//	cout << "SOUTH\n";
		//	break;
		//case 2:
		//	cout << "WEST\n";
		//	break;
		//case 3:
		//	cout << "EAST\n";
		//	break;
		//}
	}
}
void PLAYER::takeDamage(int dmg) 
{
	if (dmg < 0)
		return;
	HP -= dmg;
	if (HP < 0)
		HP = 0;
}
void PLAYER::giveDamage(CHARACTER& enemy) 
{
	if ((DMG < 0) || (!isALive()))
		return;
	else
		enemy.takeDamage(DMG);
}
bool PLAYER::destroy_on_facing()
{
	if (!isALive())
		return false;
	size_t mapSize = getMAP().getSize();
	switch (FACE)
	{
	case south:
		return (Map.destroy_sub({ int(Pos.x), int(Pos.y + 1) }) || Map.destroy_sub({ int(Pos.x + 1), int(Pos.y + 1) }));
		break;
	case north:
		return (Map.destroy_sub({ int(Pos.x), int(Pos.y - 1) }) || Map.destroy_sub({ int(Pos.x + 1), int(Pos.y - 1) }));
		break;
	case east:
		return (Map.destroy_sub({ int(Pos.x + 1), int(Pos.y) }) || Map.destroy_sub({ int(Pos.x + 1), int(Pos.y + 1) }));
		break;
	case west:
		return (Map.destroy_sub({ int(Pos.x - 1), int(Pos.y) }) || Map.destroy_sub({ int(Pos.x - 1), int(Pos.y + 1) }));
		break;
	default:
		return false;
		break;
	}
}
