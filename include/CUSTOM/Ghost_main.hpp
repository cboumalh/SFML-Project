#ifndef GHOST_MAIN_H
#define GHOST_MAIN_H


#include<iostream>
#include<ctime>
#include<vector>
#include<cmath>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include "Character_main.hpp"


class Ghost{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        bool ghostActive;
        float ghostSpeed;
        Character *playerToFollow;
        
        void initTexture();
        void initSprite();
        void initVariables(Character *thePlayer);
        
    public:
        Ghost(Character *thePlayer);
        virtual ~Ghost();
            
        void updateSpritePos(Character *thePlayer);
        void render(sf::RenderTarget *target);
        const sf::Sprite & getSprite();
        const bool getActiveBool() const;
        void setActiveBool(bool value);

};

#endif
