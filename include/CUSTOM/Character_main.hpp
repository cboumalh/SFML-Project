#ifndef CHARACTER_MAIN_H
#define CHARACTER_MAIN_H


#include<iostream>
#include<ctime>
#include <vector>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Character{
    private:
        sf::Texture *textures;
        sf::Sprite sprite;
        unsigned int textureChoice;
        float movementSpeed;
        unsigned int currDirection;
        unsigned int nbrTextures;

        void initVariables();
        void initTextures();
        void initSprite();
        void initSpritePos();
        void updateSprite();
    
        
    public:
        Character();
        virtual ~Character();
            
        void update(const sf::RenderTarget *target);
        void render(sf::RenderTarget *target);
        
        const int whichTexture();
        void updateWindowBoundsCollision(const sf::RenderTarget *target);
        const sf::FloatRect getPlayerPos() const;
        void moveCharacter();
        sf::Sprite & getSprite();


};

#endif
