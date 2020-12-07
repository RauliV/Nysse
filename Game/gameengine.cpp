#include "gameengine.h"
#include "setboard.hh"
#include "actors/taxi.hh"
#include <boost/any.hpp>

std::shared_ptr<City> cityPtr;


//Loppufanfaarit/Aika ym.
void theEnd()
{

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

double calculateCost(std::shared_ptr<Player> player,
                     std::shared_ptr<Interface::IVehicle> vehicle,
                     Interface::Location targeLocation)
{

    //Korjattava kustannusten ja nopeuden määrittäminen kulkuneuvoon
    // Nykyisillä specseillä menee koskeen.

    return 5;
}



//Pelaaja baariin

QString enterBar(std::shared_ptr<Player> player,
              std::shared_ptr<Bar> bar)
{
    //tarkista onko rahee
    if (player->getCash() < 6) // Tästä vakio!! 6 e tuoppi
    {
        return "cantDrinkCash";
    }
    else
    {   player->drink(1);
        player->spendCash(6);
        if (bar->isPilotInBar())
        {
            //pilotIsFound();
            //loppumatkashöy
            // end(); -> game is over (jos vain voittaja haetaan)
        }

        //Odotetaan baarissa tickejä/siirretään vain vuoro?
        // tässä lopetetaan vuoro
        player->setIdle(false); //Ota pois seuraavan vuoron jälkeen.
        player->resetRoute();
        return "Hyvvee kaliaa";
    }
}



//Pelaaja siirtyy pysäkille odottamaan nysseä
//Tässä versiossa bussia ei varsinaisesti odoteta, vaan matka alkaa
//heti sen bussin kyydissä, joka pysähtyy pysäkille
//Määränpää on bussin seuraava pysäkki
//Palauttaa virheilmoitukset, jos ei matka onnistu ja "" jos ok.

QString enterStop(std::shared_ptr<Player> player,
                  std::shared_ptr<CourseSide::Stop> stop)
{
    std::shared_ptr<CourseSide::Nysse> nToWait;

    //Käydään läpi actorit listasta
    for (auto const& actor : cityPtr->getActors())
    {

        //Jos actor on nysse
        if (std::dynamic_pointer_cast<CourseSide::Nysse> (actor) != 0)
        {

           std::shared_ptr<CourseSide::Nysse> nysse =
                   std::dynamic_pointer_cast<CourseSide::Nysse> (actor);

           //Mikä bussi kulkee pysäkillä
           auto const nTimeRoute = nysse->getTimeRoute();
           for (auto const& nStop : nTimeRoute)
           {
               if (nStop.second.second.lock()  == stop)
               {
                   nToWait = nysse;
                   break;
               }
               else nToWait = nullptr;
           }
        }
    }

    // Jos löytyi pysäkiltä kulkeva bussi
    if (nToWait != nullptr)
    {
        std::shared_ptr<CourseSide::Stop> nFinalStop = nToWait->getFinalStop().lock();
        std::shared_ptr<CourseSide::Stop> nNextStop;

        //Tutkitaan bussimatkustamisen ehdot
        if (player->getDrunkness() > 3)
         {
             return "cantMoveDrunk";

         }
         else if (player->getCash() < BUSS_FARE)
         {
             return "cantMoveCash";
         }

         else if (stop == nFinalStop)
         {
            return "cantMoveFinalStop";
         }

         else
         {
            //Bussilla voidaan matkustaa -> Etsitään seuraava pysäkki
            for (unsigned int it = 0; it < cityPtr->getStops().size(); it++)
            {
                if (cityPtr->getStops().at(it) == stop)
                {
                    nNextStop = std::dynamic_pointer_cast<CourseSide::Stop>
                            (cityPtr->getStops().at(it+1));
                }
             }

             //Matka seuraavalle pysäkille voi alkaa
             Interface::Location nextLoc = nNextStop->getLocation();
             player->spendCash(BUSS_FARE);
             player->resetRoute();
             player->getInVechile(nToWait); //pelaajan ikonin muutos
             std::shared_ptr<CourseSide::Nysse> nysse =
                     std::dynamic_pointer_cast<CourseSide::Nysse> (nToWait);
             player->setChosenLocation(nextLoc);
             player->setIdle(false);
             return "";
         }
     }
     else
    {
        return "No buses will come today";
    }
}






int calculateBatteryUsage(std::shared_ptr<Scooter> scooter,
                          Interface::Location targetLocation)
{
    return 5; //laskettava uudelleen
}


//Matkustetaan muuten kuin bussilla, eli määränpää annetu

QString startJourney(std::shared_ptr<Player> player,
                     std::shared_ptr<Interface::IVehicle> vehicle,
                     Interface::Location targetLocation)
{

    if (getSubClass(vehicle) == "scooter")
     {

        std::shared_ptr<Scooter> scooter =
                std::dynamic_pointer_cast<Scooter> (vehicle);


        if (player->getDrunkness() > scooter->getMaxPromilleLevel())
         {
             return "cantMoveDrunk";

         }
         else if (player->getCash() < calculateCost(player, scooter, targetLocation))
         {
             return "cantMoveCash";
         }

         else if (scooter->getBatteryStatus() < calculateBatteryUsage(scooter, targetLocation))
         {
            return "cantMoveBattery";
         }
         else
         {
            //Aloitetaan matka - muista lisätä takeSteppiin myös rahan
            //ja akun kuluminen
            player->resetRoute();
            player->getInVechile(scooter);
            player->setIdle(false);
            player->setChosenLocation(targetLocation);
            player->setRouteVector(calculatePlayerRoute(player->giveLocation(),
                                                        targetLocation));
            return "matka kohteeseen alkaa";
         }

     }
     else if (getSubClass(vehicle) == "taxi")
     {

       std::shared_ptr<Taxi> taxi =
               std::dynamic_pointer_cast<Taxi> (vehicle);


       if (player->getDrunkness() > taxi->getMaxPromilleLevel())
        {
            return "cantMoveDrunk";

        }
        else if (player->getCash() < calculateCost(player, taxi, targetLocation))
        {
            return "cantMoveCash";
        }

        else
        {
           //Aloitetaan matka
           player->resetRoute();
           player->getInVechile(taxi);
           player->setIdle(false);
           player->setChosenLocation(targetLocation);
           player->setRouteVector(calculatePlayerRoute(player->giveLocation(),
                                                       targetLocation));
           return "Matka kohteeseen alkaa";
        }
    }
    else
    {
        return "En tunnista kulkuneuvoa";
    }
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
    movePlayer(player);


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






}
void startYourEngines(std::shared_ptr<Interface::ICity> cPtr)
{
    cityPtr = std::dynamic_pointer_cast<City>(cPtr);


    //Setboard funktioita


}

