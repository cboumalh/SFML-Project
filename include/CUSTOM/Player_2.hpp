#ifndef PLAYER_2_H
#define PLAYER_2_H


#include<iostream>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Player{
    private:
        sf::RectangleShape shape;
    
        float movementSpeed;

        void initVariables();
        void initShape();

    public:
        Player(float xi = 0.f, float y = 0.f);
        virtual ~Player();


        void updateInput();
        void updateWindowBoundsCollision(const sf::RenderTarget *target);
        void update(const sf::RenderTarget *target);
        void render(sf::RenderTarget *target);



};

#endif
