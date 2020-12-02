#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "mainwindow.h"
#include "city.hh"

#include <QtDebug>
void teststuff();
void onTheTick(std::shared_ptr<Player> player);
void createActorItems();
void startYourEngines(std::shared_ptr<Interface::ICity> city);
void initScreen(std::shared_ptr<Interface::ICity> city);
void createPlayers(std::vector<std::pair<std::string, std::string>> playerSpecs);
std::list<std::shared_ptr<Player>> getPlayers();
#endif // GAME_ENGINE_H
