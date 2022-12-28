//Class that acts as game engine
#ifndef GAME_2_HPP
#define GAME_2_HPP

#include<iosteam>
#include<ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game{

	private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        bool endGame;
    
    
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
        
        //Modifiers
    
		
};



#endif
