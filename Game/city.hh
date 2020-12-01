#ifndef CITY_HH
#define CITY_HH

#include "mainwindow.h"
#include "core/logic.hh"
#include "actors/player.hh"
#include "interfaces/icity.hh"
#include <QTime>
#include <memory>
#include <vector>

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




    //Omien metodien määrittely


    void setPlayerList (std::list<std::shared_ptr<Player>> playerList)
    {
        playerList_ = playerList;
    }

    std::list<std::shared_ptr<Player>> getPlayerList (){
        return playerList_;
    }



    std::list<std::shared_ptr<Interface::IActor>> getMovedActors(){
        return movedActors_;
    }



    void setStops (std::shared_ptr<Interface::IStop> stopPtr)
    {
        stopsList_.push_back(stopPtr);
    };

    std::vector<std::shared_ptr<Interface::IStop>> getStops(){

        return stopsList_;
    };



    void setGame (std::shared_ptr<CourseSide::Logic> gamePtr)
    {
        gamePtr_ = gamePtr;
    }

    std::shared_ptr<CourseSide::Logic> getGame ()
    {
        return gamePtr_;
    }



    void setGameClock(std::shared_ptr<QTime> gameClock)
    {
        gameClock_ = gameClock;
    }

    std::shared_ptr<QTime> getGameClock()
    {
        return gameClock_;
    }



    void setWindow (std::shared_ptr<MainWindow> mainWindowPtr)
    {
        mainWindowPtr_ = mainWindowPtr;
    }

    std::shared_ptr<MainWindow> getWindow ()
    {
        return mainWindowPtr_;
    }


    std::list<std::shared_ptr<Interface::IActor>> getActors(){
        return actorsList_;

    }

    void setGoalLocation (Interface::Location gLoc)
    {
        goalLocation_ = gLoc;
    }

    Interface::Location getGoalLocation ()
    {
        return goalLocation_;
    }



private:
   std::shared_ptr <MainWindow> mainWindowPtr_;
   std::shared_ptr<CourseSide::Logic> gamePtr_;
   std::vector<std::shared_ptr<Interface::IStop>> stopsList_;
   std::list<std::shared_ptr<Interface::IActor>> actorsList_;
   std::list<std::shared_ptr<Interface::IActor>> movedActors_;
   std::list<std::shared_ptr<Player>> playerList_;
   std::shared_ptr<QTime> gameClock_;
   Interface::Location goalLocation_;

};

#endif // CITY_HH
