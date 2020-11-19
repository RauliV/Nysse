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


    //Miksi paluuarvona createGamessa on osoite ICity -abstraktiin luokkaan, eikä
    //staattiseen Cityyn, josta olisi luotavissa olio?

    //pointer = Interface::createGame(); //Em. ristiriidasta johtuen tässä sekoaa?

    auto pointer = std::make_shared <City> (); //koeajoja varten korvataan se tällä

    // Koeajoja - oikeastaan funktiokutsuja, mitkä olisivat createGamessa
    auto ikkuna_osoitin = std::make_shared<CourseSide::SimpleMainWindow> ();
    pointer->set_window(ikkuna_osoitin); //Atribuutiksi ikkunaolio
    init_screen(pointer);     //createGame.cc funktio
    addActors(pointer);
    return a.exec();


}
