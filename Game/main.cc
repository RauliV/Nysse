//#include "test_func_runs.h"
#include "core/logic.hh"
#include "creategame.hh"
#include "city.hh"
#include "setboard.hh"
#include "game_engine.h"
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

    std::shared_ptr<City> cPtr = std::dynamic_pointer_cast<City>(Tampere);

    std::shared_ptr<MainWindow> mainWindow = std::make_shared<MainWindow> ();

    cPtr->setWindow(mainWindow);
    initScreen(Tampere);
    cPtr->getGame()->finalizeGameStart();
    startYourEngines(Tampere);



    return a.exec();

}

//targetlocation cityyn
//miten välitän saman cityolion sekä game-engineen, että
//setboardiin.
//luodaan täällä
//konstaillaan
//Baarien ja atm luokat ja luonti
//Player - in_vechile
//Timerouteplayer
//tick -> player not idle -> move
