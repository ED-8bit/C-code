#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "STRUCTS.h"
#include "ENTS.h"

sf::Sprite CREATE_SPRITE(sf::Texture& Pic, point_double dot);
void CHANGE_SPRITE(sf::Sprite& spr, sf::Texture& NewPic, point_double dot = {NULL, NULL});
void DRAW_SPRITES(sf::RenderWindow& w, std::vector<sf::Sprite>& sprites);

void SET_GRID(int TILE_SIZE, std::vector<std::vector<tile>>& map, std::vector<sf::Texture> &subs, std::vector<sf::Texture>& floors, std::vector<std::vector<sf::RectangleShape>>& tiles);
void UPDATE_TILE(std::vector<std::vector<tile>>& map, std::vector<sf::Texture>& subs, std::vector<sf::Texture>& floors, std::vector<std::vector<sf::RectangleShape>>& tiles, point_int dot);
void DRAW_GRID(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles);

void SET_PLAYER(int TILE_SIZE, PLAYER& p, sf::RectangleShape& tile);
void UPDATE_PLAYER(int TILE_SIZE, PLAYER& p, sf::RenderWindow& w, sf::RectangleShape& tile);
void DRAW_PLAYER(sf::RenderWindow& w, sf::RectangleShape& tile);

void REFRESH_DISPLAY(sf::RenderWindow& w, std::vector<std::vector<sf::RectangleShape>>& tiles, std::vector<sf::Sprite>& sprites, sf::RectangleShape& player);