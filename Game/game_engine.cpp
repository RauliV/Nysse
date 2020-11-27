#include "game_engine.h"






//Kassa (xx)

//onko liikkunut (QTime x QTime x1 loc !)
//päivitä
//saapuu kohteeseen ->

Interface::Location getRandomLocation (){

    int randomX = rand() % 501;
    int randomY = rand() % 501;
    Interface::Location rndLocation(randomX, randomY);

    return rndLocation;

    // arpoo lokaation bussireiteiltä
}


void startingPoints_setup()
{

    Interface::Location targetLocation = getRandomLocation();

    //osa vakioita, osa tiedoista muualta.
    int playerCount = 4;
    int distanceToTarget = 400;
    int distanceTreshold = 10;
    std::list <std::shared_ptr<Player>> playerList = {};


    for (int it = 0; it < playerCount; it++){
        std::shared_ptr<Player> playerPointer = std::make_shared<Player> ();
        playerList.push_back(playerPointer);
        int distance = getRandomLocation().calcDistance(getRandomLocation(),
                                                   targetLocation);
        while (distance < (distanceToTarget-distanceTreshold) or
            (distance > (distanceToTarget+distanceTreshold))){

            distance = getRandomLocation().calcDistance(getRandomLocation(),targetLocation);
        }
        qDebug() << "Player " << it << "start location is: ";
        qDebug() << getRandomLocation().giveX() << getRandomLocation().giveX();
        playerPointer->move(getRandomLocation());

    }







}



void make_game(std::shared_ptr<Interface::ICity> city){


std::shared_ptr<City> kaupunki = std::dynamic_pointer_cast<City>(city);



kaupunki->getGame()->finalizeGameStart();


//käy läpi kaikki pelaajat ja asettaa niille aloitus koordinaatit



   // for (it = playerList.begin();it < playerList.end())
   // Interface::Location dist = playerList[1].


//Yksittäisiä kokeiluja


//std::shared_ptr<CourseSide::Logic> game = std::make_shared<CourseSide::Logic> ();
//

//city->gameObjectPtr->takeCity(city);

 //std::shared_ptr<CourseSide::Logic> gameObjectPtr = std::make_shared<CourseSide::Logic>();

//&gameObjectPtr(game);
//gameObjectPtr->takeCity(city);

 //City *d = dynamic_cast<Derived*>(b);
//City *city_object = dynamic_cast<std::shared_ptr<Interface::ICity*>> (city.get());
//addActors(city);

//std::shared_ptr <City> new_d = dynamic_cast<std::shared_ptr <City>>
 //                              (std::shared_ptr<Interface::ICity>);



//Game->finalizeGameStart();
/*player -> playerlocation
city -> target location*/


};
