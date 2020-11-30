#include "game_engine.h"




std::shared_ptr<City> cityPtr;
Interface::Location goalLocation;



// Koska Locationin rakentaja ei automaattisesti aseta pikseli

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

    int randomX = rand() % 500;
    int randomY = rand() % 500;
    Interface::Location rndLocation;
    rndLocation.setXY(randomX,randomY);

    return rndLocation;

}




void startingPointsSetup()
{

    const int DISTANCE_TO_TARGET = 350;
    const int DISTANCE_TRESHOLD = 10;


    //Luodaan pelille random maali
    goalLocation = getRandomLocation();



    // haetaan pelaajien aloituspisteitä, kunnes etäisyys maaliin
    // riittävän samanlainen (treshold)
    for (auto const&  player : cityPtr->getPlayerList())
    {
        Interface::Location startingPoint = getRandomLocation();
        //startingPoint.setXY(getRandomLocation().giveX(), getRandomLocation().giveY());
        double distance = Interface::Location::calcDistance(startingPoint,goalLocation); // Etäisyys targetLocationin ja arvotun pisteen välillä

        //Kunnes tresholdin sisällä.
        while (distance < (DISTANCE_TO_TARGET-DISTANCE_TRESHOLD) or
            (distance > (DISTANCE_TO_TARGET+DISTANCE_TRESHOLD)))

        {

            Interface::Location startingPoint = getRandomLocation();
            distance = Interface::Location::calcDistance(startingPoint,goalLocation);
        }


        //kun löytynyt, mene sinne
        player->move(startingPoint);

    }

}
// Laskee reitin linnuntietä paikasta A paikkaan B jaettun STEPSiin osaan.
std::vector<std::pair<int, int>> calculatePlayerRoute (Interface::Location A,
                                                      Interface::Location B)
{
    const int STEPS = 100;
    std::vector<std::pair<int, int>> returnVector = {};
    int aX = A.giveX();
    int aY = A.giveY();
    double xMovement = B.giveX() - aX;
    double yMovement = B.giveY() - aY;
    double xStep = xMovement / STEPS;
    double yStep = yMovement / STEPS;
    for (int it = 1; it < 100; it ++){
        std::pair <int, int> coord = {aX + (it*xStep),
                                      aY + (it *yStep)};
        returnVector.push_back(coord);
    }

    return returnVector;




}

void teststuff()
{


    //Testejä

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
        qDebug() << "Maali: " << goalLocation.giveX() << goalLocation.giveY();
        qDebug() << "Pelaaja: " << loc.giveX() << loc.giveY();

        it ++;
        std::vector<std::pair<int, int>> vec = calculatePlayerRoute(player->giveLocation(),
                                                                    goalLocation);
        qDebug() << "jonne mennään seuraavien pisteiden kautta";
        for (auto const& itt : vec){
            qDebug() << itt.first << itt.second;
        }
    }



}





void createPlayers(int playerCount, std::vector<std::pair<std::string, std::string>> playerSpecs)
{
    std::list <std::shared_ptr<Player>> playerList = {};


    for (auto const&  player : playerSpecs)
    {
        // pelaajaoliot listaan
        std::shared_ptr<Player> playerPointer = std::make_shared<Player> (player.first, player.second);
        playerList.push_back(playerPointer);
    }


    //pelaajalista city-olioon
    cityPtr->setPlayerList(playerList);



}


void updateActors(){


    for (auto const& actor : cityPtr->getActors()){
        Interface::Location paikka = actor->giveLocation();
        int x1 = paikka.giveEasternCoord();
        int y1 = paikka.giveNorthernCoord();
        int x = xFromEast(x1);
        int y = yFromNorth(y1);
        paikka.setXY(x,y);
        //CourseSide::SimpleActorItem acto(x,y,1);
        //cityPtr -> getWindow()-> addActor(x,y,9);
     //                                   actor->giveLocation().giveY(),1);


    }


}



void startYourEngines(std::shared_ptr<Interface::ICity> icity)
{
    cityPtr = std::dynamic_pointer_cast<City>(icity);


    //tämä siksi, ettei tarvitse aina testattaessa klikkailla.
    int pC = 1;
    std::pair<std::string, std::string> pP = {"Pekka", "musta"};
    std::vector<std::pair<std::string, std::string>> pV {pP};
    createPlayers(pC,pV);

    //aloituspistelotto
    startingPointsSetup();

    //testailuja

    teststuff();
    //startingPointsSetup();


    updateActors();
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
 *
 * Moduuleita:  luokat+rajapinnat ; Kulkuneuvot (Iactor), paikat (IStop) -baari: aika, rahat, känni
 *
 * Vakiot
 *
 *
 *

*/
