#include "city.hh"
#include "mainwindow.h"
#include "test_func_runs.h"
#include "creategame.hh"
#include "actors/stop.hh"
#include "errors/gameerror.hh"
#include "core/logic.hh"
#include <QDebug>
#include <QTime>
#include <memory>




void City::setBackground(QImage &basicbackground, QImage &bigbackground){


    //window.setSize(1095,592);
    ikkuna->setPicture(basicbackground);

};



void City::setClock(QTime clock){

    short int hours = QTime::currentTime().minute();
    short int minutes = QTime::currentTime().hour();
    clock.setHMS(minutes, hours, 0);
    qDebug() << clock;

};



void City::addStop(std::shared_ptr<Interface::IStop> stop)
{

    int id = stop->getId();
    QString nimi = stop->getName();
    Interface::Location paikka = stop->getLocation();
    CourseSide::Stop  uusi_pysakki(paikka, nimi, id);

};


void City::startGame()
{

CourseSide::SimpleMainWindow ikkuna;
ikkuna.show();

};


void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    city_actors.push_back(newactor);

};



void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if  (not actor->isDestroyed())
    {
        actor->destroy();
        qDebug() << "tuhotaan";
    };

};



void City::actorDestroyed(std::shared_ptr<Interface::IActor> actor)
{
    actor->isDestroyed();
};



bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{

    if ( std::find(city_actors.begin(), city_actors.end(), actor) != city_actors.end())
    {
        return true;
    }
    else
    {
        return false;
    }

    /*
    try
    {
        actor->giveLocation();
    }
    catch (Interface::GameError error)
    {
        error.giveMessage();
        return false;

    }
    return true;*/

};



void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{

};



std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby_actors = {};

    for (unsigned i=0; i < city_actors.size(); i++) {
        if (city_actors.at(i)->giveLocation() == loc)
        {
            nearby_actors.push_back(city_actors.at(1));
        }
    }


    return nearby_actors;
};



bool City::isGameOver() const
{
    return false;
};


