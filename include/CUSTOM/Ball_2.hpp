#ifndef BALL_2_H
#define BALL_2_H


#include<iostream>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Ball{
    private:
        sf::CircleShape shape;

        void initShape(const sf::RenderWindow *window);  
    public:
        Ball(const sf::RenderWindow *window);
        virtual ~Ball();


        void update();
        void render(sf::RenderTarget *target);



};

#endif
