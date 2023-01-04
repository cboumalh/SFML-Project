#include "../../include/CUSTOM/Coin_main.hpp"
#include "../../include/CUSTOM/Character_main.hpp"


Coin::Coin(){
    this->initTexture();
    this->initSprite();
}


Coin::~Coin(){
 
}


const sf::Sprite & Coin::getSprite(){
    return this->sprite;
}


void Coin::render(sf::RenderTarget *target){
   target->draw(this->sprite); 
}

void Coin::updateSpritePos(const sf::RenderTarget* target){

    float random_x = rand() % static_cast<int>(target->getSize().x - 2 * this->sprite.getGlobalBounds().width) + static_cast<int>(this->sprite.getGlobalBounds().width);
    float random_y = rand() % static_cast<int>(target->getSize().y - 2 * this->sprite.getGlobalBounds().height) + static_cast<int>(this->sprite.getGlobalBounds().height);

    this->sprite.setPosition(random_x, random_y);
}

void Coin::initTexture(){
    if(!this->texture.loadFromFile("../textures/coin.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
}


void Coin::initSprite(){
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.1f, 0.1f);
    this->sprite.setPosition(50.f, 50.f);
}
