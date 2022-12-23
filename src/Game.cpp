#include "../include/CUSTOM/Game.hpp"

//Private Functions
void Game::initVariables(){

    this->window == nullptr;

}

void Game::initWindow(){

    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "SFML Project", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144);

}

void Game::initEnemies(){
    // Vector2f is 
    this->enemy.setPosition(10.f, 10.f); //units are pixels
    this->enemy.setSize(sf::Vector2f(100.f, 100.f)); // .f signifies its a float val not a double or int
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}


Game::Game(){

    this->initVariables();
    this->initWindow();
    this->initEnemies();

}

Game::~Game(){

    delete this->window;

}

void Game::update(){

    this->pollEvents();

    // relative to screen
    std::cout<< "Mouse pos: " << sf::Mouse::getPosition().x << " " <<  sf::Mouse::getPosition().y << "\n";

    //relative to window
    std::cout<< "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " <<  sf::Mouse::getPosition(*this->window).y << "\n";

}

void Game::pollEvents(){

    while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed || (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape))
            this->window->close();

	}


}

void Game::render(){

    this->window->clear();

    //draw stuff below
    this->window->draw(this->enemy);

    this->window->display();

}

const bool Game::running() const {
    return this->window->isOpen();
}
