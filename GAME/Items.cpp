#include "Items.h"

Item::Item(Including_Materials m, int c) : Materials(m), Count(c) {
	CalcWeight();
}
Item::~Item() {}
void Item::CalcWeight(){
	double a, b;
	switch(Materials.primary)
	{
	case Materials::None:
		a = 0;
		break;
	case Materials::Wood:
		a = 4.5;
		break;
	case Materials::Stone:
		a = 9;
		break;
	case Materials::Iron:
		a = 9;
		break;
	default:
		a = 10;
	}
	switch (Materials.secondary)
	{
	case Materials::None:
		b = 0;
		break;
	case Materials::Wood:
		b = 3;
		break;
	case Materials::Stone:
		b = 6;
		break;
	case Materials::Iron:
		b = 5;
		break;
	default:
		b = 6.5;
	}
	Weight = (a + b)*Count;
}
void Item::AddItems(int add) {
	Count += add;
	CalcWeight();
}


Tool::Tool(Tools t, Including_Materials m): ToolType(t), Item(m, 1){
	CalcEffiency();
	CalcDurability();
	CalcWeight();
}
Tool::~Tool(){}
void Tool::CalcEffiency() {
	switch (Materials.primary)
	{
	case Materials::None:
		Effiency = 1.0f;
		break;
	case Materials::Wood:
		Effiency = 1.2f;
		break;
	case Materials::Stone:
		Effiency = 2.1f;
		break;
	case Materials::Iron:
		Effiency = 4.0f;
		break;
	default:
		Effiency = 1.0f;
	}

}
void Tool::CalcDurability(){
	double a, b;
	switch (Materials.primary)
	{
	case Materials::None:
		a = 0;
		break;
	case Materials::Wood:
		a = 4.5;
		break;
	case Materials::Stone:
		a = 9;
		break;
	case Materials::Iron:
		a = 9;
		break;
	default:
		a = 10;
	}
	switch (Materials.secondary)
	{
	case Materials::None:
		b = 0;
		break;
	case Materials::Wood:
		b = 3;
		break;
	case Materials::Stone:
		b = 6;
		break;
	case Materials::Iron:
		b = 5;
		break;
	default:
		b = 6.5;
	}
	Durability = a * 15 + b * 8;
}

Block::Block(Blocks t, int c): BlockType(t){
	DefineMaterials();
	CalcWeight();
}
Block::~Block(){}
void Block::DefineMaterials(){
	switch (BlockType)
	{
	case Blocks::NotBlock:
		Materials.primary = Materials::None;
		Materials.secondary = Materials::None;
		break;
	case Blocks::Cobblestone:
		Materials.primary = Materials::Stone;
		Materials.secondary = Materials::Stone;
		break;
	case Blocks::Stone:
		Materials.primary = Materials::Stone;
		Materials.secondary = Materials::Stone;
		break;
	case Blocks::Ore:
		Materials.primary = Materials::Iron;
		Materials.secondary = Materials::Iron;
		break;
	}
}

