#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "STRUCTS.h"
#include "ENTS.h"

//class SpriteManager
//{
//private:
//	std::vector<std::vector<sf::Sprite>> data[3]; // data[n]  -> Слои ДЛЯ РАБОТЫ
//	int FieldSize;
//
//	bool outlayer(int l); //Проверка Выхода за предел слоев сетки. actual_layers -> Слои ДЛЯ ПРОВЕРКИ
//	bool outBorder(point_int dot); // Проверка Выхода за горизонтальные пределы сетки
//	bool outData(point_int dot, int l); // Проверка Выхода за пределы структуры
//public:
//	SpriteManager(int Map_Size);
//	~SpriteManager();
//
//	void CREATE_SPRITE(sf::Texture& Pic, point_int dot, int layer);
//	void CHANGE_SPRITE(point_int dot, int l, sf::Texture& NewPic, point_int NewDot = { -1, -1 }, int NewL = -1);
//};
void DRAW_SPRITES(sf::RenderWindow& w, std::vector<sf::Sprite>& sprites);

void SET_GRID(int TILE_SIZE, std::vector<std::vector<tile>>& map, std::vector<sf::Texture> &subs, std::vector<sf::Texture>& floors, std::vector<std::vector<sf::RectangleShape>>& tiles);
void UPDATE_TILE(std::vector<std::vector<tile>>& map, std::vector<sf::Texture>& subs, std::vector<sf::Texture>& floors, std::vector<std::vector<sf::RectangleShape>>& tiles, point_int dot);
void DRAW_GRID(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles);

void SET_PLAYER(int TILE_SIZE, PLAYER& p, sf::RectangleShape& tile);
void UPDATE_PLAYER(int TILE_SIZE, PLAYER& p, sf::RenderWindow& w, sf::RectangleShape& tile);
void DRAW_PLAYER(sf::RenderWindow& w, sf::RectangleShape& tile);

void REFRESH_DISPLAY(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles,
	std::vector<sf::Sprite>& sprites, sf::RectangleShape& player);