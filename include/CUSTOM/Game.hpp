//Class that acts as game engine
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game{

	private:
		sf::RenderWindow* window;
		sf::Event event;
		sf::VideoMode videoMode;

		//Mouse Position
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		int points;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies; 

		// Game objects
		sf::RectangleShape enemy;
		std::vector<sf::RectangleShape> enemies;
		
		void initVariables();
		void initWindow();
		void initEnemies();

	public:
		Game(); 

		virtual ~Game();

		//Accessors
		const bool running() const;

		//functions
		void spawnEnemy();
		void updateMousePositions();
		void updateEnemies();
		void update();
		void pollEvents();
		void render();
		void renderEnemies();


};



#endif
