//Class that acts as game engine
#ifndef GAME_MAIN_HPP
#define GAME_MAIN_HPP

#include "Character_main.hpp"

class Game{

	private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        sf::View view;
        float width;
        float height;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

        bool endGame;
        sf::Event sfmlEvent;

        Character player;

        void initVariables();
        void initWindow();
        void initView();
        void initBackground();
        void renderBackground();
        void updateView();

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
