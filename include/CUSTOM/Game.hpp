//Class that acts as game engine
#ifndef GAME_HPP
#define GAME_HPP

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
		
		void initVariables();
		void initWindow();

	public:
		Game(); 

		virtual ~Game();

		//Accessors
		const bool running() const;

		//functions
		void update();
		void pollEvents();
		void render();

};



#endif
