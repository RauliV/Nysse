/* PALAUTUS MAANANTAINA 7.12 ON RAAKILEPALAUTUS. HALUAMME TOTEUTTAA
 * KUNNIANHIMOISEN PROJEKTIMME LOPPUUN, VAIKKA AIKATAULU YLITTYY
 *
 * TÄMÄ EI OLE VALMIS PELI. SAIMME SANKTIOTONTA LISÄAIKAA 7.12 ASTI

********************************************************************************
**********    Tampereen Tähti - pikkujouluinen kaupunkiseikkailu   *************
******************      TIE 0240X-OHJELMOINTI3 2020 - 2021      ****************
*******                                                                  *******
**********          Sami Mansikkala            Rauli Virtanen         **********
****             sami.mansikkala@tuni.fi    rauli.virtanen@tuni.fi          ****
*                                                                              *
*                ON:                             ON: 290592                    *
*                                                                              *
********************************************************************************
*
*
* PELIN TAVOITE
*
* Pelin tavoitteena on saavuttaa kartalta arvottu maalilokaatio ensimmäisenä
*
*
*
* PELIN ALOITUS
*
* Pelin alussa 1-4 pelaajaa luovat pelinappulalleen nimen ja värin
* Ohjelma arpoo pelaajien aloituspisteen joka on riittävän suurella tarkkuudella
* yhtä kaukana maalista jokaisella pelaajalla
*
* Peli arpoo (muiden kuin nyssepysäkkien) pysähtymispisteiden sijainnit
* - yhteen baareista arvotaan helikopteripilotti
*
* Peli arpoo (muiden kuin nyssejen) kulkuneuvojen sijainnit kartalla. Eivät
* liiku itsellään.
*
*
*
* PELAAJIEN OMINAISUUDET
* Iactor -virtuualiluokassa esiteltyjen lisäksi, josta pelaajaluokka on periytetty
*
* Rahat
* Humala -> pelaajan kuvake portraitissa vaihtuu humalan mukaan. Max lvl 5,
* jolloin tulee noutaja
*
*
*
* KÄYTETTÄVÄT KULKUNEUVOT
*
* Ei mitään(kävellen):  Nopeus:     hidas (default)
*                       Hinta:      ilmainen
*                       Promillet:  ei rajoitusta
*
* Taxi ->               Nopeus:     nopea
*                       Hinta:      kallis
*                       Promillet:  korkea raja
*
* Scooter ->            Nopeus:     kohtalainen
*                       Hinta:      kohtalainen
*                       Promillet:  alhainen raja
* *
* Helikopteri ->        Nopeus:     supernopea (heti maaliin)
*                       Hinta:      ilmainen
*                       Promillet:  ei promillerajoitusta
*                       Edellyttää, että baarista on löytynyt helikopteripilotti
*                       Ei ole tarkoituksenmukaista luoda omaa luokkaa tälle
*
*
* PYSÄHDYSPISTEET:
* Periytetty IStopista
*
* Nyssepysäkki->        Odottaa seuraavaa nysseä. Määränpää seuraava pysäkki.
*
* ATM->                 Rahat lompakossa lisääntyy, tililtä vähenee. Vain
*                       kerran voi nostaa samalata automaatilta
*
* Baari ->              Aikaa/vuoro kuluu, humalatila nousee, rahat vähenee
*                       10% mahdollisuus löytää pilotti
*
*
*
* PELIN KULKU
*
* Vuorossa seuraava "idle" pelaaja
*
* Valittavana interaktio lähellä olevien pysähdyspisteiden kanssa (ATM,
* nyssepysäkki tai baari)
*   - kohteessa tehdään em. toimet
*
* tai
*
* matkustus kartalta klikattuun kohteeseen.
*   - jos pelaajan lähellä kulkuneuvo(ja), kysytään miten haluaa matkustaa
*   - tarkistaa, että pelaaja on kelpoinen käyttämään kulkuneuvoa
*   - matka alkaa -> pelaaja ei ole "idle"
*
*
* VOITTO:
*
* Kun pelaajan lokaatio on maalin lokaatio
* Jos helikopteripilotti löytynyt (pelaajan lokaatio = maalin lokaatio)
*
* Kun muita pelaajia ei enää jälkellä (promilleLvl muilla ollut > 5)
*
*
*/

#include "core/logic.hh"
#include "creategame.hh"
#include "city.hh"
#include "setboard.hh"
#include "gameengine_old.h"
#include <QApplication>
#include <QDebug>
#include <memory>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);


    std::shared_ptr<Interface::ICity> Tampere = Interface::createGame();


    return a.exec();

}



/*  NOTES/TODO/ETC:
 


 * Säännöt/documentointi ym.
 * drunkness - drunkeness -> buzz?
 * goalDestination -> punainen x?
 * loadscreen
 * loppuscreen
*/
