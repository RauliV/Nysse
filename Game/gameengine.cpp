#include "gameengine.h"
#include "setboard.hh"
#include "actors/taxi.hh"

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
{
    std::vector<Interface::Location> returnVector;
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

void stepInVehicle(std::shared_ptr<Player> player, std::shared_ptr<Interface::IVehicle> vechile)
{
    player->getInVechile(vechile);

    //poista actori käytön jälkeen?

    //Bussi -> jos ei jo ollut ja jos rahaa eikä liikaa kännissä - astu sisään
    //Scooter -> jos akkua ja rahaa eikä liikaa kännissä
    //Taksi -> jos rahaa eikä liikaa kännissä
}

void arriveDestination(std::shared_ptr<Player> player, Interface::Location dest)

{
    player->setIdle(true);
    player->resetRoute();
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
   //    if (onkosullarahee)
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


    //Testejä
    auto list = cityPtr->getPlayerList();
    int it = 1;
    for (auto const& player : list){
        Interface::Location loc = player->giveLocation();
        /*loc.setXY(xFromEast(player->giveLocation().giveEasternCoord()),
                  yFromNorth(player->giveLocation().giveNorthernCoord()));
        //Interface::Location y = loc.setXY(player->giveLocation().giveEasternCoord();

*/
        QString qname = QString::fromStdString(player->getName());
        QString qcolour = QString::fromStdString(player->getColour());
        qDebug() << "Pelaaja " << it << ": " << qname;
        qDebug() << "Väri on: " << qcolour;
        qDebug() << "Paikassa: ";
        qDebug() << "Maali: " << cityPtr->getGoalLocation().giveX() << cityPtr->getGoalLocation().giveY();
        qDebug() << "Pelaaja: " << loc.giveX() << loc.giveY();

        it ++;
    }


    std::shared_ptr<Taxi> taksi = std::make_shared<Taxi> ();
   /* std::shared_ptr<Interface::IVehicle> veh =
            std::dynamic_pointer_cast<Interface::IVehicle>(taksi);*/

    auto ppl = cityPtr->getPlayerList().front();
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


}



void startYourEngines(std::shared_ptr<Interface::ICity> cPtr)
{
    cityPtr = std::dynamic_pointer_cast<City>(cPtr);


    //Setboard funktioita
    createAtmsBars();
    createTaxisScooters();
    addStaticItems();
    addActorItems();
    clearPassengers();
    startingPointsSetup();


    
    for (auto const& actor : cityPtr->getActors())
        


    {

        cityPtr->getWindow()->addActor(actor->giveLocation().giveX(),
                                       actor->giveLocation().giveY(),
                                       2,
                                       SCOOTER_ICON_PTR);
       /* std::string sClass = getSubClass(actor);
        
        if (sClass == "taxi")
        {
            auto icon = std::dynamic_pointer_cast<Taxi>(actor)->getIcon();
            cityPtr->getWindow()->addActor(actor->giveLocation().giveX(),
                                           actor->giveLocation().giveY(),
                                           2,
                                           icon);*/
                    

    }
    



    


};

