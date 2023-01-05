#include "../../include/CUSTOM/Ghost_main.hpp"

Ghost::Ghost(Character *thePlayer){
    this->initTexture();
    this->initSprite();
    this->initVariables(thePlayer);
}

void Ghost::initVariables(Character *thePlayer){
    this->playerToFollow = thePlayer;
    this->ghostSpeed = 0.5f;
}


Ghost::~Ghost(){
 
}


const sf::Sprite & Ghost::getSprite(){
    return this->sprite;
}

//ghostActive is a bool to decide whether a collision between the player and the ghost will end the game or not
const bool Ghost::getActiveBool() const{
    return this->ghostActive;
}
void Ghost::setActiveBool(bool value){
    this->ghostActive = value;
}

void Ghost::render(sf::RenderTarget *target){
    target->draw(this->sprite);
}

// Make the ghost follow a player who's pointer is an argument. Basic vector arithmetic to for the math portion
void Ghost::updateSpritePos(Character *thePlayer){
    sf::Vector2f vPlayer(thePlayer->getSprite().getPosition());
    sf::Vector2f vGhost(this->sprite.getPosition());
    sf::Vector2f vGhostMoveDirection(vPlayer - vGhost);
    float vGhostMoveDirectionMagnitude = sqrt(vGhostMoveDirection.x * vGhostMoveDirection.x + vGhostMoveDirection.y * vGhostMoveDirection.y);

    this->sprite.move((vGhostMoveDirection.x / vGhostMoveDirectionMagnitude) * this->ghostSpeed, (vGhostMoveDirection.y / vGhostMoveDirectionMagnitude) * this->ghostSpeed);

}

void Ghost::initTexture(){
    if(!this->texture.loadFromFile("../textures/ghost.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
}


void Ghost::initSprite(){
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.15f, 0.15f);
    this->sprite.setColor(sf::Color(255,255,255,128));
    this->sprite.setPosition(20.f, 20.f);
}
