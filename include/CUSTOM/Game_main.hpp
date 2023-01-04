//Class that acts as game engine
#ifndef GAME_MAIN_HPP
#define GAME_MAIN_HPP

#define SFML_AUDIO_PROVIDES_MP3_DECODER
#include "Character_main.hpp"
#include "Car_main.hpp"
#include "Coin_main.hpp"


class Game{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow *window;
        sf::View view;
        float width;
        float height;
        unsigned int points;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Font font;
	    sf::Text guiText;
	    sf::Text endGameText;

        bool endGame;
        sf::Event sfmlEvent;
        sf::Clock clock;
        sf::Music highwaySound;
        sf::SoundBuffer buffer;
        sf::Sound coinSound;

        Character *player;
        std::vector<Car*> cars;
        Coin *coin;

        void initVariables();
        void initWindow();
        void initView();
        void initCoin();
        void initCars();
        void initText();
        void initFonts();
        void initPlayer();
        void initCoinSound();
        void initBackgroundSprite();
        void initBackgroundTexture();
        void renderBackground();
        void initHighwaySound();
        void updateView();
        void handleVerticalCarCollisions();
        void handleHorizontalCarCollisions();
        void CharacterCarCollided();
        void updateGui();
        void renderGui(sf::RenderTarget* target);
        void updateEndGameText();
        void updatePlayerCoinCollision();
        void speedUpGame();
        void stopHighwaySound();
        
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
