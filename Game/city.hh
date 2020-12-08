#ifndef CITY_HH
#define CITY_HH

#include "mainwindow.h"
#include "stops/bar.hh"
#include "stops/atm.hh"
#include "core/logic.hh"
#include "actors/player.hh"
#include "interfaces/icity.hh"
#include <vector>
#include "actors/stop.hh"
#include "errors/gameerror.hh"
#include <QDebug>
#include <QTime>
#include <memory>

class City : public Interface::ICity
{

public:


    void setBackground(QImage& basicbackground, QImage& bigbackground);

    void setClock(QTime clock);

    void addStop(std::shared_ptr<Interface::IStop> stop);

    void startGame();

    void addActor(std::shared_ptr<Interface::IActor> newactor);

    void removeActor(std::shared_ptr<Interface::IActor> actor);

    void actorRemoved(std::shared_ptr<Interface::IActor> actor);

    bool findActor(std::shared_ptr<Interface::IActor> actor) const;

    void actorMoved(std::shared_ptr<Interface::IActor> actor);

    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const;

    bool isGameOver() const;


    void setBarList (std::list<std::shared_ptr<Bar>> bList);
    std::list<std::shared_ptr<Bar>> getBarList () const;

    void setAtmList (std::list<std::shared_ptr<Atm>> aList);
    std::list<std::shared_ptr<Atm>> getAtmList () const;

    void setPlayerList (std::list<std::shared_ptr<Player>> playerList);
    std::list<std::shared_ptr<Player>> getPlayerList () const;

    std::list<std::shared_ptr<Interface::IActor>> getMovedActors() const;

    void setStops (std::shared_ptr<Interface::IStop> stopPtr);
    std::vector<std::shared_ptr<Interface::IStop>> getStops() const;

    void setGame (std::shared_ptr<CourseSide::Logic> gamePtr);
    std::shared_ptr<CourseSide::Logic> getGame () const;

    void setGameClock(std::shared_ptr<QTime> gameClock);
    std::shared_ptr<QTime> getGameClock() const;

    void setWindow (std::shared_ptr<MainWindow> mainWindowPtr);
    std::shared_ptr<MainWindow> getWindow () const;

    std::list<std::shared_ptr<Interface::IActor>> getActors() const;

    void setGoalLocation (Interface::Location gLoc);

    Interface::Location getGoalLocation () const;

private:
   std::shared_ptr <MainWindow> mainWindowPtr_;
   std::shared_ptr<CourseSide::Logic> gamePtr_;
   std::vector<std::shared_ptr<Interface::IStop>> stopsList_;
   std::list<std::shared_ptr<Interface::IActor>> actorsList_;
   std::list<std::shared_ptr<Interface::IActor>> movedActors_;
   std::list<std::shared_ptr<Player>> playerList_;
   std::list<std::shared_ptr<Bar>> barList_;
   std::list<std::shared_ptr<Atm>> atmList_;
   std::shared_ptr<QTime> gameClock_;
   Interface::Location goalLocation_;

};

#endif // CITY_HH
