#include "../../include/CUSTOM/Game_main.hpp"


Game::~Game(){
    delete this->window;
    delete this->player;
}


Game::Game(){
    this->initVariables();
    this->initBackgroundTexture();
    this->initView();
    this->initWindow();
    this->initBackgroundSprite();
}



void Game::initVariables(){
    this->width = 800.f;
    this->height = 600.f;
    this->endGame = false;
    this->player = new Character();
    this->cars.push_back(new Car("../textures/car_1.png", 415.f, 800.f, 1.5f, 'U'));
    this->cars.push_back(new Car("../textures/car_2.png", 350.f, 0.f, 1.5f, 'D'));
    this->cars.push_back(new Car("../textures/car_3.png", 0.f, 350.f, 1.5f, 'R'));
    this->cars.push_back(new Car("../textures/car_4.png", 600.f, 300.f, 1.5f, 'L'));

}

void Game::initBackgroundTexture(){
    if(!this->backgroundTexture.loadFromFile("../textures/background.png"))
        std::cout<<"TEXTURE DID NOT LOAD \n";
}

void Game::initWindow(){
    this->videoMode = sf::VideoMode(this->width, this->height);
    this->window = new sf::RenderWindow(this->videoMode, "Traffic Survival!", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(140);
    this->window->setView(this->view);

}

void Game::initView(){
    this->view.setCenter(sf::Vector2f(this->width - this->player->getPlayerPos().width / 2.f, this->height - this->player->getPlayerPos().height / 2.f));
    this->view.setSize(sf::Vector2f(this->width / 2.f , this->height / 2.f));

}

void Game::updateView(){
    auto playerPos = this->player->getPlayerPos();
    auto half_window_height = this->height / 4.f;
    auto half_window_width = this->width / 4.f;

    if(playerPos.left <= this->width - half_window_width && playerPos.left >= half_window_width && playerPos.top <= this->height - half_window_height && playerPos.top >= half_window_height)
        this->view.setCenter(playerPos.left, playerPos.top);
    else if(playerPos.left >= this->width - half_window_width && playerPos.top <= this->height - half_window_height && playerPos.top >= half_window_height)
        this->view.setCenter(this->width - half_window_width, playerPos.top);
    else if(playerPos.left <= half_window_width && playerPos.top <= this->height - half_window_height && playerPos.top >= half_window_height)
        this->view.setCenter(half_window_width, playerPos.top);
    else if(playerPos.top >= this->height - half_window_height && playerPos.left <= this->width - half_window_width && playerPos.left >= half_window_width)
        this->view.setCenter(playerPos.left, this->height - half_window_height);
    else if(playerPos.top <= half_window_height && playerPos.left <= this->width - half_window_width && playerPos.left >= half_window_width)
        this->view.setCenter(playerPos.left, half_window_height);


    this->window->setView(this->view);
}

void Game::initBackgroundSprite(){
    this->backgroundSprite.setTexture(this->backgroundTexture);

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

    for(auto &car : this->cars)
        car->render(this->window);

    this->player->render(this->window);

    this->window->display();

}


void Game::update(){

    this->pollEvents();
    for(auto &car : this->cars)
        car->update(this->window);
    this->player->update(this->window);
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


