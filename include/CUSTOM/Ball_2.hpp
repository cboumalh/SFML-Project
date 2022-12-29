#ifndef BALL_2_H
#define BALL_2_H


#include<iostream>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

enum ballTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class Ball{
    private:
        sf::CircleShape shape;
        int type;

        void initShape(const sf::RenderWindow *window);  
    public:
        Ball(const sf::RenderWindow *window, int type);
        virtual ~Ball();


        void update();
        void render(sf::RenderTarget *target);

        const sf::CircleShape getShape() const;
        const int& getType() const;


};

#endif
