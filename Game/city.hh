#ifndef CITY_HH
#define CITY_HH

#include "graphics/simplemainwindow.hh"

#include "interfaces/icity.hh"
#include <QTime>
#include <memory>

class City : public Interface::ICity
{

public:

    //City () :ICity(){};


    void set_window (std::shared_ptr<CourseSide::SimpleMainWindow> ikkuna_osoite)
    {
        ikkuna = ikkuna_osoite;
    }

    std::shared_ptr<CourseSide::SimpleMainWindow> get_window ()
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

private:
   std::shared_ptr <CourseSide::SimpleMainWindow> ikkuna;
};

#endif // CITY_HH
