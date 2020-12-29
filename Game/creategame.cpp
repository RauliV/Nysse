
//#include "test_func_runs.h"
#include "creategame.hh"
#include "city.hh"
#include "setboard.hh"
#include "gameengine.hh"
//#include "statistics.hh"


namespace Interface {


std::shared_ptr<Interface::ICity> createGame()

{   //luodaan pelin oliot
    std::shared_ptr<City> cityPtr = std::make_shared<City> ();
    std::shared_ptr<Interface::ICity> icityPtr = cityPtr;
    std::shared_ptr<CourseSide::Logic> game_ptr = std::make_shared<CourseSide::Logic> ();
    std::shared_ptr<QTime> gameClk = std::make_shared<QTime> (0,0,0);

    //Ensimmäinen pelaaja asetetaan vasta, kun pelaajat on luotu
    std::shared_ptr<GameEngine> gameEngine (cityPtr, nullptr);

    cityPtr->setGameClock(gameClk);
    cityPtr->setGame(game_ptr);

    game_ptr->fileConfig();
    game_ptr->takeCity(icityPtr);
    game_ptr->finalizeGameStart();

    initScreen(icityPtr);
    createAtmsBars();
    createTaxisScooters();
    clearPassengers();

    initScreen(icityPtr);

    return icityPtr;

}
}
