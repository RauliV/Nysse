#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "mainwindow.h"
#include "actors/player.hh"
#include "core/location.hh"
#include "actors/stop.hh"
#include "city.hh"
#include <QtDebug>


class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine(std::shared_ptr<Player>& playerInTurn,
               std::shared_ptr<City>& gameCity,
               Interface::Location goalLocation);

    ~GameEngine();
    void initScreen(std::shared_ptr<Interface::ICity> city);
    //std::list<std::shared_ptr<Player>> getPlayers();
    void setGoalLocation(Interface::Location);
    void addActorItems();
    void addStaticItems();


public slots:

    void onTheTick();
    QString enterBar(std::shared_ptr<Bar>& bar);  //Palauttaa virheilmoitustekstin
    QString enterStop(std::shared_ptr<CourseSide::Stop> stop);
    QString startJourney(std::shared_ptr<Interface::IVehicle> vechile,
                         Interface::Location  location);

signals:

    void nextTurn (std::shared_ptr<Player>& player);
    void addStaticItem (int aX, int aY, std::shared_ptr<Interface::IStop> stop);
    void addActor(int aX, int aY, int type,
                  std::shared_ptr<Interface::IActor> actor);

private:

    void movePlayer(std::shared_ptr<Player> player);
    void endTurn();

    std::shared_ptr<City>& gameCity_;
    Interface::Location& goalLocation_;
    std::shared_ptr<Player>& playerInTurn_;


};
#endif // GAMEENGINE_HH
