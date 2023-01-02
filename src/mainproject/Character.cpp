#include "../../include/CUSTOM/Character_main.hpp"

Character::Character(){
    
    this->initVariables();
    this->initTextures();
    this->initSprites();
    this->initSpritePos(400.f, 300.f);
}


Character::~Character(){
    

}


void Character::initVariables(){

    this->nbrSprites = 12;
    this->currDirection = 0;
    this->movementSpeed = 2.5;
    this->spriteChoice = 0;
    this->money = 0;


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


void Character::initSpritePos(const float x, const float y){
    
    for(int i = 0; i < this->nbrSprites; i++)
        this->sprites[i].setPosition(x, y);
    
}


void Character::initSprites(){
   
    for(int i = 0; i < this->nbrSprites; i++)
        this->sprites[i].setTexture(this->textures[i]);
    
}


void Character::update(const sf::RenderTarget* target){

    this->moveCharacter();        
    this->updateWindowBoundsCollision(target);
}

void Character::moveCharacter(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){    
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].move(-this->movementSpeed, 0.f);   
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].move(this->movementSpeed, 0.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].move(0.f, -this->movementSpeed);
    }  
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].move(0.f, this->movementSpeed);
    }

}



const int Character::whichSprite(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->currDirection = 6;

        if(this->spriteChoice == 0){
            this->spriteChoice += 1;
            return 6;
        }
        else if(this->spriteChoice == 1){
            this->spriteChoice += 1;
            return 7;
        }
        else {
            this->spriteChoice = 0;
            return 8;
        }
    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->currDirection = 9;

        if(this->spriteChoice == 0){
            this->spriteChoice += 1;
            return 9;
        }
        else if(this->spriteChoice == 1){
            this->spriteChoice += 1;
            return 10;
        }
        else {
            this->spriteChoice = 0;
            return 11;
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->currDirection = 3;
    
        if(this->spriteChoice == 0){
            this->spriteChoice += 1;
            return 3;
        }
        else if(this->spriteChoice == 1){
            this->spriteChoice += 1;
            return 4;
        }
        else{
            this->spriteChoice = 0;
            return 5;
        }    

    }
    
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->currDirection = 0;    
    
        if(this->spriteChoice == 0){
            this->spriteChoice += 1;
            return 0;
        } 
        else if(this->spriteChoice == 1){
            this->spriteChoice += 1;
            return 1;
        }
        else{
            this->spriteChoice = 0;
            return 2;
        }
    }
 
    return this->currDirection;
  
}



void Character::render(sf::RenderTarget *target){
   target->draw(this->sprites[this->whichSprite()]); 
}


void Character::updateWindowBoundsCollision(const sf::RenderTarget *target){
    sf::FloatRect playerBounds = this->sprites[this->whichSprite()].getGlobalBounds();
    
    if(this->sprites[this->whichSprite()].getGlobalBounds().left <= 0.f)
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].setPosition(0, playerBounds.top); 

    else if(this->sprites[this->whichSprite()].getGlobalBounds().left + this->sprites[this->whichSprite()].getGlobalBounds().width >= target->getSize().x)
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].setPosition(target->getSize().x - this->sprites[this->whichSprite()].getGlobalBounds().width, this->sprites[this->whichSprite()].getGlobalBounds().top);

    if(this->sprites[this->whichSprite()].getGlobalBounds().top <= 0.f)
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].setPosition(this->sprites[this->whichSprite()].getGlobalBounds().left, 0.f);

    else if(this->sprites[this->whichSprite()].getGlobalBounds().top + this->sprites[this->whichSprite()].getGlobalBounds().height >= target->getSize().y)
        for(int i = 0; i < this->nbrSprites; i++)
            this->sprites[i].setPosition(this->sprites[this->whichSprite()].getGlobalBounds().left, target->getSize().y - this->sprites[this->whichSprite()].getGlobalBounds().height);

}

const sf::FloatRect Character::getPlayerPos() const {
    return this->sprites[0].getGlobalBounds();
}





