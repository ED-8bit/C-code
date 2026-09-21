#include <iostream>
#include "ENTS.h"
#include "WORLD.h"
#include "GRAPH.h"
#include <SFML/Graphics.hpp>
int MAPs = 0;
int ENTs = 0;
using namespace std;

void GAME(const float aspect, const unsigned int width)
{
	const int MAP_SIZE = 48;
	const int MAP_WIDTH = MAP_SIZE;
	const int MAP_HEIGHT = MAP_SIZE;
	const int TILE_SIZE = 16;

	const float ASPECT_RATIO = aspect;
	const float VIEW_WIDTH = 24.f * float(TILE_SIZE);
	const float VIEW_HEIGHT = VIEW_WIDTH / ASPECT_RATIO;

	const unsigned int GAME_W = MAP_WIDTH * TILE_SIZE;   
	const unsigned int GAME_H = MAP_HEIGHT * TILE_SIZE;   
	const unsigned int WIN_W = width;   
	const unsigned int WIN_H = (unsigned int)(WIN_W / ASPECT_RATIO);   

	//			\/ Textures \/
	int textures_size = 16;
	string textures_path = "assets/textures/SUBJECTS/CavePack.png";
	
	vector<sf::Texture> sub_tiles_pic;
	sub_tiles_pic.resize(3);
	for (int i = 0; i < 3; i++)
	{
		if (!sub_tiles_pic[i].loadFromFile(textures_path, false, sf::IntRect({ i * textures_size, 0 }, { textures_size, textures_size })))
			return;
	}
	vector<sf::Texture> floor_tiles_pic;
	floor_tiles_pic.resize(3);
	for (int i = 0; i < 3; i++)
	{
		if (!floor_tiles_pic[i].loadFromFile(textures_path, false, sf::IntRect({ i * textures_size, textures_size }, { textures_size, textures_size })))
			return;
	}
	//			/\ Textures /\

	//=============================================================================================================

	//			 \/ Window \/
	sf::RenderWindow window(sf::VideoMode({ WIN_W, WIN_H }), "Game", sf::Style::Default | sf::Style::Resize);
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	window.setMinimumSize(sf::Vector2u{ (unsigned)VIEW_WIDTH, (unsigned)VIEW_HEIGHT });
	//		     /\ Window /\
	
	//=============================================================================================================

	//			 \/ Camera \/
	sf::View camera(sf::FloatRect({ 0.f, 0.f }, { VIEW_WIDTH, VIEW_HEIGHT }));
	auto applyViewport = [&](unsigned int w, unsigned int h)
		{
			float winAspect = (float)w / (float)h;
			float vpX = 0.f, vpY = 0.f, vpW = 1.f, vpH = 1.f;

			if (winAspect > ASPECT_RATIO) { // Окно шире камеры -> полосы по бокам
				vpW = ASPECT_RATIO / winAspect;
				vpX = (1.f - vpW) * 0.5f;
			}
			else {                       // Окно выше камеры -> полосы сверху/снизу
				vpH = winAspect / ASPECT_RATIO;
				vpY = (1.f - vpH) * 0.5f;
			}
			camera.setViewport(sf::FloatRect({ vpX, vpY }, { vpW, vpH }));
		};
	applyViewport(WIN_W, WIN_H); 
	//			 /\ Camera /\

	//=============================================================================================================



	sf::Clock moveClock;
	sf::Clock breakClock;
	const float moveDelay = 0.0016f; 
	const float breakDelay = 0.57f;

	LEVEL game("Пещера", cave, rand(), MAP_SIZE);
	PLAYER p1(game, game.getSpawn(), "HELLBOUND", int(0.75*TILE_SIZE));

	vector<vector<sf::RectangleShape>> tiles(MAP_SIZE, vector<sf::RectangleShape>(MAP_SIZE, sf::RectangleShape()));
	sf::RectangleShape player_tile;
	SET_GRID_TILES(TILE_SIZE, game.getGrid(), sub_tiles_pic, floor_tiles_pic, tiles);
	SET_PLAYER_TILE(TILE_SIZE, p1, player_tile);


	while (window.isOpen())
	{
		// Обработка событий
		while (const optional<sf::Event> p_event = window.pollEvent())
		{
			if (p_event->is<sf::Event::Closed>())
			{
				window.close();
			}

			// Адаптивность окна и камера
			if (const sf::Event::Resized* resized = p_event->getIf<sf::Event::Resized>())
			{
				applyViewport(resized->size.x, resized->size.y);
			}

			// Обработка нажатия пробела для копания
			if (p_event->is<sf::Event::KeyPressed>())
			{
				auto keyEvent = p_event->getIf<sf::Event::KeyPressed>();
				if (keyEvent && keyEvent->code == sf::Keyboard::Key::Space)
				{
					if (breakClock.getElapsedTime().asSeconds() >= breakDelay)
					{
						if (p1.damage_sub_on_facing())
						{
							switch (p1.getFacing())
							{
							case 0: //north
								UPDATE_GRID_TILE(game.getGrid(), sub_tiles_pic, floor_tiles_pic, tiles, { int(p1.getPos().x), int(p1.getPos().y - 1) });
								break;
							case 1: //south
								UPDATE_GRID_TILE(game.getGrid(), sub_tiles_pic, floor_tiles_pic, tiles, { int(p1.getPos().x), int(p1.getPos().y + 1) });
								break;
							case 2: //west
								UPDATE_GRID_TILE(game.getGrid(), sub_tiles_pic, floor_tiles_pic, tiles, { int(p1.getPos().x - 1), int(p1.getPos().y) });
								break;
							case 3: //east
								UPDATE_GRID_TILE(game.getGrid(), sub_tiles_pic, floor_tiles_pic, tiles, { int(p1.getPos().x + 1), int(p1.getPos().y) });
								break;
							}
							breakClock.restart();
						}
					}
				}
			}
		}

		// Обработка передвижения
		if (moveClock.getElapsedTime().asSeconds() >= moveDelay)
		{
			bool moved = false;

			// Определяем направление движения
			bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
			bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
			bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
			bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

			// Диагональное движение
			if (up && left) {
				p1.move(north_west, TILE_SIZE);
				moved = true;
			}
			else if (up && right) {
				p1.move(north_east, TILE_SIZE);
				moved = true;
			}
			else if (down && left) {
				p1.move(south_west, TILE_SIZE);
				moved = true;
			}
			else if (down && right) {
				p1.move(south_east, TILE_SIZE);
				moved = true;
			}

			else if (left && right || up && down)
			{

			}

			// Обычное движение (только если нет диагонали)
			else if (up) {
				p1.move(north, TILE_SIZE);
				moved = true;
			}
			else if (down) {
				p1.move(south, TILE_SIZE);
				moved = true;
			}
			else if (left) {
				p1.move(west, TILE_SIZE);
				moved = true;
			}
			else if (right) {
				p1.move(east, TILE_SIZE);
				moved = true;
			}

			if (moved)
			{
				UPDATE_PLAYER_TILE(TILE_SIZE, p1, window, player_tile);
				moveClock.restart();
			}

			sf::Vector2f center = {
			(float)p1.getPos().x * TILE_SIZE + TILE_SIZE * 0.5f,
			(float)p1.getPos().y * TILE_SIZE + TILE_SIZE * 0.5f
			};

			float halfW = VIEW_WIDTH * 0.5f;
			float halfH = VIEW_HEIGHT * 0.5f;

			// Ограничение, чтобы камера не выходила за пределы карты
			if (GAME_W >= (unsigned)VIEW_WIDTH)
				center.x = clamp(center.x, halfW, (float)GAME_W - halfW);
			else
				center.x = (float)GAME_W * 0.5f;

			if (GAME_H >= (unsigned)VIEW_HEIGHT)
				center.y = clamp(center.y, halfH, (float)GAME_H - halfH);
			else
				center.y = (float)GAME_H * 0.5f;

			camera.setCenter(center);
			window.setView(camera); // Применяем изменения камеры
		}

		// Обновление экрана
		REFRESH_DISPLAY(window, tiles, player_tile);
	}
}

int main() {
	system("chcp 1251");
	srand(time(0));
	GAME(16.f / 9.f, 720);


	return 0;
}
