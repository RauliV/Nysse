#include "city.hh"
#include "mainwindow.h"
#include "test_func_runs.h"
#include "actors/stop.hh"
#include "errors/gameerror.hh"
#include <QDebug>
#include <QTime>
#include <memory>




void City::setBackground(QImage &basicbackground, QImage &bigbackground){


    //window.setSize(1095,592);
    ikkuna->setPicture(basicbackground);

};



void City::setClock(QTime clock){

    short int hours = clock.hour();
    short int minutes = clock.minute();
    gameClock->setHMS(hours,minutes,0);


};



void City::addStop(std::shared_ptr<Interface::IStop> stop)
{

    cityStopsPtr->push_back(stop);
    /*int id = stop->getId();
    QString nimi = stop->getName();
    Interface::Location paikka = stop->getLocation();
    CourseSide::Stop  uusi_pysakki(paikka, nimi, id);*/

};


void City::startGame()
{

ikkuna->show();

};


void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    cityActorsPtr->push_back(newactor);

};



void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    std::list<std::shared_ptr<Interface::IActor>>::iterator position =
            std::find(cityActorsPtr->begin(), cityActorsPtr->end(), actor);
    if (position != cityActorsPtr->end())
        cityActorsPtr->erase(position);
/*
    //poista vektorista
    if  (not actor->isDestroyed())
    {
        actor->destroy();
        qDebug() << "tuhotaan";
    };*/

};



void City::actorDestroyed(std::shared_ptr<Interface::IActor> actor)
{
    actor->isDestroyed();
};



bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{

    if ( std::find(cityActorsPtr->begin(), cityActorsPtr->end(), actor) != cityActorsPtr->end())
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

    std::list<std::shared_ptr<Interface::IActor>>::iterator it;
    for(it = cityActorsPtr->begin(); it != cityActorsPtr->end(); ++it)
    {
        std::shared_ptr<Interface::IActor> item = *it;

        //nyt sama lokaatio. Mikä on "lähellä"?

        if (item->giveLocation() == loc)
        {
            nearby_actors.push_back(item);
        }
    }


    return nearby_actors;
};



bool City::isGameOver() const
{

    //if target_location == player_location

    return false;
};


