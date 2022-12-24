#include "../include/CUSTOM/Game.hpp"


int main(){
    //Init game engine
    srand(static_cast<unsigned>(time(NULL)));
    Game game;


	while(game.running()){
		
        game.update();

        game.render();

	}


    return 0;
}

