#include "game_engine.h"
#include "setboard.hh"

std::shared_ptr<City> cityPtr;


void bar(std::shared_ptr<Player> player)
{

    // mitä tapahtuu, kun pelaaja saapuu baariin

}


void atm(std::shared_ptr<Player> player)
{

    // mitä tapahtuu, kun pelaaja saapuu automaatille

}


void stop(std::shared_ptr<Player> player)
{

    // mitä tapahtuu, kun pelaaja saapuu pysäkille

}


void arriveDestination(){ //välietappi



    // jos wanted_destination on baari -> bar(player)
    // jos wanted_destination on atm -> atm(player)
    // jos wanted_destination on stop -> stop(player)

    //movedActors remove(player)


}

void movePlayer(std::shared_ptr<Player> player, int x, int y){
    Interface::Location newLoc(x,y);
    player->move(newLoc);
    //cityPtr->actorMoved(player);
}






// Laskee reitin linnuntietä paikasta A paikkaan B jaettun STEPSiin osaan.
std::vector<std::pair<int, int>> calculatePlayerRoute (Interface::Location A,
                                                      Interface::Location B)
{
    std::vector<std::pair<int, int>> returnVector = {};
    int aX = A.giveX();
    int aY = A.giveY();
    double xMovement = B.giveX() - aX;
    double yMovement = B.giveY() - aY;
    double xStep = xMovement / STEPS;
    double yStep = yMovement / STEPS;
    for (int it = 1; it < 100; it ++){
        std::pair <int, int> coord = {aX + (it*xStep),
                                      aY + (it *yStep)};
        returnVector.push_back(coord);
    }

    return returnVector;

}

void teststuff()
{


    //Testejä
    auto list = cityPtr->getPlayerList();
    int it = 1;
    for (auto const& player : list){
        Interface::Location loc = player->giveLocation();
        /*loc.setXY(xFromEast(player->giveLocation().giveEasternCoord()),
                  yFromNorth(player->giveLocation().giveNorthernCoord()));
        //Interface::Location y = loc.setXY(player->giveLocation().giveEasternCoord();

*/
        QString qname = QString::fromStdString(player->getName());
        QString qcolour = QString::fromStdString(player->getColour());
        qDebug() << "Pelaaja " << it << ": " << qname;
        qDebug() << "Väri on: " << qcolour;
        qDebug() << "Paikassa: ";
        qDebug() << "Maali: " << cityPtr->getGoalLocation().giveX() << cityPtr->getGoalLocation().giveY();
        qDebug() << "Pelaaja: " << loc.giveX() << loc.giveY();

        it ++;
        std::vector<std::pair<int, int>> vec = calculatePlayerRoute(player->giveLocation(),
                                                                    cityPtr->getGoalLocation());
        qDebug() << "jonne mennään seuraavien pisteiden kautta";
        for (auto const& itt : vec){
            qDebug() << itt.first << itt.second;
        }
    }



}


    // X -intervallin napsulla
void updateActors()
{
    for (auto const& actor : cityPtr->getMovedActors()){


/*        Interface::Location paikka = actor->giveLocation();
        int x1 = paikka.giveEasternCoord();
        int y1 = paikka.giveNorthernCoord();
        int x = xFromEast(x1);
        int y = yFromNorth(y1);
        paikka.setXY(x,y);
        //CourseSide::SimpleActorItem acto(x,y,1);
        //cityPtr -> getWindow()-> addActor(x,y,9);
     //                                   actor->giveLocation().giveY(),1);
*/

   // }


}
}


void startYourEngines(std::shared_ptr<Interface::ICity> cPtr)
{
    cityPtr = std::dynamic_pointer_cast<City>(cPtr);


    //tämä siksi, ettei tarvitse aina testattaessa klikkailla.
    int pC = 1;
    std::pair<std::string, std::string> pP = {"Pekka", "musta"};
    std::vector<std::pair<std::string, std::string>> pV {pP};
    createPlayers(pV);

    //aloituspistelotto
    startingPointsSetup();

    //testailuja

    teststuff();
    //startingPointsSetup();


    //updateActors();
}


/*
 *
 * Klikattu kohdetta:
 *
 * jos pelaaja määränpäässä -> idle -> mitä tehdään. Baarissa ryypätään,
 * ei olla idle = vuoroa ei tule, ennenkuin juomingit loppuy
 * Laske pelaajan liikkumispisteet vector (Pelaaja (-> kulkuneuvo-> nopeus, nyt loc), wantedXY)
 * jos ei nyssessä: Jos nyssessä vektori = bussivektori
 *
 * return (Qtime,location);
 *
 *
 *
 * Pelaaja: + missä kulkuneuvossa
 *          + reitti määränpäähän
 *
 * Kulkuneuvot: + Nopeus
 *
 *
 * tick -> siirry(QTime)
 *
 * Moduuleita:  luokat+rajapinnat ; Kulkuneuvot (Iactor), paikat (IStop) -baari: aika, rahat, känni
 *
 * Vakiot
 *
 *
 *

*/
