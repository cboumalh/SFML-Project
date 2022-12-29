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
        int hp;
        int hpMax; 
        float movementSpeed;

        void initVariables();
        void initShape();

    public:
        Player(float xi = 0.f, float y = 0.f);
        virtual ~Player();

            
        const sf::RectangleShape& getShape() const;
        const int & getHp() const;
        const int & getHpMax() const;

        void takeDamage(const int damage);
        void gainHealth(const int health);
    
        void updateInput();
        void updateWindowBoundsCollision(const sf::RenderTarget *target);
        void update(const sf::RenderTarget *target);
        void render(sf::RenderTarget *target);



};

#endif
