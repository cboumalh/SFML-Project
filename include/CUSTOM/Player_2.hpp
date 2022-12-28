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

        void initVariables();
        void initShape();

    public:
        Player();
        virtual ~Player();



        void update();
        void render(sf::RenderTarget *target);



};

#endif
