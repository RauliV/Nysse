#include "game_engine.h"





std::shared_ptr<City> cityPtr;

void initScreen(std::shared_ptr<Interface::ICity> city)
{
    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);
    city->setBackground(tausta_iso, tausta_pieni);


    //city->get_window()->menu;

    //city->get_window()->centralWidget()->DrawWindowBackground z;

}



void bar(std::shared_ptr<Player> player){

    // mitä tapahtuu, kun pelaaja saapuu baariin


}

void atm(std::shared_ptr<Player> player){

    // mitä tapahtuu, kun pelaaja saapuu automaatille


}

void stop(std::shared_ptr<Player> player){

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
    cityPtr->actorMoved(player);
}



Interface::Location getRandomLocation (){

    int randomX = rand() % 501;
    int randomY = rand() % 501;
    Interface::Location rndLocation(randomX, randomY);

    return rndLocation;

}


void startingPointsSetup()
{

    //Luodaan pelille random maali
    Interface::Location targetLocation = getRandomLocation();


    //vakioita. Voisi ehkä määritellä const XXXXX.

    int distanceToTarget = 400;
    int distanceTreshold = 10;


    // tämä tieto settingsdialogista
    int playerCount = 4;


    std::list <std::shared_ptr<Interface::IActor>> playerList = {};


    for (int it = 0; it < playerCount; it++){

        // pelaajaoliot listaan
        std::shared_ptr<Interface::IActor> playerPointer = std::make_shared<Player> ();
        playerList.push_back(playerPointer);

        // haetaan pelaajien aloituspisteitä, kunnes etäisyys maaliin
        // riittävän samanlainen (treshold)
        double distance = getRandomLocation().calcDistance(getRandomLocation(),
                                                   targetLocation);
        while (distance < (distanceToTarget-distanceTreshold) or
            (distance > (distanceToTarget+distanceTreshold))){

            distance = getRandomLocation().calcDistance(getRandomLocation(),targetLocation);
        }


        qDebug() << "Player " << it << "start location is: ";
        qDebug() << getRandomLocation().giveX() << getRandomLocation().giveX();
        playerPointer->move(getRandomLocation());

    }

    //pelaajalista city-olioon
    cityPtr->setPlayerList(playerList);
}

void updateActors(){


    for (auto const& actor : cityPtr->getActors()){
        cityPtr->getWindow()->addActor(actor->giveLocation().giveX(),
                                        actor->giveLocation().giveY(),1);
    }


}

void startYourEngines(std::shared_ptr<Interface::ICity> icity){


cityPtr = std::dynamic_pointer_cast<City>(icity);

startingPointsSetup();  // luo pelaajaoliot ja arpoo aloituspisteet.
                        // puuuttuu atm ja bar -oliot

/*
cityPtr->get_window()->setSize(500,500);
cityPtr->get_window()->updateCoords(1,1);
//jos pelaaja ei idle -> liikuta
//muuten
*/
/*
 * Jos pelaajaActor on lähellä kohdetta
std::vector<std::shared_ptr<Interface::IActor>> NbAct =
cityPtr->getNearbyActors(wanted_destination(pelaaja_vuorossa))
if ( std::find(actorsList_.begin(), actorsList_.end(), player) != actorsList_.end())

{
    arriveDestination();
};

else move;


*/





};
