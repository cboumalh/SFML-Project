#include "../../include/CUSTOM/Game_main.hpp"


Game::~Game(){
    
    delete this->window;

}


Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initBackground();
}



void Game::initVariables(){
    if(!this->backgroundTexture.loadFromFile("../textures/background.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->endGame = false;
}

void Game::initWindow(){
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(140);

}

void Game::initBackground(){

    this->backgroundSprite.setScale(
        this->window->getSize().x / this->backgroundSprite.getLocalBounds().width,
        this->window->getSize().y / this->backgroundSprite.getLocalBounds().height
    );
}

void Game::renderBackground(){

    this->window->draw(this->backgroundSprite); 
}


void Game::render(){
    this->window->clear();

    this->renderBackground();

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


const bool & Game::getEndGame() const {
    return this->endGame;
}


