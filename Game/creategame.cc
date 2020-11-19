#include "creategame.hh"




std::shared_ptr<Interface::ICity> createGame()
// Tätä ei ajeta vielä, koska errorerror

{

    std::shared_ptr<Interface::ICity> iCity;
    // std::shared_ptr<Interface::City> pointer = std::make_shared<City>();
    //init_screen(pointer);
    iCity -> setClock(QTime::currentTime());
    iCity ->startGame();

    return iCity;
}

