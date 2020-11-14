#include "interfaces/icity.hh"
#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include <QDebug>
#include <QTime>


class City : public Interface::ICity{

public:


    void setBackground(QImage& basicbackground, QImage& bigbackground);

    void setClock(QTime clock);

    void addStop(std::shared_ptr<Interface::IStop> stop){};

    void startGame(){};

    void addActor(std::shared_ptr<Interface::IActor> newactor){};

    void removeActor(std::shared_ptr<Interface::IActor> actor){};

    void actorDestroyed(std::shared_ptr<Interface::IActor> actor){};

    bool findActor(std::shared_ptr<Interface::IActor> actor) const{};

    void actorMoved(std::shared_ptr<Interface::IActor> actor) {};

    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const
    {
        std::vector<std::shared_ptr<Interface::IActor>> hamyosoite;
        return hamyosoite;
    }
    bool isGameOver() const{return false;}



};

void City::setBackground(QImage &basicbackground, QImage &bigbackground){

    //CourseSide::SimpleMainWindow window;
    //window.setSize(1095,592);
    //window.setPicture(basicbackground);
    //QPointer<QWindow>
    //>extern CourseSide::SimpleMainWindow window;
    //window.setPicture(bigbackground);
    qDebug() << "nyt näkyviin";
    //window.show();

};

void City::setClock(QTime clock){

    clock = QTime::currentTime();

};
