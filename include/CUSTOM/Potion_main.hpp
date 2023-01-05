#ifndef POTION_MAIN_H
#define POTION_MAIN_H


#include<iostream>
#include<ctime>
#include <vector>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Potion{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        bool potionActive;
        
        void initTexture();
        void initSprite();
        void initVariables();
        
    public:
        Potion();
        virtual ~Potion();
            
        void updateSpritePos(const sf::RenderTarget* target);
        void render(sf::RenderTarget *target);
        const sf::Sprite & getSprite();
        const bool getActiveBool() const;
        void setActiveBool(bool value);

};

#endif
