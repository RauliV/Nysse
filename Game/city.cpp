#include "city.hh"
#include "mainwindow.h"
#include "actors/stop.hh"
#include "errors/gameerror.hh"
#include <QDebug>
#include <QTime>
#include <memory>




void City::setBackground(QImage &basicbackground, QImage &bigbackground){


    //window.setSize(1095,592);
    ikkuna->setPicture(basicbackground);
    qDebug() << "picture";

};



void City::setClock(QTime clock){

    short int hours = clock.hour();
    short int minutes = clock.minute();
    gameClock_->setHMS(hours,minutes,0);

};



void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    stopsList_.push_back(stop);


};


void City::startGame()
{

ikkuna->show();

};


void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    actorsList_.push_back(newactor);

};


void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{

    actorsList_.remove(actor);
}

void City::actorDestroyed(std::shared_ptr<Interface::IActor> actor)
{
    actor->destroy();
};



bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{

    if ( std::find(actorsList_.begin(), actorsList_.end(), actor) != actorsList_.end())
    {
        return true;
    }
    else
    {
        return false;
    }



};



void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{

    //if (actor->giveLocation() !=
    //liikutettu ylipäätään?
};



std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby_actors = {};

    for (auto const& actor : actorsList_){
        if (loc.calcDistance(actor->giveLocation(),loc) < 2) {
            nearby_actors.push_back(actor);
        }
    }


    return nearby_actors;
};



bool City::isGameOver() const
{

    //if target_location == player_location

    return false;
};


