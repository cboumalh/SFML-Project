//Class that acts as game engine
#ifndef GAME_2_HPP
#define GAME_2_HPP
#include <vector>
#include "Player_2.hpp"
#include "Ball_2.hpp"

class Game{

	private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        bool endGame;
        sf::Event sfmlEvent;

        Player player;
    
    
        void initVariables();
        void initWindow();
        std::vector<Ball> balls;
        float spawnTimerMax;
        float spawnTimer;
        int maxNbrBalls;

	
	public:
        //Constructor and destructor
        Game();
        ~Game();


        //Accessors



        //Functions
        void update();
        void render();
        void spawnBalls();
        const bool running() const;
        void pollEvents();
        
        //Modifiers
    
		
};



#endif
