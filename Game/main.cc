#include "test_func_runs.h"
#include "core/logic.hh"
#include "creategame.hh"
#include "city.hh"
#include "interfaces/icity.hh"
#include "player.hh"
#include "statistics.hh"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <memory>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);


    std::shared_ptr<Interface::ICity> Tampere = Interface::createGame();

    //!!EI TOIMI!!

    //std::shared_ptr<City> Tampere = std::make_shared<City> ();

    // Korvataan täällä kunnnes toimii


    MainWindow ikkuna;
    ikkuna.show();


    std::shared_ptr<CourseSide::Logic> Game = std::make_shared<CourseSide::Logic> ();

    read_given_data(Game);
    Tampere->startGame();
    //auto pointer = Interface::createGame();


    return a.exec();


}
