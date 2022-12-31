//Class that acts as game engine
#ifndef GAME_MAIN_HPP
#define GAME_MAIN_HPP

#include "Character_main.hpp"

class Game{

	private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        bool endGame;
        sf::Event sfmlEvent;
        Character player;

        void initVariables();
        void initWindow();

	public:

        Game();
        ~Game();


  
        const bool &getEndGame() const;


        void update();
        void render();
        const bool running() const;
        void pollEvents();

    
		
};



#endif
