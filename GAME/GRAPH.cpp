#include "GRAPH.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "WORLD.h"
#include "ENTS.h"

using namespace std;

void SET_GRID_TILES(int TILE_SIZE, vector<vector<tile>>& map, vector<vector<sf::RectangleShape>>& tiles)
{
	const int MAP_WIDTH = map.size();
	const int MAP_HEIGHT = map.size();
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			sf::RectangleShape rect({ (float)TILE_SIZE, (float)TILE_SIZE });

			rect.setPosition({ (float)(x * TILE_SIZE), (float)(y * TILE_SIZE) });

			sf::Color color;
			if (!map[x][y].subject)
			{
				if (map[x][y].floor == 1) {
					color = sf::Color(61, 56, 56);      //stone
				}
				else if (map[x][y].floor == 2) {
					color = sf::Color(209, 83, 10); //lava
				}
				else if (map[x][y].floor == 3) {
					color = sf::Color::Green; // SP
				}
				else if (map[x][y].floor == 4) {
					color = sf::Color::Black; // ESC
				}
				else {
					color = sf::Color::Black;     // По умолчанию
				}
			}
			else
			{
				if (map[x][y].subject == 1) {
					color = sf::Color(44, 40, 43);
				}
				else if (map[x][y].subject == 2) {
					color = sf::Color(31, 31, 31);
				}
				else if (map[x][y].subject == 3) {
					color = sf::Color(115, 83, 64);
				}
			}

			rect.setFillColor(color);

			//rect.setOutlineColor(sf::Color::Black);
			//rect.setOutlineThickness(1.0f);


			tiles[x][y] = rect;
		}
	}
}
void UPDATE_GRID_TILE(vector<vector<tile>>& map, vector<vector<sf::RectangleShape>>& tiles, point_int dot)
{
	int x = dot.x;
	int y = dot.y;
	sf::Color color;
	if (!map[x][y].subject)
	{
		if (map[x][y].floor == 1) {
			color = sf::Color(61, 56, 56);      //stone
		}
		else if (map[x][y].floor == 2) {
			color = sf::Color(209, 83, 10); //lava
		}
		else if (map[x][y].floor == 3) {
			color = sf::Color::Green; // SP
		}
		else if (map[x][y].floor == 4) {
			color = sf::Color::Black; // ESC
		}
		else {
			color = sf::Color::Black;     // По умолчанию
		}
	}
	else
	{
		if (map[x][y].subject == 1) {
			color = sf::Color(44, 40, 43);
		}
		else if (map[x][y].subject == 2) {
			color = sf::Color(31, 31, 31);
		}
		else if (map[x][y].subject == 3) {
			color = sf::Color(115, 83, 64);
		}
	}
	tiles[x][y].setFillColor(color);

}
void DRAW_GRID(sf::RenderWindow& w, vector<vector<sf::RectangleShape>>& tiles)
{
	int size = tiles.size();
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			w.draw(tiles[x][y]);
}

void SET_PLAYER_TILE(int TILE_SIZE, PLAYER& p, sf::RectangleShape& tile)
{
	sf::RectangleShape rect({ (float)p.getSize(), (float)p.getSize() });
	rect.setOrigin({ float(TILE_SIZE / 2), float(TILE_SIZE / 2) });
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