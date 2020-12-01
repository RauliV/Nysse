#include "setboard.hh"


std::shared_ptr<City> cityPtrSet;


// Koska Locationin rakentaja ei automaattisesti aseta pikselikoortinaatteja
// karttakoordinaattien perusteella. Siksi röyhkeästi kopioitu Locationin
// private metodit.
int xFromEast(int eastcoord)
{
    return static_cast<int>((eastcoord - 3327034) * 0.333333);
}



int yFromNorth(int northcoord)
{
    return static_cast<int>((northcoord - 6824642) * 0.333333);
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
        //startingPoint.setXY(getRandomLocation().giveX(), getRandomLocation().giveY());
        double distance = Interface::Location::calcDistance(startingPoint,cityPtrSet->getGoalLocation()); // Etäisyys targetLocationin ja arvotun pisteen välillä

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
    int randomX = rand() % MAP_WIDTH;
    int randomY = rand() % MAP_HEIGHT;
    Interface::Location rndLocation;
    rndLocation.setXY(randomX,randomY);

    return rndLocation;
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
    }
    cityPtrSet->setBarList(bList);



}

std::list <std::shared_ptr<Player>> getPlayers(){
    return cityPtrSet->getPlayerList();
}

void createActorItems()
{
    for (auto const& actor : cityPtrSet->getActors()){
        Interface::Location aLoc = actor->giveLocation();
        cityPtrSet->getWindow()->addActor(aLoc.giveX(), aLoc.giveY(),1);
    }

}


// Luo pelaajaoliot "Game Start" signaalista.
// Tallentaa kaupungin pelaajaolioiden osoitteet kaupungin pelaajaluetteloon
void createPlayers(std::vector<std::pair<std::string, std::string>> playerSpecs)
{
    std::list <std::shared_ptr<Player>> playerList = {};

    for (auto const&  player : playerSpecs)
    {
        std::shared_ptr<Player> playerPointer = std::make_shared<Player> (player.first, player.second);
        playerList.push_back(playerPointer);
    }

    //pelaajalista city-olioon
    cityPtrSet->setPlayerList(playerList);

}



