#include "test_func_runs.h"
#include "creategame.hh"
#include "city.hh"
#include "core/logic.hh"
#include "interfaces/icity.hh"
#include "statistics.hh"
#include <memory>




std::shared_ptr<Interface::ICity> createGame()

{
    Interface::ICity* icity_pointer;
    //icity_pointer->startGame();
    City* city_pointer = dynamic_cast<City*>(icity_pointer);//icity_pointer);
    std::shared_ptr<Interface::ICity> shared_ic_ptr(icity_pointer);
    std::shared_ptr<City> city_shared_ptr(city_pointer);
    city_pointer->get_window()->show();

    CourseSide::Logic game();
    QTime pelikello;

    init_screen(city_shared_ptr);
    addActors(city_shared_ptr);

    return shared_ic_ptr;

            //std::shared_ptr<Interface::ICity>  (tampere );
}

