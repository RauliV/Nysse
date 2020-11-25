
//#include "test_func_runs.h"
#include "creategame.hh"
#include "city.hh"
//#include "core/logic.hh"
//#include "interfaces/icity.hh"
//#include "statistics.hh"


namespace Interface {


std::shared_ptr<Interface::ICity> createGame()

{
    //Interface::ICity* icity_pointer;
    //icity_pointer->startGame();
    //City* city_pointer = dynamic_cast<City*>(icity_pointer);//icity_pointer);
    //std::shared_ptr<Interface::ICity> shared_ic_ptr(icity_pointer);
    std::shared_ptr<City> cityPtr = std::make_shared<City> ();
    std::shared_ptr<Interface::ICity> icityPtr = cityPtr;
    std::shared_ptr<CourseSide::Logic> game_ptr = std::make_shared<CourseSide::Logic> ();
    cityPtr->setGame(game_ptr);
    game_ptr->takeCity(icityPtr);
    //game_ptr->finalizeGameStart();
    init_screen(icityPtr);
    addActors(icityPtr);

    return icityPtr;

    //pelilogiikkaolio omaan muuttujaan engineen
}
}
