#ifndef CITY_HH
#define CITY_HH

#include "graphics/simplemainwindow.hh"

#include "interfaces/icity.hh"
#include <QTime>

class City : public Interface::ICity
{

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
    };
    bool isGameOver() const
    {
        return false;
    };
};

#endif // CITY_HH
