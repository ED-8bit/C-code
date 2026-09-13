#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "STRUCTS.h"
#include "ENTS.h"
struct texture {
	std::string name;
	sf::Texture picture;

	texture(std::string n, sf::Texture pic) : name(n), picture(pic) {}
};

void SET_GRID_TILES(int TILE_SIZE, std::vector<std::vector<tile>>& map, std::vector<std::vector<sf::RectangleShape>>& tiles);
void UPDATE_GRID_TILE(std::vector<std::vector<tile>>& map, std::vector<std::vector<sf::RectangleShape>>& tiles, point_int dot);
void DRAW_GRID(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles);

void SET_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RectangleShape& tile);
void UPDATE_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RenderWindow& w, sf::RectangleShape& tile);
void DRAW_PLAYER(sf::RenderWindow& w, sf::RectangleShape& tile);

void REFRESH_DISPLAY(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles, sf::RectangleShape& player);

class TILE_TEXTURES
{
private:
	std::vector<std::vector<texture>> data;
public:
	TILE_TEXTURES();
	~TILE_TEXTURES();

};

