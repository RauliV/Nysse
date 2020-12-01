#ifndef SETBOARD_HH
#define SETBOARD_HH

#include "stops/bar.hh"
#include "stops/atm.hh"
#include "core/logic.hh"
#include "actors/player.hh"
#include "city.hh"
#include <random>


const int DISTANCE_TO_TARGET =  350; //Target = maali
const int DISTANCE_TRESHOLD =   10;
const int STEPS =       100; //kuinka moneen osaan matka jaetaan
const int BAR_COUNT =   10;
const int ATM_COUNT =   10;
const int MAP_WIDTH =   500;
const int MAP_HEIGHT =  500;


void initScreen(std::shared_ptr<Interface::ICity> city);
Interface::Location getRandomLocation ();
void startingPointsSetup();
void createAtmsBars();
void createPlayers(std::vector<std::pair<std::string,
                   std::string>> playerSpecs);
std::list <std::shared_ptr<Player>> getPlayers();


#endif // SETBOARD_HH
