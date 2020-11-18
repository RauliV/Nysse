#include "city.hh"
#include "graphics/simplemainwindow.hh"
//#include "creategame.hh"
#include "actors/stop.hh"
#include "errors/gameerror.hh"
#include <QDebug>
#include <QTime>
#include <memory>


void City::setBackground(QImage &basicbackground, QImage &bigbackground){


    //name::window.setSize(1095,592);
    ikkuna->setPicture(basicbackground);
    qDebug() << "nyt näkyviin";

};



void City::setClock(QTime clock){

    //QTime::    setHMS(clock) clock  = clock;
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


};


void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    auto location = newactor->giveLocation(); //undefined referense. Linkitys?
    CourseSide::SimpleActorItem toimija(location.giveX(), location.giveY(), 0);
};



void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if  (not actor->isDestroyed())
    {
        actor->destroy();
    };

};



void City::actorDestroyed(std::shared_ptr<Interface::IActor> actor)
{
    actor->isDestroyed();
};



bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    try
    {
        actor->giveLocation();
    }
    catch (Interface::GameError error)
    {
        error.giveMessage();
        return false;

    }
    return true;

};



void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{

};



std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> hamyosoite;
    return hamyosoite;
};



bool City::isGameOver() const
{
    return false;
};


