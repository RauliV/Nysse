#include "gameengine.h"
#include "setboard.hh"
#include "actors/taxi.hh"
#include <boost/any.hpp>

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
{   std::vector<Interface::Location> returnVector;
    int aX = A.giveX();
    int aY = A.giveY();
    double xMovement = B.giveX() - aX;
    double yMovement = B.giveY() - aY;
    double xStep = xMovement / STEPS;
    double yStep = yMovement / STEPS;
    for (int it = 1; it < STEPS; it ++){


        std::pair <int, int> coord = {aX + (it*xStep),
                                      aY + (it *yStep)};
        Interface::Location loci;
        loci.setXY(coord.first, coord.second);

        returnVector.push_back(loci);
    }
    std::shared_ptr<std::vector<Interface::Location>> returnVectorPtr;
    returnVectorPtr = std::make_shared<std::vector<Interface::Location>> (returnVector);
    return returnVectorPtr;

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

void stepInVehicle(std::shared_ptr<Player> player,
                   std::shared_ptr<Interface::IVehicle> vehicle)
{
    // astuu nysseen

    if (getSubClass(vehicle) == "nysse")
     {
        std::shared_ptr<CourseSide::Nysse> nysse =
                std::dynamic_pointer_cast<CourseSide::Nysse> (vehicle);

        std::shared_ptr<CourseSide::Stop> nStop = nysse->getStop().lock();
        std::shared_ptr<CourseSide::Stop> nFinalStop = nysse->getFinalStop().lock();
        std::shared_ptr<CourseSide::Stop> nNextStop;


        if (player->getDrunkness() > 3)
         {
             //emit cantMoveDrunk;

         }
         else if (player->getCash() < BUSS_FARE)
         {
             //emit cantMoveCash;
         }

         else if (nStop == nFinalStop)
         {
            //emit cantMoveFinalStop
         }
         else
         {  //Etsitään seuraava pysäkki
            for (int it = 0; it < cityPtr->getStops().size(); it++)
            {
                if (cityPtr->getStops().at(it) == nStop)
                {
                    nNextStop = std::dynamic_pointer_cast<CourseSide::Stop>
                            (cityPtr->getStops().at(it+1));
                }
             }
             Interface::Location nextLoc = nNextStop->getLocation();
             player->spendCash(BUSS_FARE);
             player->resetRoute();
             player->getInVechile(vehicle); //pelaajan ikonin muutos
             std::shared_ptr<CourseSide::Nysse> nysse =
                     std::dynamic_pointer_cast<CourseSide::Nysse> (vehicle);
             player->setChosenLocation(nextLoc);
             player->setIdle(false);

         }

     }
     else
    {

        player->getInVechile(vehicle);
        player->setIdle(false);
    }


    //poista actori käytön jälkeen?

    //Bussi -> jos ei jo ollut ja jos rahaa eikä liikaa kännissä - astu sisään
    //Scooter -> jos akkua ja rahaa eikä liikaa kännissä
    //Taksi -> jos rahaa eikä liikaa kännissä
}

void arriveDestination(std::shared_ptr<Player> player, Interface::Location dest)

{
    player->setIdle(true);
    player->resetRoute();
    //set playericon


    //kutsu playerturnia?
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
   //    if (onkosullarahee) Jos nyssessä vektori = bussivektori
       Interface::Location aaa = player->giveLocation();
       player->setChosenLocation(loc);
       player->setRouteVector(calculatePlayerRoute(aaa, loc));
    }


}


//calculateTotalCosts

//Liikuta pelaajaa reitillä
void movePlayer(std::shared_ptr<Player> player){

    player->takeStep(); //päivittää askeleet ja kustannukset

    int cSteps = player->getCurrentSteps();

    if (player->getRouteVector() != nullptr)
    {
        Interface::Location newLoc = player->getRouteVector()->at(cSteps);
        //newLoc.setNorthEast(NorthFromY(newLoc.giveY()), EastFromX(newLoc.giveX()));
        player->move(newLoc);
        cityPtr->actorMoved(player);
        if (cSteps == STEPS)
        {
            arriveDestination(player, player->getChosenLocation());
        }
    } else
    {
        qDebug() << "Ei reittiä pelaajalla";
    }

}



void teststuff()
{
    std::string nimi = "pekka";
    std::string vari = "musta";
    std::shared_ptr<Player> player = std::make_shared<Player> (nimi, vari);
    //Testejä

    // Playerdata
/*
    auto list = cityPtr->getPlayerList();
    int it = 1;
    for (auto const& player : list){
        Interface::Location loc = player->giveLocation();
        loc.setXY(xFromEast(player->giveLocation().giveEasternCoord()),
                  yFromNorth(player->giveLocation().giveNorthernCoord()));
        //Interface::Location y = loc.setXY(player->giveLocation().giveEasternCoord();


        QString qname = QString::fromStdString(player->getName());
        QString qcolour = QString::fromStdString(player->getColour());
        qDebug() << "Pelaaja " << it << ": " << qname;
        qDebug() << "Väri on: " << qcolour;
        qDebug() << "Paikassa: ";
        qDebug() << "Maali: " << cityPtr->getGoalLocation().giveX() << cityPtr->getGoalLocation().giveY();
        qDebug() << "Pelaaja: " << loc.giveX() << loc.giveY();

        it ++;
    }
*/

    // Steps
    /*auto ppl = cityPtr->getPlayerList().front();
    onTheClick(ppl, cityPtr->getBarList().front()->getLocation());
    while (ppl->getCurrentSteps() < STEPS - 5 )
    {
        movePlayer(ppl);
        qDebug() << ppl->getCurrentSteps()<< ppl->giveLocation().giveX() << ppl->giveLocation().giveY();
    }

    //ppl->getInVechile(veh);
    ppl->resetRoute();

    while (ppl->getCurrentSteps() < STEPS - 5 )
    {
        movePlayer(ppl);
        qDebug() << ppl->getCurrentSteps()<< ppl->giveLocation().giveX() << ppl->giveLocation().giveY();
    }
*/

     //Step in vehicle


    std::shared_ptr<Taxi> taxi = std::make_shared<Taxi> ();
    stepInVehicle(player, taxi);








}
void startYourEngines(std::shared_ptr<Interface::ICity> cPtr)
{
    cityPtr = std::dynamic_pointer_cast<City>(cPtr);


    //Setboard funktioita
    createAtmsBars();
    createTaxisScooters();
    addStaticItems();
    //addActorItems();
    clearPassengers();
    startingPointsSetup();
    //teststuff();

}

