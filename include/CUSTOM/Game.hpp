//Class that acts as game engine
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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

		//Resources
		sf::Font font;

		//Text
		sf::Text uiText;

		//Game logic
		bool endGame;
		unsigned points;
		int health;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies;
		bool mouseHeld;

		// Game objects
		sf::RectangleShape enemy;
		std::vector<sf::RectangleShape> enemies;
		
		void initVariables();
		void initWindow();
		void initText();
		void initEnemies();
		void initFonts();

	public:
		Game(); 

		virtual ~Game();

		//Accessors
		const bool running() const;
		const bool getEndGame() const;

		//functions
		void spawnEnemy();

		void pollEvents();
		void updateMousePositions();
		void updateText();
		void updateEnemies();
		void update();


		void render();
		void renderEnemies(sf::RenderTarget& target);
		void renderText(sf::RenderTarget& target);

};



#endif
