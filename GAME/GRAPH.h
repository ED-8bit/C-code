#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "STRUCTS.h"
#include "ENTS.h"

void SET_GRID_TILES(int TILE_SIZE, std::vector<std::vector<tile>>& map, std::vector<sf::Texture> &subs, std::vector<sf::Texture>& floors, std::vector<std::vector<sf::RectangleShape>>& tiles);
void UPDATE_GRID_TILE(std::vector<std::vector<tile>>& map, std::vector<sf::Texture>& subs, std::vector<sf::Texture>& floors, std::vector<std::vector<sf::RectangleShape>>& tiles, point_int dot);
void DRAW_GRID(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles);

void SET_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RectangleShape& tile);
void UPDATE_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RenderWindow& w, sf::RectangleShape& tile);
void DRAW_PLAYER(sf::RenderWindow& w, sf::RectangleShape& tile);

void REFRESH_DISPLAY(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles, sf::RectangleShape& player);


//void SET_GRID_TILES(int TILE_SIZE, vector<vector<tile>>& map, vector<vector<sf::RectangleShape>>& tiles)
//{
//	const size_t MAP_WIDTH = map.size();
//	const size_t MAP_HEIGHT = map.size();
//	for (int x = 0; x < MAP_WIDTH; x++)
//	{
//		for (int y = 0; y < MAP_HEIGHT; y++)
//		{
//			sf::RectangleShape rect({ (float)TILE_SIZE, (float)TILE_SIZE });
//
//			rect.setPosition({ (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) });
//
//			sf::Color color;
//			if (!map[x][y].getSubject().getType())
//			{
//				if (map[x][y].getFloor().getType() == F_stone) {
//					color = sf::Color(61, 56, 56);      //stone
//				}
//				else if (map[x][y].getFloor().getType() == F_stone_spawn) {
//					color = sf::Color::Green; // SP
//				}
//				else if (map[x][y].getFloor().getType() == F_stone_exit) {
//					color = sf::Color::Black; // ESC
//				}
//				else {
//					color = sf::Color::Black;     // По умолчанию
//				}
//			}
//			else
//			{
//				if (map[x][y].getSubject().getType() == S_stone) {
//					color = sf::Color(44, 40, 43);
//				}
//				else if (map[x][y].getSubject().getType() == S_endstone) {
//					color = sf::Color(31, 31, 31);
//				}
//				else if (map[x][y].getSubject().getType() == S_ore) {
//					color = sf::Color(115, 83, 64);
//				}
//			}
//
//			rect.setFillColor(color);
//
//			//rect.setOutlineColor(sf::Color::Black);
//			//rect.setOutlineThickness(1.0f);
//
//
//			tiles[x][y] = rect;
//		}
//	}
//}