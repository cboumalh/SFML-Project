#ifndef CAR_MAIN_H
#define CAR_MAIN_H

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Car{
    private:
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        Car();
        ~Car();



};




#endif