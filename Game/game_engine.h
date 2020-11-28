#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "mainwindow.h"
#include "core/logic.hh"
#include "player.hh"
#include "city.hh"
#include "interfaces/icity.hh"
#include <random>






/*const std::shared_ptr<std::list<std::shared_ptr<Interface::IActor>>> cityActorsPtr
= std::make_shared<std::list<std::shared_ptr<Interface::IActor>>> ();;
//const std::list<std::shared_ptr<Interface::IActor>> cityActorsPtr ={nullptr};

const std::shared_ptr<std::list<std::shared_ptr<Interface::IStop>>> cityStopsPtr
= std::make_shared<std::list<std::shared_ptr<Interface::IStop>>> ();
        //std::make_shared<CourseSide::Logic>();

const std::shared_ptr<CourseSide::Logic> gameObjectPtr
= std::make_shared<CourseSide::Logic>();*/

//const std::shared_ptr<CourseSide::Logic> gameObjectPtr;

//const std::shared_ptr<QTime> gameClock = std::make_shared<QTime> (0,0,0);


void startYourEngines(std::shared_ptr<Interface::ICity> city);
void initScreen(std::shared_ptr<Interface::ICity> city);

#endif // GAME_ENGINE_H
