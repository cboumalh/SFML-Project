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

    this->window->setFramerateLimit(60);

}


void Game::render(){
    this->window->clear();

    this->player.render(this->window);

    this->window->display();

}


void Game::update(){
    this->pollEvents();
    
    this->player.update(this->window);
}


const bool Game::running() const{

    return this->window->isOpen();
}


void Game::pollEvents(){
    
    while(this->window->pollEvent(this->sfmlEvent)){
        if(this->sfmlEvent.type == sf::Event::Closed || (this->sfmlEvent.type == sf::Event::KeyPressed && this->sfmlEvent.key.code == sf::Keyboard::Escape))
        this->window->close();
    }
}



