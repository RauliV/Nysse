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



/*UI
 *Kulkuneuvoon astuminen (ehdot: akku, rahat, känni)
 * jos menee pysäkille -> nysseen, chosenlocation on next stop
 *

 * Spendcash unittest - matkustaessa kulutetaan, niin olisi syytä olla
 * menemättä negat, ettei tule tolpalla tappelua
 *
 *Montako kulkuneuvoa

//nopeus = steps on tick.

*
*
* * Kulkuneuvot:  + Nopeus, hinta/distance, icon, akku
*
*               taksi könttä
*               + Hinta:    Nysse pysäkinväli - ei voi jatkaa samalla nyssellä
*                           Taksi kulkee niin kauan kuin rahaa
*                           taksi kulkee mistä mihin? (vaatii n. 3 nostoa maaliin)
                            Tieristä loppuu akku 10 egee.
*               + ActorIcon
*
* promillerajat kulkuneuvoihin
*
* ATM pelaaja on jo nostanut;
* Lukumäärät suhteutetaan pelaajamääriin?
*
*
*
*  * kulkuneuvojen lisäämiseen AddActor
*
*

*
*
*   2.12
*
* * Unittests - karttakoko/koordinaatit
*Siivoa koko kaupunki
*
*
* get right icon
*  * actoritem -> try - catch. Jos ei löydy ikonia -> nysse, stoppi tai matkustaja
    * jos ei stoppilistassa nysse tai matkustaja
    * pitäisikö tehdä pari {actor, type(icon)}

*Timerouteplayer?

*tick -> player not idle -> move
 * Klikattu kohdetta:
 *
 * jos pelaaja määränpäässä -> idle -> mitä tehdään. Baarissa ryypätään,
 * ei olla idle = vuoroa ei tule, ennenkuin juomingit loppuy
 * Laske pelaajan liikkumispisteet vector (Pelaaja (-> kulkuneuvo-> nopeus, nyt loc), wantedXY)
 * jos ei nyssessä: Jos nyssessä vektori = bussivektori
 *
 * return (Qtime,location);

 * goalDestination -> punainen x?
 * tick -> siirry(QTime)


 * Säännöt/documentointi ym.
 *
 *
 *
 *

*/
