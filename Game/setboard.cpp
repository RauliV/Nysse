#include "setboard.hh"
//#include "playerturndialog.hh"
#include "QDebug"


std::shared_ptr<City> cityPtrSet;


// Koska Locationin rakentaja ei automaattisesti aseta pikselikoortinaatteja
// karttakoordinaattien perusteella, konversioapuohjelmat tässä.

int xFromEast(int eastcoord)
{
    return static_cast<int>((eastcoord - 3327034) * 0.333333);
}

int yFromNorth(int northcoord)
{
    return static_cast<int>((northcoord - 6824642) * 0.333333);
}

int EastFromX(int x)
{
    return static_cast<int>(x/0.333333 + 3327034);
}

int NorthFromY(int y)
{
    return static_cast<int>(y/0.333333 + 6824642);
}

void initScreen(std::shared_ptr<Interface::ICity> city)
{
    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);
    city->setBackground(tausta_iso, tausta_pieni);
    cityPtrSet = std::dynamic_pointer_cast<City>(city);

}


void clearPassengers()
{
    for (auto const& stop : cityPtrSet->getStops())
    {
        for (auto const& passenger : stop->getPassengers())
        {
            cityPtrSet->removeActor(passenger);
        }
    }
}


void startingPointsSetup()
{
    //Luodaan pelille random maali
    Interface::Location goalLocation = getRandomLocation();
    cityPtrSet->setGoalLocation(goalLocation);

    // Haetaan pelaajien aloituspisteitä, kunnes etäisyys maaliin
    // riittävän samanlainen (treshold)
    for (auto const&  player : cityPtrSet->getPlayerList())
    {
        Interface::Location startingPoint = getRandomLocation();
        startingPoint.setXY(getRandomLocation().giveX(),
        getRandomLocation().giveY());

        // Etäisyys targetLocationin ja arvotun pisteen välillä
        double distance = Interface::Location::calcDistance(startingPoint,
               cityPtrSet->getGoalLocation()); // Etäisyys targetLocationin ja arvotun pisteen välillä

        //Kunnes tresholdin sisällä.
        while (distance < (DISTANCE_TO_TARGET-DISTANCE_TRESHOLD) or
            (distance > (DISTANCE_TO_TARGET+DISTANCE_TRESHOLD)))

        {
            Interface::Location startingPoint = getRandomLocation();
            distance = Interface::Location::calcDistance(startingPoint, cityPtrSet->getGoalLocation());
        }

        //kun löytynyt, mene sinne
        player->move(startingPoint);
    }
}


Interface::Location getRandomLocation ()
{
    int randomX = (rand() % MAP_WIDTH) + MAP_NORTH_EAST_CUT;
    int randomY = rand() % MAP_HEIGHT  + MAP_NORTH_EAST_CUT;
    Interface::Location rndLocation;
    rndLocation.setXY(randomX,randomY);

    return rndLocation;
}

void createTaxisScooters()
{


    for (int it = 0; it < VEHICLE_COUNT; it++)
    {
        std::shared_ptr<Taxi> taxiPtr = std::make_shared<Taxi> ();
        std::shared_ptr<Scooter> scooterPtr = std::make_shared<Scooter> ();
        taxiPtr->move(getRandomLocation());
        scooterPtr->move(getRandomLocation());

        cityPtrSet->addActor(scooterPtr);
        cityPtrSet->addActor(taxiPtr);
    }
}

void createAtmsBars()
{
    // Bars
    std::list<std::shared_ptr<Bar>> bList = {};


    short int pilot = rand() % BAR_COUNT;

    //Arvotaan baarinumero, jossa pilotti
    for (int it = 0; it < BAR_COUNT; it++)
    {
        std::shared_ptr<Bar> barPtr = std::make_shared<Bar> ();
        barPtr->setLocation(getRandomLocation());
        if (it == pilot)
        {
            barPtr -> setPilot(true);
        }
        else
        {
            barPtr -> setPilot(false);
        }
        bList.push_back(barPtr);
        cityPtrSet->addStop(barPtr);
    }
    //Kaupungin juottolat kaupunkiolioon
    cityPtrSet->setBarList(bList);

    //Atms

    std::list<std::shared_ptr<Atm>> aList = {};

    for (int it = 0; it < ATM_COUNT; it++)
    {
        std::shared_ptr<Atm> atmPtr = std::make_shared<Atm> ();
        atmPtr->setLocation(getRandomLocation());

        aList.push_back(atmPtr);
        cityPtrSet->addStop(atmPtr);

    }
    //Kaupungin automaatit kaupunkiolioon
    cityPtrSet->setAtmList(aList);
}

std::list <std::shared_ptr<Player>> getPlayers()
{
    return cityPtrSet->getPlayerList();
}



std::string getSubClass (std::shared_ptr<Interface::IActor> iActor )
{
        if (std::dynamic_pointer_cast<Taxi>(iActor) != 0)
        {
            return "taxi" ;
        }
        else if (std::dynamic_pointer_cast<CourseSide::Nysse>(iActor) != 0)
        {
            return "nysse";
        }

        else if (std::dynamic_pointer_cast<Scooter>(iActor) != 0)
        {
            return "scooter";
        }
        else if (std::dynamic_pointer_cast<CourseSide::Passenger>(iActor) != 0)
        {
            return "passenger";
        }
        return "";
}




// Luo pelaajaoliot "Game Start" signaalista.
// Tallentaa kaupungin pelaajaolioiden osoitteet kaupungin pelaajaluetteloon
std::shared_ptr<GameEngine> createPlayers(std::vector<std::pair<std::string, std::string>>& playerSpecs)
{
    std::list <std::shared_ptr<Player>> playerList = {};
    std::vector<std::shared_ptr<Player>> playerVec ={};

    for (auto const&  player : playerSpecs)
    {
        std::shared_ptr<Player> playerPointer =
                std::make_shared<Player> (player.first, player.second);
        //playerPointer->resetRoute();
        playerList.push_back(playerPointer);
        playerVec.push_back(playerPointer);
        cityPtrSet->addActor(playerPointer);
    }

    //pelaajalista city-olioon
    cityPtrSet->setPlayerList(playerList);

    startingPointsSetup();
    auto gg = playerList.front();
    std::shared_ptr<GameEngine> myGame = std::make_shared<GameEngine>
            (playerList.front(), cityPtrSet, cityPtrSet->getGoalLocation());
    myGame->addPlayerVec(playerVec);
    myGame->addActorItems();
    myGame->addStaticItems();

    return myGame;

}
/*
void setBoard (std::vector<std::pair<std::string, std::string>> playerSpecs)
{
    createPlayers(playerSpecs);
    createAtmsBars();
    createTaxisScooters();
    startingPointsSetup();
    clearPassengers();
    addActorItems();
    addStaticItems();

}*/

