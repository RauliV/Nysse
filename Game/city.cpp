#include "city.hh"
#include "mainwindow.h"




void City::setBackground(QImage &basicbackground, QImage &bigbackground){

    auto noWarning = bigbackground;
    mainWindowPtr_->setPicture(basicbackground);

};


void City::setClock(QTime clock){

    *gameClock_=clock;

    /*short int hours = clock.hour();
    short int minutes = clock.minute();

    gameClock_->setHMS(hours,minutes,0);*/

};


void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    stopsList_.push_back(stop);

};


void City::startGame()
{
    mainWindowPtr_ = std::make_shared<MainWindow> ();
    mainWindowPtr_->show();

};


void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    actorsList_.push_back(newactor);

};


void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{

    actorsList_.remove(actor);
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    actor->remove();
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

    movedActors_.push_back(actor);

};



std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby_actors = {};

    for (auto const& actor : actorsList_){
        if (loc.calcDistance(actor->giveLocation(),loc) < 10)
        {
            nearby_actors.push_back(actor);
        }
    }


    return nearby_actors;
};



bool City::isGameOver() const
{
    for (auto const& player : playerList_)
        if (player->giveLocation() == goalLocation_)
        {
            return true;
        }

    return false;
}



void City::setBarList (std::list<std::shared_ptr<Bar>> bList){
    barList_ = bList;
}

std::list<std::shared_ptr<Bar>> City::getBarList () const
{
    return barList_;
}

void City::setAtmList (std::list<std::shared_ptr<Atm>> aList)
{
    atmList_ = aList;
}

std::list<std::shared_ptr<Atm>> City::getAtmList () const
{
    return atmList_;
}


void City::setPlayerList (std::list<std::shared_ptr<Player>> playerList)
{
    playerList_ = playerList;
}


std::list<std::shared_ptr<Player>> City::getPlayerList () const
{
    return playerList_;
}



std::list<std::shared_ptr<Interface::IActor>> City::getMovedActors() const
{
    return movedActors_;
}



void City::setStops (std::shared_ptr<Interface::IStop> stopPtr)
{
    stopsList_.push_back(stopPtr);
}

std::vector<std::shared_ptr<Interface::IStop>> City::getStops() const
{
    return stopsList_;
}



void City::setGame (std::shared_ptr<CourseSide::Logic> gamePtr)
{
    gamePtr_ = gamePtr;
}

std::shared_ptr<CourseSide::Logic> City::getGame () const
{
    return gamePtr_;
}



void City::setGameClock(std::shared_ptr<QTime> gameClock)
{
    gameClock_ = gameClock;
}

std::shared_ptr<QTime> City::getGameClock() const
{
    return gameClock_;
}


void City::setWindow (std::shared_ptr<MainWindow> mainWindowPtr)
{
    mainWindowPtr_ = mainWindowPtr;
}

std::shared_ptr<MainWindow> City::getWindow () const
{
    return mainWindowPtr_;
}


std::list<std::shared_ptr<Interface::IActor>> City::getActors() const
{
    return actorsList_;

}

void City::setGoalLocation (Interface::Location gLoc)
{
    goalLocation_ = gLoc;
}

Interface::Location City::getGoalLocation () const
{
    return goalLocation_;
}



