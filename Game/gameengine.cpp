#include "gameengine.hh"
#include "setboard.hh"
#include "mainwindow.h"



GameEngine::GameEngine(std::shared_ptr<Player>& playerInTurn,
                       std::shared_ptr<City>& gameCity,
                       Interface::Location goalLocation):
    playerInTurn_(playerInTurn),
    gameCity_(gameCity),
    goalLocation_(goalLocation)

{

}

GameEngine::~GameEngine()
{

}
//Loppufanfaarit/Aika ym.

void GameEngine::setGoalLocation(Interface::Location location)
{
    goalLocation_ = location;
}

void theEnd()
{

}

// Laskee reitin linnuntietä paikasta A paikkaan B jaettun STEPSiin osaan.
std::shared_ptr<std::vector<Interface::Location>> calculatePlayerRoute (Interface::Location A,
                                                      Interface::Location B)
{   std::vector<Interface::Location> returnVector;
    double distance = Interface::Location::calcDistance(A, B);
    int steps = distance/STEP_LENGTH; //Montako ihmisaskelta matka on

    int aX = A.giveX();
    int aY = A.giveY();
    double xMovement = B.giveX() - aX;
    double yMovement = B.giveY() - aY;
    double xStep = xMovement / steps;  //Askelen pituus näytöllä koordinaateittain
    double yStep = yMovement / steps;

    for (int it = 1; it < steps; it ++){


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
                     Interface::Location targetLocation)
{

    int cost = 0;
    auto routeVector = calculatePlayerRoute(vehicle->giveLocation(),
                                            targetLocation);
    if (getSubClass(vehicle) == "scooter")
    {
        std::shared_ptr<Scooter> vehicleObject =
                std::dynamic_pointer_cast<Scooter> (vehicle);
        cost = routeVector->size() * vehicleObject->getCostPerTick();

    }
    else if (getSubClass(vehicle) == "taxi")
    {
        std::shared_ptr<Taxi> vehicleObject =
                std::dynamic_pointer_cast<Taxi> (vehicle);
        cost = routeVector->size() * vehicleObject->getCostPerTick();
    }

    return cost;

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
        player->enterBar();
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

QString GameEngine::enterStop(
                  std::shared_ptr<CourseSide::Stop> stop)
{
    std::shared_ptr<CourseSide::Nysse> nToWait;

    //Käydään läpi actorit listasta
    for (auto const& actor : gameCity_->getActors())
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
        if (playerInTurn_->getDrunkness() > 3)
         {
             return "cantMoveDrunk";

         }
         else if (playerInTurn_->getCash() < BUSS_FARE)
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
            for (unsigned int it = 0; it < gameCity_->getStops().size(); it++)
            {
                if (gameCity_->getStops().at(it) == stop)
                {
                    nNextStop = std::dynamic_pointer_cast<CourseSide::Stop>
                            (gameCity_->getStops().at(it+1));
                }
             }

             //Matka seuraavalle pysäkille voi alkaa
             Interface::Location nextLoc = nNextStop->getLocation();
             playerInTurn_->spendCash(BUSS_FARE);
             playerInTurn_->resetRoute();
             playerInTurn_->getInVechile(nToWait); //pelaajan ikonin muutos
             std::shared_ptr<CourseSide::Nysse> nysse =
                     std::dynamic_pointer_cast<CourseSide::Nysse> (nToWait);
             playerInTurn_->setChosenLocation(nextLoc);
             playerInTurn_->setIdle(false);
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
    auto routeVector = calculatePlayerRoute(scooter->giveLocation(),
                                            targetLocation);
    int batteryUsage = routeVector->size() * scooter->getBatteryPerTick();
    return batteryUsage; //laskettava uudelleen
}


//Matkustetaan muuten kuin bussilla, eli määränpää annetu

QString GameEngine::startJourney (std::shared_ptr<Interface::IVehicle> vechile,
                     Interface::Location targetLocation)
{

    if (getSubClass(vechile) == "scooter")
     {

        std::shared_ptr<Scooter> scooter =
                std::dynamic_pointer_cast<Scooter> (vechile);


        if (playerInTurn_->getDrunkness() > scooter->getMaxPromilleLevel())
         {
             return "cantMoveDrunk";

         }
         else if (playerInTurn_->getCash() < calculateCost(playerInTurn_, scooter, targetLocation))
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
            playerInTurn_->resetRoute();
            playerInTurn_->getInVechile(scooter);
            playerInTurn_->setIdle(false);
            playerInTurn_->setChosenLocation(targetLocation);
            playerInTurn_->setRouteVector(calculatePlayerRoute(playerInTurn_->giveLocation(),
                                                        targetLocation));
            return "matka kohteeseen alkaa";
         }

     }
     else if (getSubClass(vechile) == "taxi")
     {

       std::shared_ptr<Taxi> taxi =
               std::dynamic_pointer_cast<Taxi> (vechile);


       if (playerInTurn_->getDrunkness() > taxi->getMaxPromilleLevel())
        {
            return "cantMoveDrunk";

        }
        else if (playerInTurn_->getCash() < calculateCost(playerInTurn_, taxi, targetLocation))
        {
            return "cantMoveCash";
        }

        else
        {
           //Aloitetaan matka
           playerInTurn_->resetRoute();
           playerInTurn_->getInVechile(taxi);
           playerInTurn_->setIdle(false);
           playerInTurn_->setChosenLocation(targetLocation);
           playerInTurn_->setRouteVector(calculatePlayerRoute(playerInTurn_
                                         ->giveLocation(), targetLocation));
           return "Matka kohteeseen alkaa";
        }
    }
    else
    {
        return "En tunnista kulkuneuvoa";
    }
}


//Liikuta pelaajaa reitillä
void GameEngine::movePlayer(std::shared_ptr<Player> player){

    player->takeStep(); //päivittää askeleet ja kustannukset

    int cSteps = player->getCurrentSteps();

    if (player->getRouteVector() != nullptr)
    {
        Interface::Location newLoc = player->getRouteVector()->at(cSteps);
        player->move(newLoc);
        gameCity_->actorMoved(player);


        /* tätä kai ei tarvita, koska tick -runko testaa onko kohteessa
         *
         * if (cSteps == STEPS)
        {
            arriveDestination(player, player->getChosenLocation());
        }*/
    } else
    {
        qDebug() << "Ei reittiä pelaajalla";
    }

}

void GameEngine::endTurn()
{

    if (playerInTurn_ == getPlayers().back())
    {
        playerInTurn_ = getPlayers().front();
    }
    else
    {
        for (std::list<std::shared_ptr<Player>>::iterator it = getPlayers().begin();
             it != getPlayers().end(); it ++)
        {

            if (*it == playerInTurn_)
            {
                playerInTurn_ = *(it++);
            }
        }
    }
}

void GameEngine::onTheTick()
{
    if (playerInTurn_->giveLocation() == goalLocation_)
    {
        theEnd();
    }

    //jos pelaaja baarissa - vuoro menee siinä.
    if (playerInTurn_ -> isInBar())
    {
        playerInTurn_->exitBar();
        playerInTurn_->setIdle(true);
    }
    else
    {
        //Jos pelaaja saapuu kohteeseen
        if (playerInTurn_->giveLocation() == playerInTurn_->getChosenLocation())
        {
            playerInTurn_->setIdle(true);  //tästä seuraavaan vuoroon
        }
        else
        {
            movePlayer(playerInTurn_);
        }
    }
    endTurn();  //sewuraava oelaaja playerinturbisksi
}




