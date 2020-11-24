
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
    std::shared_ptr<Interface::ICity> city_ptr = std::make_shared<City> ();
    //std::shared_ptr<CourseSide::Logic> game_ptr = std::make_shared<CourseSide::Logic> ();
   /* game_ptr->takeCity(city_ptr);
    game_ptr->finalizeGameStart();
    QTime pelikello;

    init_screen(city_ptr);
    addActors(city_ptr);*/

    return city_ptr;

    //pelilogiikkaolio omaan muuttujaan engineen
}
}
