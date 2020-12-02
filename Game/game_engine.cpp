#include "game_engine.h"
#include "setboard.hh"
#include "actors/taxi.hh"

std::shared_ptr<City> cityPtr;


void theEnd()
{

}

void onTheTick(std::shared_ptr<Player>  player)
{
    if (cityPtr->isGameOver() == true)
    {
        theEnd();
    }

    if (player->giveLocation() == player->getChosenLocation())
    {
        //arriveDestination (player);
    }


}


// Laskee reitin linnuntietä paikasta A paikkaan B jaettun STEPSiin osaan.
std::shared_ptr<std::vector<Interface::Location>> calculatePlayerRoute (Interface::Location A,
                                                      Interface::Location B)
{
    std::shared_ptr<std::vector<Interface::Location>> returnVector = {};
    int aX = A.giveX();
    int aY = A.giveY();
    double xMovement = B.giveX() - aX;
    double yMovement = B.giveY() - aY;
    double xStep = xMovement / STEPS;
    double yStep = yMovement / STEPS;
    for (int it = 1; it < STEPS; it ++){


        std::pair <int, int> coord = {aX + (it*xStep),
                                      aY + (it *yStep)};
        Interface::Location loc (coord.first, coord.second);

        returnVector->push_back(loc);
    }

    return returnVector;

}

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


//tämä voisi varmaan mennä ui:n puolelle, lähelle playerturndialogia

void stepInVehicle(std::shared_ptr<Player> player, std::shared_ptr<Interface::IVehicle> vechile)
{
    player->getInVechile(vechile);

    //poista actori käytön jälkeen?

    //Bussi -> jos ei jo ollut ja jos rahaa eikä liikaa kännissä - astu sisään
    //Scooter -> jos akkua ja rahaa eikä liikaa kännissä
    //Taksi -> jos rahaa eikä liikaa kännissä
}

void arriveDestination(std::shared_ptr<Player> player,int x,int y)

{   Interface::Location loc(0,0);
    player->setIdle(true);
    player->setChosenLocation(loc);
    player->setRouteVector({});


    //kulkuneuvolocation = playerlocation

    // wantedlocation = "";
    // jos wanted_destination on baari -> bar(player)
    // jos wanted_destination on atm -> atm(player)
    // jos wanted_destination on stop -> stop(player)

    //movedActors remove(player)


}

//voi klikata vain, jos player idle = ei baarissa tai matkalla
void onTheClick(std::shared_ptr<Player> player, Interface::Location loc)
{
    std::vector<std::shared_ptr<Interface::IActor>> actorsNear =
            cityPtr->getNearbyActors(loc);

    if (actorsNear.size()==0)
    {
        qDebug() << "There's no one nearby";
    }
    else if (actorsNear.size()>1)
    {
        qDebug () << "Choose your poison Dialog";
    }
    else
    {
       player->setChosenLocation(loc);
       player->setRouteVector(calculatePlayerRoute(player->giveLocation(), loc));
    }


}

/*for (auto const& actor : cityPtrSet->getActors()){
Interface::Location aLoc = actor->giveLocation();
cityPtrSet->getWindow()->addActor(aLoc.giveX(), aLoc.giveY(),1);
}
*/

void matkalla();
void baarissa();

// nysset ja matkustajat liikkuvat itse?
void movePlayer(std::shared_ptr<Player> player){

    if (player->inWhichVehicle()->getName() == "scooter")
    {
        player->increaseSteps(2);
    }

    else if (player->inWhichVehicle()->getName() == "taxi")
    {
        player->increaseSteps(3);
    }
    else
    {
        player->increaseSteps(1);
    }

    Interface::Location newLoc = player->getRouteVector()->at(player->getCurrentSteps());
    player->move(newLoc);
    cityPtr->actorMoved(player);
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
    }


    std::shared_ptr<Taxi> taksi = std::make_shared<Taxi> ();
   /* std::shared_ptr<Interface::IVehicle> veh =
            std::dynamic_pointer_cast<Interface::IVehicle>(taksi);*/

    auto ppl = cityPtr->getPlayerList().front();
    ppl->setChosenLocation(cityPtr->getBarList().front()->getLocation());
    while (ppl->getCurrentSteps() < 90 )
    {
        movePlayer(ppl);
        qDebug() << ppl->getCurrentSteps()<< ppl->giveLocation().giveX() << ppl->giveLocation().giveY();
    }

    //ppl->getInVechile(veh);
    ppl->resetRoute();

    while (ppl->getCurrentSteps() < 90 )
    {
        movePlayer(ppl);
        qDebug() << ppl->getCurrentSteps()<< ppl->giveLocation().giveX() << ppl->giveLocation().giveY();
    }


}


void startYourEngines(std::shared_ptr<Interface::ICity> cPtr)
{
    cityPtr = std::dynamic_pointer_cast<City>(cPtr);

    //tämä siksi, ettei tarvitse aina testattaessa klikkailla.


    //Setboard funktioita
    startingPointsSetup();
    createAtmsBars();
    //updateActorsLocations();

    for (auto const& item : cityPtr->getActors())
    {
        Interface::Location aLoc = item->giveLocation();
        cityPtr->getWindow()->addActor(aLoc.giveX(), aLoc.giveY(), 2
                               ,SCOOTER_ICON_FILE, item);

    }

    addStaticItems();

    //testailuja

    //teststuff();

};

