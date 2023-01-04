#include "../../include/CUSTOM/Game_main.hpp"



int main(){

    //initialize random seed

    srand(static_cast<unsigned>(time(0)));

    Game game;


    while(game.running()){

        game.update();


        game.render();

    }

    return 0;
}
