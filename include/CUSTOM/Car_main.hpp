#ifndef CAR_MAIN_H
#define CAR_MAIN_H

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Car {

    private:
        sf::Sprite sprite;
        sf::Texture texture;
        float carSpeed;
        char direction;
        float x_pos;
        float y_pos;

        void initVariables(float &x_pos, float &y_pos, float &carSpeed, const char &direction);
        void initTexture(const std::string &texturePath);
        void initSpritePos();
        void initSprite();
        void updateSprite();

    public:
        Car(const std::string texturePath, float x_pos, float y_pos, float carSpeed, const char direction);
        ~Car();

        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget* target);
        void updateWindowBoundsCollision(const sf::RenderTarget *target);

};




#endif