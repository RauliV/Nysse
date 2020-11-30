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

    int randomX = rand() % 100;
    int randomY = rand() % 100;
    Interface::Location rndLocation(randomX, randomY);

    return rndLocation;

}

std::list<std::shared_ptr<Player>> getPlayers()
{
    return cityPtr->getPlayerList();
}


void startingPointsSetup()
{

    //Luodaan pelille random maali
    Interface::Location targetLocation = getRandomLocation();


    //vakioita. Voisi ehkä määritellä const XXXXX.

    int distanceToTarget = 80;
    int distanceTreshold = 10;


    // haetaan pelaajien aloituspisteitä, kunnes etäisyys maaliin
    // riittävän samanlainen (treshold)
    for (auto const&  player : cityPtr->getPlayerList())
    {
        Interface::Location startingPoint = getRandomLocation();
        int distance = startingPoint.calcDistance(startingPoint,targetLocation); // Etäisyys targetLocationin ja arvotun pisteen välillä

        while (distance < (distanceToTarget-distanceTreshold) or
            (distance > (distanceToTarget+distanceTreshold)))           //Kunnes tresholdin sisällä.
        {

            Interface::Location startingPoint = getRandomLocation();
            distance = startingPoint.calcDistance(startingPoint,targetLocation);
        }


        //kun löytynyt, mene sinne
        player->move(startingPoint);  //siirtyykö heti vai liikkuuko tickeittäin?

    }

}


void teststuff()
{


    //Testejä

    auto list = cityPtr->getPlayerList();
    int it = 1;
    for (auto const& player : list){
        Interface::Location loc = player->giveLocation();
        QString qname = QString::fromStdString(player->getName());
        QString qcolour = QString::fromStdString(player->getColour());
        qDebug() << "Pelaaja " << it << ": " << qname;
        qDebug() << "Väri on: " << qcolour;
        qDebug() << "Paikassa: ";

        loc.printBoth();
    }

    Interface::Location prs(90000,40000);
    prs.printBoth();
}



// Muutin vähän pelaajaoliota. Luodessa haluaa parametrreinä nimen ja värin
//pelaajamäärää ei olisi edes varsinaisesti tarvittu täällä
//playerTurnDialogin riviä 18 jouduin hiukan väliaikaisesti sotkemaan, jotta kääntyi
//Pelaajaolioon tein name_ ja colour_ muuttujat sekä getName metodin




void createPlayers(std::vector<std::pair<std::string, std::string>> playerSpecs)
{
    std::list <std::shared_ptr<Player>> playerList = {};


    for (auto const&  player : playerSpecs)
    {
        // pelaajaoliot listaan
        std::shared_ptr<Player> playerPointer = std::make_shared<Player> (player.first, player.second);
        playerList.push_back(playerPointer);
        qDebug() << QString::fromStdString(player.first);
    }


    //pelaajalista city-olioon
    cityPtr->setPlayerList(playerList);


    //aloituspistelotto
    startingPointsSetup();

    //testailuja

    teststuff();

}


void updateActors(){


    for (auto const& actor : cityPtr->getActors()){
        cityPtr->getWindow()->addActor(actor->giveLocation().giveX(),
                                        actor->giveLocation().giveY(),1);
    }


}



void startYourEngines(std::shared_ptr<Interface::ICity> icity)
{
    cityPtr = std::dynamic_pointer_cast<City>(icity);

    //startingPointsSetup();
    //updateActors();
}


/*
 *
 * Klikattu kohdetta:
 *
 * jos pelaaja määränpäässä -> idle -> mitä tehdään. Baarissa ryypätään,
 * ei olla idle = vuoroa ei tule, ennenkuin juomingit loppuy
 * Laske pelaajan liikkumispisteet vector (Pelaaja (-> kulkuneuvo-> nopeus, nyt loc), wantedXY)
 * jos ei nyssessä: Jos nyssessä vektori = bussivektori
 *
 * return (Qtime,location);
 *
 *
 *
 * Pelaaja: + missä kulkuneuvossa
 *          + reitti määränpäähän
 *
 * Kulkuneuvot: + Nopeus
 *
 *
 * tick -> siirry(QTime)

*/
