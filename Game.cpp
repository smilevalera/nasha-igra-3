#include <SFML/Graphics.hpp>
#include "Road.h"
#include "const.h"
#include "Game.h"
#include "barrier.h"
#include "Splash.h"

Game::Game() : window(sf::VideoMode(N* ts, M* ts), "Xonix Game!"),
player(500.f, 500.f), window_borders(sf::Vector2f(WINDOW_WIDTH - 35, WINDOW_HEIGHT - 35)),
splash_screen(SPLASH_FILE_NAME, 1.2f, 1.43f),

barrier1(600.f, -140.f),
barrier2(300.f, -200.f),
barrier3(100.f, -300.f),
barrier4(200.f, -400.f),
barrier5(700.f, -500.f),
barrier6(500.f, -WINDOW_HEIGHT / 2),
game_over_screen(FILE_OVER, 2.f, 3.f)//500 200

{
	
	window.setFramerateLimit(60);
	window_borders.setPosition(17,13);
	window_borders.setOutlineColor(sf::Color::Yellow);
	window_borders.setFillColor(sf::Color::Transparent);
	window_borders.setOutlineThickness(35);
}

void Game::play(){
	while (window.isOpen()) {
		check_event();
		update();
		check_collisions();
		draw();
		
	}
}

void Game::check_event() {

	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space && game_state == SPLASH) {
				game_state = PLAY;
			}

		}
	}
}
void Game::update() {
		switch (game_state) {
		case SPLASH:

			break;
		case PLAY:
			player.update();
			barrier1.update();
			barrier2.update();
			barrier3.update();
			barrier4.update();
			barrier5.update();
			barrier6.update();
			break;
		case GAME_OVER:
			break;
		}
		
	}
void Game::draw(){

	switch (game_state) {
		case SPLASH:
			window.clear(sf::Color::White);
			window.draw(splash_screen.getSprite());
		   break;
	
		case PLAY:
			road.draw(window);
			window.draw(window_borders);
			player.draw(window);
			barrier1.draw(window);
			barrier2.draw(window);
			barrier3.draw(window);
			barrier4.draw(window);
			barrier5.draw(window);
			barrier6.draw(window);
			break;
		case GAME_OVER:
			window.clear(sf::Color(150, 150, 150));
			window.draw(game_over_screen.getSprite());
			break;
		
	}
	

	window.display();



	

}
void Game::check_collisions() {
	if (player.getHitBox().intersects(barrier1.getHitBox()) ||
		player.getHitBox().intersects(barrier2.getHitBox()) ||
		player.getHitBox().intersects(barrier3.getHitBox()) ||
		player.getHitBox().intersects(barrier4.getHitBox()) ||
		player.getHitBox().intersects(barrier5.getHitBox()) ||
		player.getHitBox().intersects(barrier6.getHitBox()) 


		)
	{
		
		game_state = GAME_OVER;
	}
}

