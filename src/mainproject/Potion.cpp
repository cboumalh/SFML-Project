#include "../../include/CUSTOM/Potion_main.hpp"


Potion::Potion(){
    this->initTexture();
    this->initSprite();
    this->initVariables();
}

void Potion::initVariables(){
    this->potionActive = false;
}


Potion::~Potion(){
 
}


const sf::Sprite & Potion::getSprite(){
    return this->sprite;
}


const bool Potion::getActiveBool() const{
    return this->potionActive;
}

void Potion::setActiveBool(bool value){
    this->potionActive = value;
}

void Potion::render(sf::RenderTarget *target){
    target->draw(this->sprite);
    
}

void Potion::updateSpritePos(const sf::RenderTarget* target){

    float random_x = rand() % static_cast<int>(target->getSize().x - 2 * this->sprite.getGlobalBounds().width) + static_cast<int>(this->sprite.getGlobalBounds().width);
    float random_y = rand() % static_cast<int>(target->getSize().y - 2 * this->sprite.getGlobalBounds().height) + static_cast<int>(this->sprite.getGlobalBounds().height);

    this->sprite.setPosition(random_x, random_y);
}

void Potion::initTexture(){
    if(!this->texture.loadFromFile("../textures/potion.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
}


void Potion::initSprite(){
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.15f, 0.15f);
    this->sprite.setPosition(70.f, 70.f);
}
