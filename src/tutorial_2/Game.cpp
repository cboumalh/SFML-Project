#include "../../include/CUSTOM/Game_2.hpp"



Game::~Game(){
    
    delete this->window;

}



Game::Game(){
    this->initVariables();
    this->initWindow();
}



void Game::initVariables(){
    this->endGame = false;
}


void Game::initWindow(){
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);

}


void Game::render(){

}


void Game::update(){

}



