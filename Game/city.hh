#ifndef CITY_HH
#define CITY_HH

#include "mainwindow.h"
#include "game_engine.h"
#include "interfaces/icity.hh"
#include <QTime>
#include <memory>
#include <vector>

class City : public Interface::ICity
{

public:

    std::list<std::shared_ptr<Interface::IStop>> getStops(){

        return stopsList_;
    };


    std::list<std::shared_ptr<Interface::IActor>> getActors() const{

        return actorsList_;
    };

    void setActors (std::shared_ptr<Interface::IActor> actorPtr){

        actorsList_.push_back(actorPtr);
    };


    void setStops (std::shared_ptr<Interface::IStop> stopPtr){

        stopsList_.push_back(stopPtr);

    };


    void setGame (std::shared_ptr<CourseSide::Logic> gamePtr){
        //std::shared_ptr<CourseSide::Logic>
        gamePtr_ = gamePtr;
    }

    std::shared_ptr<CourseSide::Logic> getGame (){

        return gamePtr_;
    }

     void setGameClock(std::shared_ptr<QTime> clk){


        gameClock_ = clk;
    }

    std::shared_ptr<QTime> getGameClock(){
        return gameClock_;
    }


    void set_window (std::shared_ptr<MainWindow> ikkuna_osoite)
    {
        ikkuna = ikkuna_osoite;
    }

    std::shared_ptr<MainWindow> get_window ()
    {
        return ikkuna;
    }

    void setBackground(QImage& basicbackground, QImage& bigbackground);

    void setClock(QTime clock);

    void addStop(std::shared_ptr<Interface::IStop> stop);

    void startGame();

    void addActor(std::shared_ptr<Interface::IActor> newactor);

    void removeActor(std::shared_ptr<Interface::IActor> actor);

    void actorDestroyed(std::shared_ptr<Interface::IActor> actor);

    bool findActor(std::shared_ptr<Interface::IActor> actor) const;

    void actorMoved(std::shared_ptr<Interface::IActor> actor);

    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const;
    /*{
        std::vector<std::shared_ptr<Interface::IActor>> hamyosoite;
        return hamyosoite;
    };*/

    bool isGameOver() const;
    /*
    {
        return false;
    };*/

    //const std::vector<std::shared_ptr<Interface::IActor>> city_actors = {};

private:
   std::shared_ptr <MainWindow> ikkuna;
   std::shared_ptr<CourseSide::Logic> gamePtr_;
   std::list<std::shared_ptr<Interface::IStop>> stopsList_;
   std::list<std::shared_ptr<Interface::IActor>> actorsList_;
   std::shared_ptr<QTime> gameClock_;

};

#endif // CITY_HH
