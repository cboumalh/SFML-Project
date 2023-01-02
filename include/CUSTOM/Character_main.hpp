#ifndef CHARACTER_MAIN_H
#define CHARACTER_MAIN_H


#include<iostream>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Character{
    private:
        sf::Texture textures[12];
        sf::Sprite sprites[12];
        int nbrSprites;
        int money;
        int spriteChoice;
        float movementSpeed;
        int currDirection;

        void initVariables();
        void initTextures();
        void initSprites();
        void initSpritePos(const float x, const float y);

    public:
        Character();
        virtual ~Character();
            
        void update(const sf::RenderTarget *target);
        void render(sf::RenderTarget *target);
        
        const int whichSprite();
        void updateWindowBoundsCollision(const sf::RenderTarget *target);
        void setPos(const int spriteIndex, const float x, const float y);
        const sf::FloatRect  getPlayerPos() const;
        void moveCharacter();



};

#endif
