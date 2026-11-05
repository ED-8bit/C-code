#include "OBJECTS.h"

//Объекты

SUBJECT::SUBJECT() { ID = 0; toughness = -1; }
SUBJECT::~SUBJECT(){}

int SUBJECT::getID() { return ID; }
int SUBJECT::getToughness() { return toughness; }
void SUBJECT::setToughness(int t) { toughness = t; }
void SUBJECT::DecreaseToughness(int dmg) {
	toughness -= dmg;
	if (toughness <= 0)
	{
		toughness = 0;
	}
}


Stone::Stone(){ ID = 1; toughness = 300; }
Stone::~Stone(){}

OreInStone::OreInStone() { ID = 2; toughness = 500; }
OreInStone::~OreInStone(){}

EndStone::EndStone() { ID = 3; toughness = -1; }
EndStone::~EndStone(){}

void EndStone::DecreaseToughness(int dmg) { return; }
void EndStone::setToughness(int t) { return; }

//Полы

FLOOR::FLOOR() { ID = 0; SpeedModifyer = 1.0; }
FLOOR::~FLOOR(){}

int FLOOR::getID() { return ID; }
double FLOOR::getSpeedModifyer() { return SpeedModifyer; }
void FLOOR::setSpeedModifyer(double s = 1.0) { SpeedModifyer = s; }


StoneFloor::StoneFloor() { ID = 1; SpeedModifyer = 1.0; }
StoneFloor::~StoneFloor(){}

StoneFloorSPWN::StoneFloorSPWN() { ID = 2; SpeedModifyer = 1.0; }
StoneFloorSPWN::~StoneFloorSPWN() {}

StoneFloorEXT::StoneFloorEXT() { ID = 3; SpeedModifyer = 1.0; }
StoneFloorEXT::~StoneFloorEXT() {}