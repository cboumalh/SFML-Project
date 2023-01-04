#include "../../include/CUSTOM/Car_main.hpp"

Car::Car(const std::string texturePath, float x_pos, float y_pos, float carSpeed, const char direction){
    this->initVariables(x_pos, y_pos, carSpeed, direction);
    this->initTexture(texturePath);
    this->initSprite();
    this->initSpritePos();
}

Car::~Car(){
    //empty
}

void Car::initVariables(float &x_pos, float &y_pos, float &carSpeed, const char &direction){
    this->direction = direction;
    this->carSpeed = carSpeed;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->stopSprite = false;
}


void Car::initTexture(const std::string &texturePath){

    if(!this->texture.loadFromFile(texturePath))
        std::cout<<"TEXTURE DID NOT LOAD \n";
}


void Car::initSpritePos(){

    this->sprite.setPosition(this->x_pos, this->y_pos);

     if(this->direction == 'L'){
        this->sprite.rotate(-90.f);
    }
    else if(this->direction == 'R'){
        this->sprite.rotate(90.f);
    }
    else if(this->direction == 'U'){
        this->sprite.rotate(0.f);
    }
    else if(this->direction == 'D'){
        this->sprite.rotate(180.f);
    }
}


void Car::initSprite(){
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.3f, 0.3f);
    
}

void Car::updateSprite(){
    if(!this->stopSprite){
        if(this->direction == 'L'){
            this->sprite.move(-this->carSpeed, 0.f);
        }
        else if(this->direction == 'R'){
            this->sprite.move(this->carSpeed, 0.f);
        }
        else if(this->direction == 'U'){
            this->sprite.move(0.f, -this->carSpeed);
        }
        else if(this->direction == 'D'){
            this->sprite.move(0.f, this->carSpeed); 
        }
    }
}


void Car::update(const sf::RenderTarget* target){

    this->updateSprite();
    this->updateWindowBoundsCollision(target);

}

const sf::Sprite & Car::getSprite(){
    return this->sprite;
}

void Car::render(sf::RenderTarget* target){

    target->draw(this->sprite);
}

void Car::updateWindowBoundsCollision(const sf::RenderTarget *target){
    sf::FloatRect carBounds = this->sprite.getGlobalBounds();
    
    if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width <= 0.f && this->direction == 'L')
        this->sprite.setPosition(target->getSize().x, carBounds.top + carBounds.height); 

    else if(this->sprite.getGlobalBounds().left >= target->getSize().x && this->direction == 'R')
        this->sprite.setPosition(-this->sprite.getGlobalBounds().width, carBounds.top);

    else if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height <= 0.f && this->direction == 'U')
        this->sprite.setPosition(carBounds.left, target->getSize().y);

    else if(this->sprite.getGlobalBounds().top >= target->getSize().y && this->direction == 'D')
        this->sprite.setPosition(carBounds.left + carBounds.width, -this->sprite.getGlobalBounds().height);

}

const bool Car::checkCarCollision(Car &other_car) const{

    return this->sprite.getGlobalBounds().intersects(other_car.getSprite().getGlobalBounds());
}

const float Car::getCarSpeed() const {
    return this->carSpeed;
}

void Car::setStopSprite(bool value){
    this->stopSprite = value;
}


const float Car::getCarDirection() const {
    return this->direction;
}

const bool Car::isSpriteMoving() const{
    return this->stopSprite;
}
