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
    this->height = 800.f;
    this->endGame = false;
    this->player = new Character();
    this->cars.push_back(new Car("../textures/car_1.png", this->width / 2.f + 15.f, this->width / 2.f, 3.f, 'U'));
    this->cars.push_back(new Car("../textures/car_2.png", this->width / 2.1f, this->height / 2.f, 3.f, 'D'));
    this->cars.push_back(new Car("../textures/car_3.png", 0.f, this->height / 1.8f, 3.f, 'R'));
    this->cars.push_back(new Car("../textures/car_4.png", this->width, this->height / 2.1f, 3.f, 'L'));

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
    this->handleVerticalCarCollisions();
    this->handleHorizontalCarCollisions();
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

void Game::handleVerticalCarCollisions(){
    //collisions where cars moving vertically hit cars moving across
    const unsigned int carGoingUp = 0;
    const unsigned int carGoingDown = 1;
    const unsigned int carGoingRight = 2;
    const unsigned int carGoingLeft = 3;

    const float collisionDist = 5.f;
    const float removeEmptyCollisionSpace = 8.f;

    //Car going up hits car going right as it is on its way
    if(this->cars[carGoingUp]->checkCarCollision(*this->cars[carGoingRight])){
        auto y_coord = this->cars[carGoingUp]->getSprite().getGlobalBounds().top - collisionDist;
        auto x_coord_1 = this->cars[carGoingUp]->getSprite().getGlobalBounds().left + removeEmptyCollisionSpace;
        auto x_coord_2 = this->cars[carGoingUp]->getSprite().getGlobalBounds().left + this->cars[carGoingUp]->getSprite().getGlobalBounds().width - removeEmptyCollisionSpace;

        if(this->cars[carGoingRight]->getSprite().getGlobalBounds().contains(x_coord_1, y_coord))
            this->cars[carGoingUp]->setStopSprite(true);
        else if(this->cars[carGoingRight]->getSprite().getGlobalBounds().contains(x_coord_2, y_coord))
            this->cars[carGoingUp]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingUp]->setStopSprite(false);

    //Car going up hits car going left as it is on its way
    if(this->cars[carGoingUp]->checkCarCollision(*this->cars[carGoingLeft])){
        auto y_coord = this->cars[carGoingUp]->getSprite().getGlobalBounds().top - collisionDist;
        auto x_coord_1 = this->cars[carGoingUp]->getSprite().getGlobalBounds().left + removeEmptyCollisionSpace;
        auto x_coord_2 = this->cars[carGoingUp]->getSprite().getGlobalBounds().left + this->cars[carGoingUp]->getSprite().getGlobalBounds().width - removeEmptyCollisionSpace;

        if(this->cars[carGoingLeft]->getSprite().getGlobalBounds().contains(x_coord_1, y_coord))
            this->cars[carGoingUp]->setStopSprite(true);
        else if(this->cars[carGoingLeft]->getSprite().getGlobalBounds().contains(x_coord_2, y_coord))
            this->cars[carGoingUp]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingUp]->setStopSprite(false);

    //Car going down hits car going right as it is on its way
    if(this->cars[carGoingDown]->checkCarCollision(*this->cars[carGoingRight])){
        auto y_coord = this->cars[carGoingDown]->getSprite().getGlobalBounds().top + this->cars[carGoingDown]->getSprite().getGlobalBounds().height + collisionDist;
        auto x_coord_1 = this->cars[carGoingDown]->getSprite().getGlobalBounds().left + removeEmptyCollisionSpace;
        auto x_coord_2 = this->cars[carGoingDown]->getSprite().getGlobalBounds().left + this->cars[carGoingDown]->getSprite().getGlobalBounds().width - removeEmptyCollisionSpace;

        if(this->cars[carGoingRight]->getSprite().getGlobalBounds().contains(x_coord_1, y_coord))
            this->cars[carGoingDown]->setStopSprite(true);
        else if(this->cars[carGoingRight]->getSprite().getGlobalBounds().contains(x_coord_2, y_coord))
            this->cars[carGoingDown]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingDown]->setStopSprite(false);

    //Car going down hits car going left as it is on its way
    if(this->cars[carGoingDown]->checkCarCollision(*this->cars[carGoingLeft])){
        auto y_coord = this->cars[carGoingDown]->getSprite().getGlobalBounds().top + this->cars[carGoingDown]->getSprite().getGlobalBounds().height + collisionDist;
        auto x_coord_1 = this->cars[carGoingDown]->getSprite().getGlobalBounds().left + removeEmptyCollisionSpace;
        auto x_coord_2 = this->cars[carGoingDown]->getSprite().getGlobalBounds().left + this->cars[carGoingDown]->getSprite().getGlobalBounds().width - removeEmptyCollisionSpace;

        if(this->cars[carGoingLeft]->getSprite().getGlobalBounds().contains(x_coord_1, y_coord))
            this->cars[carGoingDown]->setStopSprite(true);
        else if(this->cars[carGoingLeft]->getSprite().getGlobalBounds().contains(x_coord_2, y_coord))
            this->cars[carGoingDown]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingDown]->setStopSprite(false);

}


void Game::handleHorizontalCarCollisions(){
    //collisions where cars moving horizontally hit cars moving vertically
    const unsigned int carGoingUp = 0;
    const unsigned int carGoingDown = 1;
    const unsigned int carGoingRight = 2;
    const unsigned int carGoingLeft = 3;

    const float collisionDist = 5.f;
    const float removeEmptyCollisionSpace = 8.f;

    //Car going right hits car going down as it is on its way
    if(this->cars[carGoingRight]->checkCarCollision(*this->cars[carGoingDown])){
        auto x_coord = this->cars[carGoingRight]->getSprite().getGlobalBounds().left + this->cars[carGoingRight]->getSprite().getGlobalBounds().width + collisionDist;
        auto y_coord_1 = this->cars[carGoingRight]->getSprite().getGlobalBounds().top + removeEmptyCollisionSpace;
        auto y_coord_2 = this->cars[carGoingRight]->getSprite().getGlobalBounds().top + this->cars[carGoingRight]->getSprite().getGlobalBounds().height - removeEmptyCollisionSpace;

        if(this->cars[carGoingDown]->getSprite().getGlobalBounds().contains(x_coord, y_coord_1))
            this->cars[carGoingRight]->setStopSprite(true);
        else if(this->cars[carGoingDown]->getSprite().getGlobalBounds().contains(x_coord, y_coord_2))
            this->cars[carGoingRight]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingRight]->setStopSprite(false);

    //Car going right hits car going up as it is on its way
    if(this->cars[carGoingRight]->checkCarCollision(*this->cars[carGoingUp])){
        auto x_coord = this->cars[carGoingRight]->getSprite().getGlobalBounds().left + this->cars[carGoingRight]->getSprite().getGlobalBounds().width + collisionDist;
        auto y_coord_1 = this->cars[carGoingRight]->getSprite().getGlobalBounds().top + removeEmptyCollisionSpace;
        auto y_coord_2 = this->cars[carGoingRight]->getSprite().getGlobalBounds().top + this->cars[carGoingRight]->getSprite().getGlobalBounds().height - removeEmptyCollisionSpace;


        if(this->cars[carGoingUp]->getSprite().getGlobalBounds().contains(x_coord, y_coord_1))
            this->cars[carGoingRight]->setStopSprite(true);
        else if(this->cars[carGoingUp]->getSprite().getGlobalBounds().contains(x_coord, y_coord_2))
            this->cars[carGoingRight]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingRight]->setStopSprite(false);

    //Car going left hits car going down as it is on its way
    if(this->cars[carGoingLeft]->checkCarCollision(*this->cars[carGoingDown])){
        auto x_coord = this->cars[carGoingLeft]->getSprite().getGlobalBounds().left - collisionDist;
        auto y_coord_1 = this->cars[carGoingLeft]->getSprite().getGlobalBounds().top + removeEmptyCollisionSpace;
        auto y_coord_2 = this->cars[carGoingLeft]->getSprite().getGlobalBounds().top + this->cars[carGoingRight]->getSprite().getGlobalBounds().height - removeEmptyCollisionSpace;

        if(this->cars[carGoingDown]->getSprite().getGlobalBounds().contains(x_coord, y_coord_1))
            this->cars[carGoingLeft]->setStopSprite(true);
        else if(this->cars[carGoingDown]->getSprite().getGlobalBounds().contains(x_coord, y_coord_2))
            this->cars[carGoingLeft]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingLeft]->setStopSprite(false);

    //Car going left hits car going up as it is on its way
    if(this->cars[carGoingLeft]->checkCarCollision(*this->cars[carGoingUp])){
        auto x_coord = this->cars[carGoingLeft]->getSprite().getGlobalBounds().left - collisionDist;
        auto y_coord_1 = this->cars[carGoingLeft]->getSprite().getGlobalBounds().top + removeEmptyCollisionSpace;
        auto y_coord_2 = this->cars[carGoingLeft]->getSprite().getGlobalBounds().top + this->cars[carGoingRight]->getSprite().getGlobalBounds().height - removeEmptyCollisionSpace;

        if(this->cars[carGoingUp]->getSprite().getGlobalBounds().contains(x_coord, y_coord_1))
            this->cars[carGoingLeft]->setStopSprite(true);
        else if(this->cars[carGoingUp]->getSprite().getGlobalBounds().contains(x_coord, y_coord_2))
            this->cars[carGoingLeft]->setStopSprite(true);

        return;
    }
    else
        this->cars[carGoingLeft]->setStopSprite(false);

}
