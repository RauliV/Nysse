//#include "city.hh"
//#include "interfaces/icity.hh"
#include "graphics/simplemainwindow.hh"
#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include "actors/stop.hh"
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

    void actorDestroyed(std::shared_ptr<Interface::IActor> actor);

    bool findActor(std::shared_ptr<Interface::IActor> actor) const;

    void actorMoved(std::shared_ptr<Interface::IActor> actor);

    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const;

    bool isGameOver() const;


};


void City::setBackground(QImage &basicbackground, QImage &bigbackground){

    // Taustan asettamisessa ongelma, koska pitäisi käyttää toisessa instanssissa
    // (main.cc) luotua ikkunaoliota

    //name::window.setSize(1095,592);
    //window.setPicture(basicbackground);
    //QPointer<QWindow>
    //>extern CourseSide::SimpleMainWindow window;
    //window.setPicture(bigbackground);
    qDebug() << "nyt näkyviin";
    //window.show();

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

    /*
    CourseSide::Stop::setId (stop->getId());
    CourseSide::Stop::setLocation(stop->getLocation();
    CourseSide::Stop::setName(stop->getName());
    //pysakki()*/
};


void City::startGame()
{


};



void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

};



void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    actor->destroy();
};



void City::actorDestroyed(std::shared_ptr<Interface::IActor> actor)
{

};



bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{

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



