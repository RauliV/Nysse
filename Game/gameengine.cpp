#include "gameengine.hh"
#include "setboard.hh"
#include "mainwindow.h"

//#include "mainwindow.h"



GameEngine::GameEngine(std::shared_ptr<Player>& playerInTurn,
                       std::shared_ptr<City>& gameCity,
                       Interface::Location goalLocation):
    playerInT_(playerInTurn),
    gameCity_(gameCity),
    goalLocation_(goalLocation)

{   MainWindow* window = gameCity->getWindow().get();

    connect(window, &MainWindow::tick, this, &GameEngine::onTheTick);
    connect(window, &MainWindow::enterBar, this, &GameEngine::enterBar);
    connect(window, &MainWindow::enterStop, this, &GameEngine::enterStop);
    connect(window, &MainWindow::startJourney, this, &GameEngine::startJourney);
}

GameEngine::~GameEngine()
{

}

void GameEngine::addPlayerVec(std::vector<std::shared_ptr<Player> > playerVec)
{
    playerVec_ = playerVec;
}

void GameEngine::setGoalLocation(Interface::Location location)
{
    goalLocation_ = location;
}

void GameEngine::theEnd()
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

double GameEngine::calculateCost(std::shared_ptr<Player> player,
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

QString GameEngine::enterBar(std::shared_ptr<Bar> bar)
{
    //tarkista onko rahee

    if (playerInT_->getCash() < 6) // Tästä vakio!! 6 e tuoppi
    {
        return "cantDrinkCash";
    }
    else
    {   playerInT_->drink(1);
        playerInT_->spendCash(6);
        if (bar->isPilotInBar())
        {
            //pilotIsFound();
            //loppumatkashöy
            // end(); -> game is over (jos vain voittaja haetaan)
        }

        //Odotetaan baarissa tickejä/siirretään vain vuoro?
        // tässä lopetetaan vuoro
        playerInT_->enterBar();
        playerInT_->setIdle(false); //Ota pois seuraavan vuoron jälkeen.
        playerInT_->resetRoute();
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
               nToWait = nullptr;
           }
        }
    }

    // Jos löytyi pysäkiltä kulkeva bussi
    if (nToWait != nullptr)
    {
        std::shared_ptr<CourseSide::Stop> nFinalStop = nToWait->getFinalStop().lock();
        std::shared_ptr<CourseSide::Stop> nNextStop;

        //Tutkitaan bussimatkustamisen ehdot
        if (playerInT_->getDrunkness() > 3)
         {
             return "cantMoveDrunk";

         }
         if (playerInT_->getCash() < BUSS_FARE)
         {
             return "cantMoveCash";
         }

         if (stop == nFinalStop)
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
             playerInT_->spendCash(BUSS_FARE);
             playerInT_->resetRoute();
             playerInT_->getInVechile(nToWait); //pelaajan ikonin muutos
             std::shared_ptr<CourseSide::Nysse> nysse =
                     std::dynamic_pointer_cast<CourseSide::Nysse> (nToWait);
             playerInT_->setChosenLocation(nextLoc);
             playerInT_->setIdle(false);
             return "";
         }
     }
     else
    {
        return "No buses will come today";
    }
}


int GameEngine::calculateBatteryUsage(std::shared_ptr<Scooter> scooter,
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


        if (playerInT_->getDrunkness() > scooter->getMaxPromilleLevel())
         {
             return "cantMoveDrunk";

         }
         else if (playerInT_->getCash() < calculateCost(playerInT_, scooter, targetLocation))
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
            playerInT_->resetRoute();
            playerInT_->getInVechile(scooter);
            playerInT_->setIdle(false);
            playerInT_->setChosenLocation(targetLocation);
            playerInT_->setRouteVector(calculatePlayerRoute(playerInT_->giveLocation(),
                                                        targetLocation));
            return "matka kohteeseen alkaa";
         }

     }
     else if (getSubClass(vechile) == "taxi")
     {

       std::shared_ptr<Taxi> taxi =
               std::dynamic_pointer_cast<Taxi> (vechile);


       if (playerInT_->getDrunkness() > taxi->getMaxPromilleLevel())
        {
            return "cantMoveDrunk";

        }
        else if (playerInT_->getCash() < calculateCost(playerInT_, taxi, targetLocation))
        {
            return "cantMoveCash";
        }

        else
        {
           //Aloitetaan matka
           playerInT_->resetRoute();
           playerInT_->getInVechile(taxi);
           playerInT_->setIdle(false);
           playerInT_->setChosenLocation(targetLocation);
           playerInT_->setRouteVector(calculatePlayerRoute(playerInT_
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
{   //         gameCity_->getPlayerList().back()

    QString qstrPlayer = QString::fromStdString(playerInT_->getName());
    qDebug() << "1" << qstrPlayer;

    if (playerInT_ == playerVec_.back())
    {
        playerInT_ = getPlayers().front();
        QString qstrPlayer = QString::fromStdString(playerInT_->getName());
        qDebug() << "2" << qstrPlayer;
    }
    else
    {
        for (unsigned long it = 0; it < playerVec_.size(); it++)
        {
            if (playerVec_.at(it) == playerInT_){
                playerInT_ = playerVec_.at(it+1);
                QString qstrPlayer = QString::fromStdString(playerInT_->getName());
                qDebug() << "3" << qstrPlayer;
                break;
            }
        }
  /*      std::list<std::shared_ptr<Player>>::iterator it =
                getPlayers().begin();

        for (std::list<std::shared_ptr<Player>>::iterator it = getPlayers().begin();
             it != getPlayers().end(); it ++)
        {

            if (*it == playerInTurn_)
            {
                playerInTurn_ = *(it++);
                break;
            }
        }
        */
    }
}

void GameEngine::onTheTick()
{
    playerInT_->drink(7);  // TESTI - MUISTA POISTAA
    auto trest = playerInT_->giveLocation();


    auto test3 = goalLocation_;
    if (playerInT_->giveLocation() == goalLocation_)
    {
        theEnd();
    }

    //jos pelaaja baarissa - vuoro menee siinä.
    if (playerInT_ -> isInBar())
    {
        playerInT_->exitBar();
        playerInT_->setIdle(true);
    }
    else
    {   if (playerInT_->isIdle())
        {
            emit nextTurn(playerInT_);
        }
        //Jos pelaaja saapunut kohteeseen
        if (playerInT_->giveLocation() == playerInT_->getChosenLocation())
        {
            playerInT_->setIdle(true);  //tästä seuraavaan vuoroon
        }
        else
        {
            movePlayer(playerInT_);
        }
    }
    endTurn();  //siirtyy seuraavaan pelaajaan
}


void GameEngine::addActorItems ()
{
    for (auto const& actor : gameCity_->getActors())
    {
        int aX = actor->giveLocation().giveX();
        int aY = actor->giveLocation().giveY();

        emit addActor(aX, aY, 0, actor);
    }
}

void GameEngine::addStaticItems()
{

    // Maalista punainen X ?

    for (auto const& stop : gameCity_->getStops())
    {
        Interface::Location aLoc = stop->getLocation();
        
        emit addStaticItem(aLoc.giveX(), aLoc.giveY(), stop);
    }


    for (auto const& bar : gameCity_->getBarList())
    {
        Interface::Location aLoc = bar->getLocation();

        //emit addStaticItem(aLoc.giveX(), aLoc.giveY(), bar);

    }
}





