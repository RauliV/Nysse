
//#include "test_func_runs.h"
#include "creategame.hh"
#include "city.hh"
#include "game_engine.h"
//#include "core/logic.hh"
//#include "interfaces/icity.hh"
//#include "statistics.hh"


namespace Interface {


std::shared_ptr<Interface::ICity> createGame()

{   //luodaan pelin oliot
    std::shared_ptr<City> cityPtr = std::make_shared<City> ();
    std::shared_ptr<Interface::ICity> icityPtr = cityPtr;
    std::shared_ptr<CourseSide::Logic> game_ptr = std::make_shared<CourseSide::Logic> ();
    std::shared_ptr<QTime> gameClk = std::make_shared<QTime> (0,0,0);

    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);
    //cityPtr->setBackground(tausta_pieni, tausta_iso);

    cityPtr->setGameClock(gameClk);
    cityPtr->setGame(game_ptr);

    game_ptr->fileConfig();

    game_ptr->takeCity(icityPtr);


    return icityPtr;

    //pelilogiikkaolio omaan muuttujaan engineen
}
}
