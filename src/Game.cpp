#include "../include/CUSTOM/Game.hpp"

//Private Functions
void Game::initVariables(){

    this->window = nullptr;

    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;



}

void Game::initWindow(){

    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "SFML Project", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);

}

void Game::initEnemies(){
    // Vector2f is 
    this->enemy.setPosition(10.f, 10.f); //units are pixels
    this->enemy.setSize(sf::Vector2f(100.f, 100.f)); // .f signifies its a float val not a double or int
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);


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

    this->updateMousePositions();

    this->updateEnemies();
}

void Game::pollEvents(){

    while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed || (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape))
            this->window->close();

	}


}

void Game::updateEnemies(){
    if(static_cast<int>(this->enemies.size()) < this->maxEnemies){
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax){

            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else{

            this->enemySpawnTimer += 1.f;
        }
    }

    for(int i = 0; i < (int) this->enemies.size(); i++){
        this->enemies[i].move(0.f, 5.f);

        bool deleted = false;


        //check if we clicked mouse
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
                deleted = true;

                this->points += 10.f;

            }
            

        // enemy is past bottom of screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
            deleted = true;
        

        if(deleted)
            this->enemies.erase(this->enemies.begin() + i);

    }

}


void Game::render(){

    this->window->clear();

    //draw stuff below
    this->renderEnemies();

    this->window->display();

}

void Game::renderEnemies(){

    for(auto &e : this->enemies){
        this->window->draw(e);
    }
    
}

const bool Game::running() const {
    return this->window->isOpen();
}


void Game::updateMousePositions(){
    // return void function
    // updates mouse position relative to window
    // Vector2i

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::spawnEnemy(){

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>((this->window->getSize().x - this->enemy.getSize().x))),
        0.f
    );

    this->enemy.setFillColor(sf::Color::Green);

    this->enemies.push_back(this->enemy);
}

