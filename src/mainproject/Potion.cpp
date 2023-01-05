#include "../../include/CUSTOM/Potion_main.hpp"
#include "../../include/CUSTOM/Character_main.hpp"


Potion::Potion(){
    this->initTexture();
    this->initSprite();
    this->potionActive = false;
}


Potion::~Potion(){
 
}


const sf::Sprite & Potion::getSprite(){
    return this->sprite;
}

sf::Clock & Potion::getClock(){
    return this->clock;
}


const bool Potion::getActiveBool() const{
    return this->potionActive;
}

void Potion::setActiveBool(bool value){
    this->potionActive = value;
}

void Potion::render(sf::RenderTarget *target){
    if(this->clock.getElapsedTime().asSeconds() > 20.f){
        this->potionActive = true;
        target->draw(this->sprite);
    }
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
    this->sprite.setPosition(100.f, 100.f);
}
