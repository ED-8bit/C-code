#pragma once
#include "STRUCTS.h"
enum class Materials
{
	None, Wood, Stone, Iron
};
enum class Blocks
{
	NotBlock, Cobblestone, Stone, Ore
};
enum class Tools
{
	NotTool, Pickaxe, Shovel, Axe
};

struct Including_Materials
{
	Materials primary;
	Materials secondary;
	//Material optional;

	Including_Materials(Materials p, Materials s = Materials::None): primary(p), secondary(s){}
};

class Item
{
protected:
	Including_Materials Materials;
	double Weight;
	int Count;
public:
	Item(Including_Materials m = {Materials::None, Materials::None}, int c = 0);
	~Item();
	void CalcWeight();
	void AddItems(int add = 1);
};

class Tool: public Item
{
protected:
	Tools ToolType;
	float Effiency = 0.5f;
	double Durability;
public:
	Tool(Tools t = Tools::NotTool, Including_Materials m = { Materials::None, Materials::None});
	~Tool();
	void CalcEffiency();
	void CalcDurability();
};

class Block: public Item
{
protected:
	Blocks BlockType;
public:
	Block(Blocks t = Blocks::NotBlock, int c);
	~Block();
	void DefineMaterials();
};






