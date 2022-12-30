#include "../../include/CUSTOM/Game_2.hpp"


Game::~Game(){
    
    delete this->window;

}



Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}



void Game::initVariables(){
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxNbrBalls = 15;
    this->points = 0; 
}


void Game::initWindow(){
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(60);

}


void Game::render(){
    this->window->clear();

    this->player.render(this->window);

    for(auto i : this->balls){
        i.render(this->window);
    }


    this->renderGui(this->window);
    this->window->display();

}


void Game::update(){
    this->pollEvents();
    this->spawnBalls();
    this->updatePlayer();
    this->updateCollision();
    this->updateGui();
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


void Game::spawnBalls(){
    if(this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 1.f;
    else{
        if((int)this->balls.size() < this->maxNbrBalls){
            this->balls.push_back(Ball(this->window, this->randBallType()));
            
            this->spawnTimer = 0.f; 
        }
        
    }

}

void Game::updateCollision(){

    for(size_t i = 0; i < this->balls.size(); i++){
        if(this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds())){  
           if(this->balls[i].getType() == ballTypes::DEFAULT)
                this->points += 1;

           else if(this->balls[i].getType() == ballTypes::DAMAGING)
                this->player.takeDamage(5);

           else if(this->balls[i].getType() == ballTypes::HEALING)
                this->player.gainHealth(1);

            

            this->balls.erase(this->balls.begin() + i);
        }
    }

}


int Game::initFont(){
    if(!this->font.loadFromFile("../fonts/Caladea-Regular.ttf"))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void Game::initText(){
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(24);


}


void Game::renderGui(sf::RenderTarget* target){

    target->draw(this->guiText);

}


void Game::updateGui(){
    std::stringstream ss;

    ss << "Points: " << this->points << "\n" << "Health: " << this->player.getHp() << " / " << 
    this->player.getHpMax() << "\n";
    this->guiText.setString(ss.str());
}


const int Game::randBallType() const{
    
    int type = ballTypes::DEFAULT;

    int randValue = rand() % 100 + 1;


    if(randValue > 60 && randValue <= 80)
        type = ballTypes::DAMAGING;
    else if(randValue > 80 && randValue <= 100)
        type = ballTypes::HEALING;
    
    return type;

}


const bool & Game::getEndGame() const{

    return this->endGame;
}

void Game::updatePlayer(){
    this->player.update(this->window);
    
    if(this->player.getHp() <= 0)
        this->endGame = true;
    
}
