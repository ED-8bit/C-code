#pragma once
#include "WORLD.h"
#include "STRUCTS.h"

using namespace std;

extern int ENTs;
enum Dir { north, south, west, east, north_west, north_east, south_west, south_east };
enum AI_type { None };

class ENTITY
{
protected:
	int ID;
	string Name;
	int Size;
	LEVEL& Map;
	point_double Pos;
public:
	ENTITY(LEVEL& game, point_double pos, string name, int size) : Name(name), Pos(pos), Map(game), Size(size)
	{
		ID = ++ENTs;
		//cout << "ENTITY: " << Name << " CREATED\n";
	}

	virtual void setSize(int NewSize) { Size = NewSize; }
	virtual void setName(string NewName) { Name = NewName; }
	virtual void setPos(point_double NewPos) { Pos = NewPos; }
	virtual void setMAP(LEVEL& NewMap) { Map = NewMap; }

	virtual int getID() const { return ID; }
	virtual int getSize() const { return Size; }
	virtual string getName() const { return Name; }
	virtual point_double getPos() const { return Pos; }
	virtual LEVEL& getMAP() const { return Map; }

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
	CHARACTER(LEVEL& game, point_double pos, string name, int size, int hp = 10, int dmg = 0, AI_type ai = None) : ENTITY(game, pos, name, size), HP(hp), DMG(dmg), AI(ai)
	{
		// cout << "CHARACTER: " << Name << " CREATED\n";
	}

	virtual void setSize(int NewSize) override { Size = NewSize; }
	virtual int getID() const override { return ID; }
	virtual string getName() const override { return Name; }
	virtual point_double getPos() const override { return Pos; }
	virtual LEVEL& getMAP() const override { return Map; }
	virtual void setName(string NewName) override { Name = NewName; }
	virtual void setPos(point_double NewPos) override
	{
		if (NewPos.x >= 0 && NewPos.x < double(getMAP().getSize()) && NewPos.y >= 0 && NewPos.y < double(getMAP().getSize()))
		{
			Pos = NewPos;
		}
	}
	virtual void setMAP(LEVEL& NewMap) override { Map = NewMap; }

	virtual int getSize() const override { return Size; }

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

	virtual void move(Dir dir, int TILE_SIZE)
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
	PLAYER(LEVEL& game, point_double pos, string name, int size, int hp = 100, int dmg = 10, AI_type ai = None) : CHARACTER(game, pos, name, size, hp, dmg, ai)
	{
		cout << "PLAYER: " << Name << " CREATED\n";
	}
	PLAYER(LEVEL& game, point_int pos, string name, int size, int hp = 100, int dmg = 10, AI_type ai = None) : CHARACTER(game, { double(pos.x) + 0.5, double(pos.y) + 0.5 }, name, size, hp, dmg, ai)
	{
		cout << "PLAYER: " << Name << " CREATED\n";
	}

	virtual void setName(string NewName) override { Name = NewName; }
	virtual void setSize(int NewSize) override { Size = NewSize; }
	virtual void setHP(int NewHP) { HP = NewHP; }
	virtual void setDMG(int NewDMG) { DMG = NewDMG; }
	virtual void setAI(AI_type NewAI) { AI = NewAI; }
	virtual void setPos(point_double NewPos) override
	{
		if (NewPos.x >= 0 && NewPos.x < double(getMAP().getSize()) && NewPos.y >= 0 && NewPos.y < double(getMAP().getSize()))
		{
			Pos = NewPos;
		}
	}
	virtual void setFacing(Dir NewFACE) { FACE = NewFACE; }
	virtual void setMAP(LEVEL& NewMap) override { Map = NewMap; }

	virtual string getName() const override { return Name; }
	virtual int getSize() const override { return Size; }
	virtual int getHP() const { return HP; }
	virtual int getDMG() const { return DMG; }
	virtual AI_type getAI() const { return AI; }
	virtual point_double getPos() const override { return Pos; }
	virtual Dir getFacing() const { return FACE; }
	virtual LEVEL& getMAP() const override { return Map; }
	virtual int getID() const override { return ID; }

	virtual bool isALive() const
	{
		return HP > 0;
	}
	virtual void move(Dir dir, int TILE_SIZE) override
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
			newY = (Pos.y > 0 && (!Map.getGrid()[int(newX - block)][int(Pos.y - block - step)].subject) && (!Map.getGrid()[int(newX + block)][int(Pos.y - block - step)].subject))
				? Pos.y - step : Pos.y;
			newX = (Pos.x < mapSize - 1 && (!Map.getGrid()[int(Pos.x + block + step)][int(newY - block)].subject) && (!Map.getGrid()[int(Pos.x + block + step)][int(newY + block)].subject))
				? Pos.x + step : Pos.x;
			break;
		case north_west:
			FACE = north_west;
			newY = (Pos.y > 0 && (!Map.getGrid()[int(newX - block)][int(Pos.y - block - step)].subject) && (!Map.getGrid()[int(newX + block)][int(Pos.y - block - step)].subject))
				? Pos.y - step : Pos.y;
			newX = (Pos.x > 0 && (!Map.getGrid()[int(Pos.x - block - step)][int(newY - block)].subject) && (!Map.getGrid()[int(Pos.x - block - step)][int(newY + block)].subject))
				? Pos.x - step : Pos.x;
			break;
		case south_east:
			FACE = south_east;
			newY = (Pos.y < mapSize - 1 && (!Map.getGrid()[int(newX - block)][int(Pos.y + block + step)].subject) && (!Map.getGrid()[int(newX + block)][int(Pos.y + block + step)].subject))
				? Pos.y + step : Pos.y;
			newX = (Pos.x < mapSize - 1 && (!Map.getGrid()[int(Pos.x + block + step)][int(newY - block)].subject) && (!Map.getGrid()[int(Pos.x + block + step)][int(newY + block)].subject))
				? Pos.x + step : Pos.x;
			break;
		case south_west:
			newY = (Pos.y < mapSize - 1 && (!Map.getGrid()[int(newX - block)][int(Pos.y + block + step)].subject) && (!Map.getGrid()[int(newX + block)][int(Pos.y + block + step)].subject))
				? Pos.y + step : Pos.y;
			newX = (Pos.x > 0 && (!Map.getGrid()[int(Pos.x - block - step)][int(newY - block)].subject) && (!Map.getGrid()[int(Pos.x - block - step)][int(newY + block)].subject))
				? Pos.x - step : Pos.x;
			break;
		case south:
			FACE = south;    //                                       ;:                                                            :;
			newY = (Pos.y < mapSize - 1 && (!Map.getGrid()[int(newX - block)][int(Pos.y + block + step)].subject) && (!Map.getGrid()[int(newX + block)][int(Pos.y + block + step)].subject))
				? Pos.y + step : Pos.y;
			break;
		case north:
			FACE = north;   //                           ':                                                            :'
			newY = (Pos.y > 0 && (!Map.getGrid()[int(newX - block)][int(Pos.y - block - step)].subject) && (!Map.getGrid()[int(newX + block)][int(Pos.y - block - step)].subject))
				? Pos.y - step : Pos.y;
			break;
		case east:
			FACE = east;   //                            :'                                                            :;
			newX = (Pos.x < mapSize - 1 && (!Map.getGrid()[int(Pos.x + block + step)][int(newY - block)].subject) && (!Map.getGrid()[int(Pos.x + block + step)][int(newY + block)].subject))
				? Pos.x + step : Pos.x;
			break;
		case west:
			FACE = west;   //                            ':                                                            ;:
			newX = (Pos.x > 0 && (!Map.getGrid()[int(Pos.x - block - step)][int(newY - block)].subject) && (!Map.getGrid()[int(Pos.x - block - step)][int(newY + block)].subject))
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
		}
	}

	virtual ~PLAYER() override
	{
		cout << "PLAYER: " << Name << " DELETED\n";
	}
};