#include "test_func_runs.h"
#include "core/logic.hh"
#include "creategame.hh"
#include "city.hh"
#include "interfaces/icity.hh"
#include "player.hh"
#include "statistics.hh"
#include "graphics/simplemainwindow.hh"
#include <QApplication>
#include <QDebug>
#include <memory>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    //auto pointer = Interface::createGame();
    auto city_pointer = std::make_shared <City> ();
    auto ikkuna_osoitin = std::make_shared<CourseSide::SimpleMainWindow> ();
    city_pointer->set_window(ikkuna_osoitin);
    init_screen(city_pointer);
    addActors(city_pointer);

    return a.exec();


}
