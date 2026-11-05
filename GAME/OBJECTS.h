#pragma once

// Объекты
class SUBJECT {
protected:
	int ID;
	int toughness;
public:
	SUBJECT();
	virtual ~SUBJECT();

	int getID(); // Возвращает ID объекта
	virtual int getToughness(); // Возвращает прочность объекта
	virtual void setToughness(int t); // Устанавливает прочность объекта
	virtual void DecreaseToughness(int dmg); //Уменьшает прочность объекта
};
class Stone: public SUBJECT
{
protected:

public:
	Stone();
	virtual ~Stone();
};
class OreInStone : public Stone
{
protected:

public:
	OreInStone();
	~OreInStone();
};
class EndStone: public SUBJECT {
private:

public:
	EndStone();
	~EndStone();

	void DecreaseToughness(int dmg) override;
	void setToughness(int t) override;
};


// Полы
class FLOOR
{
protected:
	int ID;
	double SpeedModifyer;
public:
	FLOOR();
	~FLOOR();

	int getID(); // Возвращает ID поверхности
	virtual void setSpeedModifyer(double s); // Устанавливает модификатор скорости для поверхности
	virtual double getSpeedModifyer(); // Возвращает модификатор скорости для поверхности
};

class StoneFloor:public FLOOR
{
protected:

public:
	StoneFloor();
	~StoneFloor();

};

class StoneFloorEXT : public StoneFloor
{
private:

public:
	StoneFloorEXT();
	~StoneFloorEXT();
};
class StoneFloorSPWN : public StoneFloor
{
private:

public:
	StoneFloorSPWN();
	~StoneFloorSPWN();
};





