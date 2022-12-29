//Class that acts as game engine
#ifndef GAME_2_HPP
#define GAME_2_HPP
#include <vector>
#include <sstream>
#include "Player_2.hpp"
#include "Ball_2.hpp"

class Game{

	private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        bool endGame;
        sf::Event sfmlEvent;
        int points;

        Player player;
    
        sf::Font font;
        sf::Text guiText;   
 
        void initVariables();
        void initWindow();

        std::vector<Ball> balls;
        float spawnTimerMax;
        float spawnTimer;
        int maxNbrBalls;

        int initFont();
        void initText();

	
	public:
        //Constructor and destructor
        Game();
        ~Game();


        //Accessors
        const bool &getEndGame() const;

        //Functions
        void update();
        void render();
        void spawnBalls();
        void updateCollision();
        void updateGui();
        const int randBallType() const;
        void updatePlayer();
        const bool running() const;
        void pollEvents();
        void renderGui(sf::RenderTarget *target); 
        //Modifiers
    
		
};



#endif
