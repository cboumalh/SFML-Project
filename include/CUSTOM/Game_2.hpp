//Class that acts as game engine
#ifndef GAME_2_HPP
#define GAME_2_HPP
#include "Player_2.hpp"

class Game{

	private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        bool endGame;
        sf::Event sfmlEvent;

        Player player;
    
    
        void initVariables();
        void initWindow();
	
	public:
        //Constructor and destructor
        Game();
        ~Game();


        //Accessors



        //Functions
        void update();
        void render();
        const bool running() const;
        void pollEvents();
        
        //Modifiers
    
		
};



#endif
