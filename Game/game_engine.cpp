#include "game_engine.h"
#include "setboard.hh"
#include "unistd.h"

std::shared_ptr<City> cityPtr;


void bar(std::shared_ptr<Player> player)
{

    // mitä tapahtuu, kun pelaaja saapuu baariin
    // aika, rahat, känni

}


void atm(std::shared_ptr<Player> player)
{

    // mitä tapahtuu, kun pelaaja saapuu automaatille
    // jos ei vielä nostettu täältä, jos saldoa?


}


void stop(std::shared_ptr<Player> player)
{

    // mitä tapahtuu, kun pelaaja saapuu pysäkille

}

void stepInVehicle(std::shared_ptr<Player> player)
{
    //Bussi -> jos ei jo ollut ja jos rahaa eikä liikaa kännissä - astu sisään
    //Scooter -> jos akkua ja rahaa eikä liikaa kännissä
    //Taksi -> jos rahaa eikä liikaa kännissä
}

void arriveDestination(){ //välietappi
    //kulkuneuvolocation = playerlocation

    // wantedlocation = "";
    // jos ei baari -> player = idle

    // jos wanted_destination on baari -> bar(player)
    // jos wanted_destination on atm -> atm(player)
    // jos wanted_destination on stop -> stop(player)

    //movedActors remove(player)


}

//voi klikata vain, jos player idle = ei kulkuneuvossa, baarissa tai matkalla
void clicked(std::shared_ptr<Player> player, Interface::Location loc)
{
    std::vector<std::shared_ptr<Interface::IActor>> actorsNear =
            cityPtr->getNearbyActors(loc);

    if (actorsNear.size()==0)
    {
        qDebug() << "There's no one nearby";
    }
    else if (actorsNear.size()>1)
    {
        qDebug () << "Choose your poison";
    }
    else
    {
       // wantedlocation = loc;
    }


}

/*for (auto const& actor : cityPtrSet->getActors()){
Interface::Location aLoc = actor->giveLocation();
cityPtrSet->getWindow()->addActor(aLoc.giveX(), aLoc.giveY(),1);
}
*/

void updateActorsLocations()

{   //päivitetäänkö myös nysset ja matkustajat?
    //uusi lokaatio tulee, mutta ruudunpäivitys meillä?
    //Muutenhan ei ole muuta liikkuvaa, kuin pelaaja. Ikoini ja nopeus muuttuu
    //jos kulkuneuvossa


    //päivitetään muut kuin pelaajat

        //staattiset createen, eli stop, atm, bar
    for (auto const& stop : cityPtr->getStops())
    {
        Interface::Location aLoc = stop->getLocation();
        //cityPtr->getWindow()->addActor(aLoc.giveX(), aLoc.giveY(),
         //                              ifile, actor);

    }


        // atm


        // bar


       //dynaamiset actorit listasta = nysset ja passet
 /*   for (auto const& actor : cityPtr->getMovedActors())
    {
        QString ifile = "";
        Interface::Location aLoc = actor->giveLocation();

        if ( std::find(cityPtr->getStops().begin()->get(),
                       cityPtr->getStops().end()->get(),
                       actor) != cityPtr->getStops().end()->get())
        {
            ifile = BUS_STOP_ICON_FILE;
        }

        else if (std::find(cityPtr->getBarList().begin(), cityPtr->getBarList().end(),
                           actor) != cityPtr->getBarList().end())
        {
            ifile = BAR_ICON_FILE;
        }

        else if (std::find(cityPtr->getAtmList().begin(), cityPtr->getAtmList().end(),
                           actor) != cityPtr->getAtmList().end())
        {
            ifile = ATM_ICON_FILE;
        }


        cityPtr->getWindow()->addActor(aLoc.giveX(), aLoc.giveY(), ifile, actor);

*/


        // ja pelaajat lopuksi - saako dynamiccastpointterilla iactoriksi
     for (auto const& player : cityPtr->getPlayerList())
     {
     }




}

// nysset ja matkustajat liikkuvat itse?
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

        for (auto const& it : cityPtr->getBarList()){
            qDebug() << "Bar nr: " << it->isPilotInBar();

        }
    }

  /*  for (int it = 0; it < 10;it ++)
    {
        createActorItems();
        sleep(1);
    }*/
}


void startYourEngines(std::shared_ptr<Interface::ICity> cPtr)
{
    cityPtr = std::dynamic_pointer_cast<City>(cPtr);

    //tämä siksi, ettei tarvitse aina testattaessa klikkailla.
    int pC = 1;
    std::pair<std::string, std::string> pP = {"Pekka", "musta"};
    std::vector<std::pair<std::string, std::string>> pV {pP};
    createPlayers(pV);

    //Setboard funktioita
    startingPointsSetup();
    createAtmsBars();
    createActorItems();

    //testailuja

    teststuff();

};

