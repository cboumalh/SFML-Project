#include "../../include/CUSTOM/Ball_2.hpp"


Ball::Ball(const sf::RenderWindow *window, int type){
    this->type = type;
    this->initShape(window);

}


Ball::~Ball(){

}


void Ball::initShape(const sf::RenderWindow *window){

    this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
    sf::Color color;

    switch (this->type){
        case DEFAULT:
            color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
            break;
        
        case DAMAGING:
            color = sf::Color::Red;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;

        case HEALING:
            color = sf::Color::Green;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;

    }


    this->shape.setPosition(sf::Vector2f(static_cast<float>(rand() % window->getSize().x - this->shape.getGlobalBounds().width), static_cast<float>(rand() % window->getSize().y - this->shape.getGlobalBounds().height)));
    
    this->shape.setFillColor(color);
}



void Ball::render(sf::RenderTarget *target){

    target->draw(this->shape);
}



const sf::CircleShape Ball::getShape() const {

    return this->shape;

}

const int & Ball::getType() const {
    return this->type;
}
