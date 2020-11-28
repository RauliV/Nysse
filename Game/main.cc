//#include "test_func_runs.h"
#include "core/logic.hh"
#include "creategame.hh"
#include "city.hh"
#include "game_engine.h"
//#include "interfaces/icity.hh"
/*#include "player.hh"
#include "statistics.hh"
#include "mainwindow.h"*/
#include <QApplication>
#include <QDebug>
#include <memory>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);


    std::shared_ptr<Interface::ICity> Tampere = Interface::createGame();

    std::shared_ptr<MainWindow> mainWindow = std::make_shared<MainWindow> ();

    std::shared_ptr<City> city = std::dynamic_pointer_cast<City>(Tampere);

    city->setWindow(mainWindow);
    make_game(Tampere);


   /* std::shared_ptr<CourseSide::Logic> Game = std::make_shared<CourseSide::Logic> ();
    kaupunki->setGame(Game);
    make_game(Tampere);
    kaupunki->startGame();*/


    return a.exec();

}
