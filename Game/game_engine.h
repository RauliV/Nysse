#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "mainwindow.h"
#include "city.hh"

#include <QtDebug>



void startYourEngines(std::shared_ptr<Interface::ICity> city);
void initScreen(std::shared_ptr<Interface::ICity> city);
void createPlayers(int playerCount, std::vector<std::pair<std::string, std::string>> playerSpecs);
#endif // GAME_ENGINE_H
