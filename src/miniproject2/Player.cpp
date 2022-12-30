#include "../../include/CUSTOM/Player_2.hpp"

Player::Player(float x, float y){
    this->shape.setPosition(x,y);

    this->initVariables();
    this->initShape();

}


Player::~Player(){

}


void Player::initVariables(){
    this->movementSpeed = 5.f;
    this->hpMax = 10;
    this->hp = this->hpMax;


}


void Player::initShape(){
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}


void Player::update(const sf::RenderTarget* target){
        
   
    this->updateInput();

    this->updateWindowBoundsCollision(target);
}

void Player::updateInput(){


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->shape.move(-this->movementSpeed, 0.f);
    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->shape.move(this->movementSpeed, 0.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->shape.move(0.f, -this->movementSpeed);
    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->shape.move(0.f, this->movementSpeed);
    }

}

void Player::render(sf::RenderTarget *target){
    
    target->draw(this->shape);
}


void Player::updateWindowBoundsCollision(const sf::RenderTarget *target){
    sf::FloatRect playerBounds = this->shape.getGlobalBounds();
    
    if(this->shape.getGlobalBounds().left <= 0.f)
        this->shape.setPosition(0, playerBounds.top);

    else if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

    if(this->shape.getGlobalBounds().top <= 0.f)
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);

    else if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);

}

const sf::RectangleShape & Player::getShape() const {
    return this->shape;

}



const int & Player::getHp() const {
    return this->hp;
}

const int & Player::getHpMax() const {
    return this->hpMax;
}


void Player::takeDamage(const int damage){
    if(this->hp > 0)
        this->hp -= damage;

    if(this->hp < 0)
        this->hp = 0;
}


void Player::gainHealth(const int health){

    if(this->hp < this->hpMax)
        this->hp += health;

    if(this->hp > this->hpMax)
        this->hp = this->hpMax;

}







