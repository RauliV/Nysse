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

    qDebug() << "clock";
};



void City::addStop(std::shared_ptr<Interface::IStop> stop)
{

    this->setStops(stop);
    //cityStopsPtr->push_back(stop);
    /*int id = stop->getId();
    QString nimi = stop->getName();
    Interface::Location paikka = stop->getLocation();
    CourseSide::Stop  uusi_pysakki(paikka, nimi, id);*/

    qDebug() << "stop";

};


void City::startGame()
{

ikkuna->show();

};


void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    setActors(newactor);

    //cityActorsPtr->push_back(newactor);

    qDebug() << "actor";

};


void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
   //cityActorsPtr->remove_if(actor);
  std::list<std::shared_ptr<Interface::IActor>>::iterator position =
    std::find(actorsList_.begin(), actorsList_.end(), actor);
    if (position != actorsList_.end())
    {
        actorsList_.erase(position);
    }
    qDebug() << "rm actor";

};



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

    //liikutettu ylipäätään?
};



std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby_actors = {};

    std::list<std::shared_ptr<Interface::IActor>>::iterator ite;
  /*  for(ite = actorsList_.begin(); ite != actorsList_.end(); ++ite)
    {
        std::shared_ptr<Interface::IActor> item = *ite;

        //nyt sama lokaatio. Mikä on "lähellä"?

        if (item->giveLocation() == loc)
        {
            nearby_actors.push_back(item);
        }
    }*/


    return nearby_actors;
};



bool City::isGameOver() const
{

    //if target_location == player_location

    return false;
};


