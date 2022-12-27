#include "../include/CUSTOM/Game.hpp"

//Private Functions
void Game::initVariables(){

    this->window = nullptr;
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;



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
    this->initFonts();
    this->initText();
    this->initEnemies();

}

Game::~Game(){

    delete this->window;

}

void Game::update(){

    this->pollEvents();

    if(!this->endGame){
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    if(this->health <= 0){
        this->endGame = true;
    }
}

void Game::pollEvents(){

    while(this->window->pollEvent(this->event)){
		if(this->event.type == sf::Event::Closed || (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape))
            this->window->close();

	}


}

const bool Game::getEndGame() const{
    return this->endGame;
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

        // enemy is past bottom of screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            this->health -= 1;
            this->enemies.erase(this->enemies.begin() + i);
        }
    }

    
    //check if we clicked mouse
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!this->mouseHeld){
            this->mouseHeld = true;
            bool deleted = false;
            for(size_t i = 0; i < this->enemies.size() && !deleted; i++){
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    this->points += 1;

                }
            }
        }
    }
    else{
        this->mouseHeld = false;
    }

}

void Game::initFonts(){

    this->font.loadFromFile("fonts/Caladea-Regular.ttf");
}

void Game::initText(){
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}


void Game::render(){

    this->window->clear();

    //draw stuff below
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();

}

void Game::renderEnemies(sf::RenderTarget& target){

    for(auto &e : this->enemies){
        target.draw(e);
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

void Game::updateText(){

    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
       << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());  
}

void Game::renderText(sf::RenderTarget& target){

    target.draw(this->uiText);

}
