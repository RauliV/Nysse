#include "../Course/CourseLib/creategame.hh"
#include "city.hh"





std::shared_ptr<Interface::ICity> createGame()
// Tätä ei ajeta vielä, koska errorerror
{
    City tampere;
    auto ikkuna_osoitin = std::make_shared<CourseSide::SimpleMainWindow> ();
    tampere.set_window(ikkuna_osoitin);

    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);
    tampere.setBackground(tausta_iso, tausta_pieni);
    tampere.get_window()->show();

    std::shared_ptr<Interface::ICity> pCity = std::make_shared<City>(tampere);
    return pCity;

}

/*{

    std::shared_ptr<Interface::ICity> iCity;
    // std::shared_ptr<Interface::City> pointer = std::make_shared<City>();
    //init_screen(pointer);
    iCity -> setClock(QTime::currentTime());
    iCity ->startGame();

    return iCity;
}
*/
