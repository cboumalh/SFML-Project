#include "../include/CUSTOM/Game.hpp"

//Private Functions
void Game::initVariables(){

    this->window == nullptr;

}

void Game::initWindow(){

    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "SFML Project", sf::Style::Titlebar | sf::Style::Close);

}

Game::Game(){

    this->initVariables();
    this->initWindow();

}

Game::~Game(){

    delete this->window;

}

void Game::update(){

    this->pollEvents();

}

void Game::pollEvents(){

    while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed || (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape))
            this->window->close();

	}


}

void Game::render(){

    this->window->clear(sf::Color(255, 0, 0, 255));

    //draw stuff below

    this->window->display();

}

const bool Game::running() const {
    return this->window->isOpen();
}
