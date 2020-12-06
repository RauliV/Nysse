#include "core/logic.hh"
#include "creategame.hh"
#include "city.hh"
#include "setboard.hh"
#include "gameengine.h"
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



/*
 
 * tilanneraportti ja aikataulu
 * static itemsit
 * playerit
 * calculateTotalTravelCosts
 * astu scootteriin ja taksiin.
 * Nysseä pitää odottaa?
 * akkuhuomio scooter: ehkä vaan funktio is_travel_possible tms.
 * *Siivoa koko kaupunki
 * Baari - ajan kuluminen
 * Säännöt/documentointi ym.

 * UnitTests:   SpendCash - matkustaessa kulutetaan, niin olisi syytä olla
 *                          menemättä negat, ettei tule tolpalla tappelua
 *
 * *

drunkness - drunkeness -> buzz?

Ihmettelyä:
 * liikkuuko bussit pysäkinvälit linnuntietä?
 * vakiomäärittelyt omiin tiedostoihinsa
 *Montako kulkuneuvoa. nyt 6? vakio määrästä? suhteutettuna pelaajiin?

Nysse pysäkinväli - ei voi jatkaa samalla nyssellä? -> chosenLocation = nextstop

*
* ATM pelaaja on jo nostanut -> button inactive - onko lopullisesti ?;

*tick -> player not idle -> move
 * Klikattu kohdetta:
 *
 * jos pelaaja määränpäässä -> idle -> mitä tehdään. Baarissa ryypätään,
 * ei olla idle = vuoroa ei tule, ennenkuin juomingit loppuy
 * Laske pelaajan liikkumispisteet vector (Pelaaja (-> kulkuneuvo-> nopeus, nyt loc), wantedXY)
 * jos ei nyssessä:
 *
 * goalDestination -> punainen x?

 *loadscreen
 *loppuscreen

 *
 *
 *

*/
