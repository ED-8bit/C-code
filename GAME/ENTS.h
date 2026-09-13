#pragma once
#include "WORLD.h"
#include "STRUCTS.h"


extern int ENTs;
enum Dir { north, south, west, east, north_west, north_east, south_west, south_east };
enum AI_type { None };

class ENTITY
{
protected:
	int ID;
	std::string Name;
	int Size;
	LEVEL& Map;
	point_double Pos;
public:
	ENTITY(LEVEL& game, point_double pos, std::string name, int size);

	virtual void setSize(int NewSize) { Size = NewSize; }
	virtual void setName(std::string NewName) { Name = NewName; }
	virtual void setPos(point_double NewPos) { Pos = NewPos; }
	virtual void setMAP(LEVEL& NewMap) { Map = NewMap; }

	virtual int getID() const { return ID; }
	virtual int getSize() const { return Size; }
	virtual std::string getName() const { return Name; }
	virtual point_double getPos() const { return Pos; }
	virtual LEVEL& getMAP() const { return Map; }

	virtual ~ENTITY();
};
class CHARACTER : public ENTITY
{
protected:
	int HP;
	int DMG;
	Dir FACE = south;
	AI_type AI = None;
public:
	CHARACTER(LEVEL& game, point_double pos, std::string name, int size, int hp = 10, int dmg = 0, AI_type ai = None);

	virtual void setSize(int NewSize) override { Size = NewSize; }
	virtual void setName(std::string NewName) override { Name = NewName; }
	virtual void setPos(point_double NewPos) override
	{
		if (NewPos.x >= 0 && NewPos.x < double(getMAP().getSize()) && NewPos.y >= 0 && NewPos.y < double(getMAP().getSize()))
		{
			Pos = NewPos;
		}
	}
	virtual void setMAP(LEVEL& NewMap) override { Map = NewMap; }
	virtual void setHP(int NewHP) { HP = NewHP; }
	virtual void setDMG(int NewDMG) { DMG = NewDMG; }
	virtual void setAI(AI_type NewAI) { AI = NewAI; }
	virtual void setFacing(Dir NewFACE) { FACE = NewFACE; }

	virtual int getID() const override { return ID; }
	virtual std::string getName() const override { return Name; }
	virtual point_double getPos() const override { return Pos; }
	virtual LEVEL& getMAP() const override { return Map; }
	virtual int getSize() const override { return Size; }
	virtual int getHP() const { return HP; }
	virtual int getDMG() const { return DMG; }
	virtual AI_type getAI() const { return AI; }
	virtual Dir getFacing() const { return FACE; }

	virtual bool isALive() const;
	virtual void move(Dir dir, int TILE_SIZE);
	virtual void takeDamage(int dmg);
	virtual void giveDamage(CHARACTER& enemy);


	virtual ~CHARACTER() override;
};
class PLAYER : public CHARACTER
{
protected:


public:
	PLAYER(LEVEL& game, point_double pos, std::string name, int size, int hp = 100, int dmg = 10, AI_type ai = None);
	PLAYER(LEVEL& game, point_int pos, std::string name, int size, int hp = 100, int dmg = 10, AI_type ai = None);

	virtual void setName(std::string NewName) override { Name = NewName; }
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

	virtual std::string getName() const override { return Name; }
	virtual int getSize() const override { return Size; }
	virtual int getHP() const { return HP; }
	virtual int getDMG() const { return DMG; }
	virtual AI_type getAI() const { return AI; }
	virtual point_double getPos() const override { return Pos; }
	virtual Dir getFacing() const { return FACE; }
	virtual LEVEL& getMAP() const override { return Map; }
	virtual int getID() const override { return ID; }

	virtual bool isALive() const;
	virtual void move(Dir dir, int TILE_SIZE) override;
	virtual void takeDamage(int dmg) override;
	virtual void giveDamage(CHARACTER& enemy) override;
	virtual bool destroy_on_facing();

	virtual ~PLAYER() override;
};