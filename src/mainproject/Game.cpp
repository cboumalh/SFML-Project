#include "../../include/CUSTOM/Game_main.hpp"


Game::~Game(){
    delete this->window;
    delete this->player;
    delete this->coin;
    delete this->potion;
}


Game::Game(){
    this->initVariables();
    this->initPlayer();
    this->initCoin();
    this->initText();
    this->initPotion();
    this->initCoinSound();
    this->initPotionSound();
    this->initGhost();
    this->initCars();
    this->initFonts();
    this->initBackgroundTexture();
    this->initView();
    this->initWindow();
    this->initBackgroundSprite();
    this->initHighwaySound();
}



void Game::initVariables(){
    this->width = 800.f;
    this->height = 800.f;
    this->endGame = false;
    this->points = 0;
    this->clockRestartCounter = 0;
    this->playerInvisible = false;
    this->nightModeOn = false;
    this->potionDuration = 20.f;

}

void Game::initCars(){
    this->cars.push_back(new Car("../textures/car_1.png", this->width / 2.f + 15.f, this->width / 2.f, 1.5f, 'U'));
    this->cars.push_back(new Car("../textures/car_2.png", this->width / 2.1f, this->height / 2.f, 1.5f, 'D'));
    this->cars.push_back(new Car("../textures/car_3.png", 0.f, this->height / 1.8f, 1.5f, 'R'));
    this->cars.push_back(new Car("../textures/car_4.png", this->width, this->height / 2.1f, 1.5f, 'L'));

}

void Game::initPlayer(){
    this->player = new Character();
}

void Game::initGhost(){
    this->ghost = new Ghost(this->player);
}

void Game::initHighwaySound(){
    if (!this->highwaySound.openFromFile("../sounds/highwaySound.ogg"))
         std::cout<< "Traffic sound did not load" << std::endl;

    // Set the volume and play the music
    this->highwaySound.setVolume(30);
    this->highwaySound.play();
    this->highwaySound.setLoop(true);  
}

void Game::stopHighwaySound(){
    this->highwaySound.setVolume(0);
}

void Game::initCoinSound(){
    if (!this->coinBuffer.loadFromFile("../sounds/coinSound.ogg"))
        std::cout<< "Coin sound did not load" << std::endl;


    this->coinSound.setBuffer(coinBuffer);
}

void Game::initPotionSound(){
    if (!this->potionBuffer.loadFromFile("../sounds/potionSound.ogg"))
        std::cout<< "Potion sound did not load" << std::endl;


    this->potionSound.setBuffer(potionBuffer);
}

void Game::initCoin(){
    this->coin = new Coin();
}

void Game::initPotion(){
    this->potion = new Potion();
}

void Game::initFonts(){
	if (!this->font.loadFromFile("../fonts/Caladea-Regular.ttf")){
		std::cout << "FONT DID NOT LOAD" << std::endl;
	}
}


void Game::initText()
{
	//Gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(20);
	this->guiText.setFillColor(sf::Color::Black);


	//End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Black);
	this->endGameText.setCharacterSize(30);
	this->endGameText.setString("YOU DIED!");
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

void Game::nightMode(){
    this->backgroundSprite.setColor(sf::Color(255, 255, 255, 128));
}

void Game::dayMode(){
    this->backgroundSprite.setColor(sf::Color(255, 255, 255, 255));
}

void Game::updateMode(){
    if(this->clockRestartCounter > 3){
        this->nightMode();
        if(this->clockRestartCounter == 7) this->clockRestartCounter = 0;
        this->nightModeOn = true;
    }
    else{
        this->dayMode();
        this->nightModeOn = false;
    }
}

void Game::renderBackground(){

    this->window->draw(this->backgroundSprite); 
}

void Game::renderGui(sf::RenderTarget* target){
	target->draw(this->guiText);
}


void Game::render(){
    this->window->clear();

    this->renderBackground();

    for(auto &car : this->cars)
        car->render(this->window);

    this->player->render(this->window);

    this->coin->render(this->window);

    this->renderPotion(this->window);

    this->renderGhost(this->window);

    this->renderGui(this->window);

    if(this->endGame == true)
		this->window->draw(this->endGameText);

    this->window->display();

}

void Game::renderPotion(sf::RenderTarget *target){
    if(this->potionClock.getElapsedTime().asSeconds() > this->potionDuration){
        this->potion->setActiveBool(true);
        this->potion->render(target);
    }
}

void Game::renderGhost(sf::RenderTarget *target){
    if(this->nightModeOn){
        this->ghost->render(target);
    }
}

void Game::updateGhost(){
    if(this->nightModeOn){
        this->ghost->setActiveBool(true);
        this->ghost->updateSpritePos(this->player);
    }
    else{
        this->ghost->setActiveBool(false);
    }
}

void Game::update(){
    this->pollEvents();
    if(this->endGame == false){
        for(auto &car : this->cars)
            car->update(this->window);
        this->handleVerticalCarCollisions();
        this->handleHorizontalCarCollisions();
        this->player->update(this->window);
        this->PlayerCarCollision();
        this->updatePlayerCoinCollision();
        this->updatePlayerPotionCollision();
        this->updateGui();
        this->updateGhost();
        this->GhostPlayerCollision();
        this->speedUpGame();
        this->makePlayerVisible();
        this->updateEndGameText();
        this->updateView();
        this->updateMode();
    }
}


const bool Game::running() const{

    return this->window->isOpen();
}

void Game::updateGui(){
	std::stringstream ss;

	ss << " Points: " << this->points << std::endl;

	this->guiText.setString(ss.str());
    this->guiText.setPosition(this->view.getCenter().x - this->view.getSize().x / 2.f, this->view.getCenter().y - this->view.getSize().y / 2.f);

}


void Game::updateEndGameText(){
	this->endGameText.setPosition(this->view.getCenter().x - this->endGameText.getLocalBounds().width / 2.f, this->view.getCenter().y - this->endGameText.getLocalBounds().height / 2.f);
}

void Game::updatePlayerCoinCollision(){
    if(this->coin->getSprite().getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds())) {
        this->coin->updateSpritePos(this->window);
        this->points++;
        this->coinSound.play();
    }
}

void Game::makePlayerInvisible(){
    this->player->setTookPotion(true);
    this->player->getSprite().setColor(sf::Color(255, 255, 255, 128));
}

void Game::makePlayerVisible(){
    if(this->potionClock.getElapsedTime().asSeconds() > 5.f){
        this->player->setTookPotion(false);
        this->player->getSprite().setColor(sf::Color(255, 255, 255, 255));
    }
}

void Game::updatePlayerPotionCollision(){
    if(this->potion->getSprite().getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds()) && this->potion->getActiveBool()){
        this->potion->updateSpritePos(this->window);
        this->potion->setActiveBool(false);
        this->potionSound.play();
        this->makePlayerInvisible();
        this->potionClock.restart();
    }
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

void Game::PlayerCarCollision(){
    for(auto &car : this->cars)
        if(car->getSprite().getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds()) && !this->player->getTookPotion()) {
            this->endGame = true;
            this->stopHighwaySound();
        }
}

void Game::GhostPlayerCollision(){
    if(this->ghost->getSprite().getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds()) && this->ghost->getActiveBool()) {
        this->endGame = true;
        this->stopHighwaySound();
    }
}

void Game::speedUpGame(){
    if(this->clock.getElapsedTime().asSeconds() > 10.f){
        for(auto &car : this->cars)
            car->incrementCarSpeed();
        this->clock.restart();
        this->clockRestartCounter += 1;
    }
}

