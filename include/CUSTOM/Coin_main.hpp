#ifndef COIN_MAIN_H
#define COIN_MAIN_H


#include<iostream>
#include<ctime>
#include <vector>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Coin{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        
        void initTexture();
        void initSprite();
        
    public:
        Coin();
        virtual ~Coin();
            
        void updateSpritePos(const sf::RenderTarget* target);
        void render(sf::RenderTarget *target);
        const sf::Sprite & getSprite();

};

#endif
