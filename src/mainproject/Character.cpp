#include "../../include/CUSTOM/Character_main.hpp"

Character::Character(){
    
    this->initVariables();
    this->initTextures();
    this->initSprite();
    this->initSpritePos();
}

Character::~Character(){
    delete[] this->textures;
}


void Character::initVariables(){
    this->currDirection = 0;
    this->movementSpeed = 2.5f;
    this->textureChoice = 0;
    this->nbrTextures = 12;
    this->textures = new sf::Texture[this->nbrTextures];

}


void Character::initTextures(){
 
    if(!this->textures[0].loadFromFile("../textures/down_1.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[1].loadFromFile("../textures/down_2.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[2].loadFromFile("../textures/down_3.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";

 
    if(!this->textures[3].loadFromFile("../textures/up_1.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[4].loadFromFile("../textures/up_2.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[5].loadFromFile("../textures/up_3.png"))
        std::cout<<"TEXTURES DID NOT LOAD";

    if(!this->textures[6].loadFromFile("../textures/left_1.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[7].loadFromFile("../textures/left_2.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[8].loadFromFile("../textures/left_3.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";

    if(!this->textures[9].loadFromFile("../textures/right_1.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[10].loadFromFile("../textures/right_2.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    if(!this->textures[11].loadFromFile("../textures/right_3.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
}


void Character::initSpritePos(){
    float init_x = 200.f;
    float init_y = 200.f;

    this->sprite.setPosition(init_x, init_y);
    
}


void Character::initSprite(){
    this->sprite.setTexture(this->textures[0]);
    
}

void Character::updateSprite(){
    this->sprite.setTexture(this->textures[this->whichTexture()]);
}


void Character::update(const sf::RenderTarget* target){

    this->moveCharacter();
    this->updateSprite();
    this->updateWindowBoundsCollision(target);
}

void Character::moveCharacter(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->sprite.move(-this->movementSpeed, 0.f);   
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->sprite.move(this->movementSpeed, 0.f);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->sprite.move(0.f, -this->movementSpeed);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->sprite.move(0.f, this->movementSpeed);

}


const int Character::whichTexture(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->currDirection = 6;

        if(this->textureChoice == 0){
            this->textureChoice += 1;
            return 6;
        }
        else if(this->textureChoice == 1){
            this->textureChoice += 1;
            return 7;
        }
        else {
            this->textureChoice = 0;
            return 8;
        }
    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->currDirection = 9;

        if(this->textureChoice == 0){
            this->textureChoice += 1;
            return 9;
        }
        else if(this->textureChoice == 1){
            this->textureChoice += 1;
            return 10;
        }
        else {
            this->textureChoice = 0;
            return 11;
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->currDirection = 3;
    
        if(this->textureChoice == 0){
            this->textureChoice += 1;
            return 3;
        }
        else if(this->textureChoice == 1){
            this->textureChoice += 1;
            return 4;
        }
        else{
            this->textureChoice = 0;
            return 5;
        }    

    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->currDirection = 0;    
    
        if(this->textureChoice == 0){
            this->textureChoice += 1;
            return 0;
        } 
        else if(this->textureChoice == 1){
            this->textureChoice += 1;
            return 1;
        }
        else{
            this->textureChoice = 0;
            return 2;
        }
    }
 
    return this->currDirection;
  
}



void Character::render(sf::RenderTarget *target){
   target->draw(this->sprite); 
}


void Character::updateWindowBoundsCollision(const sf::RenderTarget *target){
    sf::FloatRect playerBounds = this->sprite.getGlobalBounds();
    
    if(this->sprite.getGlobalBounds().left <= 0.f)
        this->sprite.setPosition(0, playerBounds.top); 

    else if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
        this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);

    if(this->sprite.getGlobalBounds().top <= 0.f)
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);

    else if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);

}

const sf::FloatRect Character::getPlayerPos() const {
    return this->sprite.getGlobalBounds();
}

const sf::Sprite & Character::getSprite(){
    return this->sprite;
}



