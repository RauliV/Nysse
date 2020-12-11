#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

//#include "mainwindow.h"
#include "actors/player.hh"
#include "actors/stop.hh"
#include "city.hh"
#include <QtDebug>

class GameEngine
{
public:
    GameEngine(std::shared_ptr<Player>& playerInTurn,
               std::shared_ptr<City>& gameCity);
    ~GameEngine();

    void teststuff();
    void onTheTick(std::shared_ptr<Player> player);
    void createActorItems();
    void startYourEngines(std::shared_ptr<Interface::ICity> city);
    void initScreen(std::shared_ptr<Interface::ICity> city);
    std::list<std::shared_ptr<Player>> getPlayers();

public slots:


    QString enterBar(std::shared_ptr<Bar>& bar);  //Palauttaa virheilmoitustekstin
    QString enterStop(std::shared_ptr<CourseSide::Stop> stop);
    QString startJourney(std::shared_ptr<Interface::IVehicle> vechile,
                         Interface::Location  location);
    GameEngine startGame();

signals:

    void nextTurn (std::shared_ptr<Player>& player);

private:

    void movePlayer(std::shared_ptr<Player> player);
    void addActorItems();
    void addStaticItems();

    std::shared_ptr<Player>& playerInTurn_;
    std::shared_ptr<City>& gameCity_;

};
#endif // GAMEENGINE_HH
