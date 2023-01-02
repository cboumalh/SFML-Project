#include "../../include/CUSTOM/Game_main.hpp"


Game::~Game(){
    
    delete this->window;

}


Game::Game(){
    this->initVariables();
    this->initView();
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
    this->window->setView(this->view);

}

void Game::initView(){
    this->view.setCenter(sf::Vector2f(400.f, 300.f));
    this->view.setSize(sf::Vector2f(400.f, 300.f));

}

void Game::updateView(){
    auto playerPos = this->player.getPlayerPos();

    if(playerPos.left <= 600 && playerPos.left >= 205 && playerPos.top <= 450 && playerPos.top >= 150)
        this->view.setCenter(playerPos.left, playerPos.top);
    else if(playerPos.left >= 600 && playerPos.top <= 450 && playerPos.top >= 150)
        this->view.setCenter(600, playerPos.top);
    else if(playerPos.left <= 205 && playerPos.top <= 450 && playerPos.top >= 150)
        this->view.setCenter(205, playerPos.top);
    else if(playerPos.top >= 450 && playerPos.left <= 600 && playerPos.left >= 205)
        this->view.setCenter(playerPos.left, 450);
    else if(playerPos.top <= 150 && playerPos.left <= 600 && playerPos.left >= 205)
        this->view.setCenter(playerPos.left, 150);


    this->window->setView(this->view);
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
    this->updateView();
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


