#include "GRAPH.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "WORLD.h"
#include "ENTS.h"

using namespace std;


void SET_GRID_TILES(int TILE_SIZE, vector<vector<tile>>& map, std::vector<sf::Texture>& subs, std::vector<sf::Texture> &floors, vector<vector<sf::RectangleShape>>& tiles)
{
	const size_t MAP_WIDTH = map.size();
	const size_t MAP_HEIGHT = map[0].size();
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			tiles[x][y].setSize({ (float)TILE_SIZE, (float)TILE_SIZE });

			tiles[x][y].setPosition({ (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) });

			sf::Texture *pic = nullptr;
			if (!map[x][y].getSubject().getType())
			{
				if (map[x][y].getFloor().getType() == F_stone) {
					pic = &floors[0];      //stone
				}
				else if (map[x][y].getFloor().getType() == F_stone_exit) {
					pic = &floors[1]; // ESC
				}
				else if (map[x][y].getFloor().getType() == F_stone_spawn) {
					pic = &floors[2]; // SP
				}
				else {
					tiles[x][y].setFillColor(sf::Color::Black); // По умолчанию
				}
				tiles[x][y].setTexture(pic);
			}
			else
			{
				if (map[x][y].getSubject().getType() == S_stone) {
					pic = &subs[0];
				}
				else if (map[x][y].getSubject().getType() == S_ore) {
					pic = &subs[1];
				}
				else if (map[x][y].getSubject().getType() == S_endstone) {
					pic = &subs[2];
				}
				tiles[x][y].setTexture(pic);
			}
			//tiles[x][y].setOutlineColor(sf::Color::Black);
			//tiles[x][y].setOutlineThickness(0.1f);
		}
	}
}
void UPDATE_GRID_TILE(vector<vector<tile>>& map, std::vector<sf::Texture>& subs, std::vector<sf::Texture>& floors, vector<vector<sf::RectangleShape>>& tiles, point_int dot)
{
	int x = dot.x;
	int y = dot.y;
	sf::Texture* pic = nullptr;
	if (!map[x][y].getSubject().getType())
	{
		if (map[x][y].getFloor().getType() == F_stone) {
			pic = &floors[0];      //stone
		}
		else if (map[x][y].getFloor().getType() == F_stone_spawn) {
			pic = &floors[1]; // SP
		}
		else if (map[x][y].getFloor().getType() == F_stone_exit) {
			pic = &floors[2]; // ESC
		}
		else {
			tiles[x][y].setFillColor(sf::Color::Black); // По умолчанию
		}
		tiles[x][y].setTexture(pic);
	}
	else
	{
		if (map[x][y].getSubject().getType() == S_stone) {
			pic = &subs[0];
		}
		else if (map[x][y].getSubject().getType() == S_ore) {
			pic = &subs[1];
		}
		else if (map[x][y].getSubject().getType() == S_endstone) {
			pic = &subs[2];
		}
		tiles[x][y].setTexture(pic);
	}
	//tiles[x][y].setOutlineColor(sf::Color::Black);
	//tiles[x][y].setOutlineThickness(0.5f);

}
void DRAW_GRID(sf::RenderWindow& w, vector<vector<sf::RectangleShape>>& tiles)
{
	size_t size = tiles.size();
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			w.draw(tiles[x][y]);
}

void SET_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RectangleShape& tile)
{
	sf::RectangleShape rect({ (float)p.getSize(), (float)p.getSize() });
	rect.setOrigin({ float(p.getSize() / 2), float(p.getSize() / 2) });
	rect.setPosition({ (float)((p.getPos().x) * TILE_SIZE), (float)((p.getPos().y) * TILE_SIZE) });

	sf::Color color(180, 32, 32);
	rect.setFillColor(color);
	tile = rect;
}
void UPDATE_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RenderWindow& w, sf::RectangleShape& tile)
{
	tile.setPosition({ (float)((p.getPos().x) * TILE_SIZE), (float)((p.getPos().y) * TILE_SIZE) });
}
void DRAW_PLAYER(sf::RenderWindow& w, sf::RectangleShape& tile)
{
	w.draw(tile);
}

void REFRESH_DISPLAY(sf::RenderWindow& w, vector<vector<sf::RectangleShape>>& tiles, sf::RectangleShape& player)
{
	w.clear();
	DRAW_GRID(w, tiles);
	DRAW_PLAYER(w, player);
	w.display();
}

