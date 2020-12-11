#ifndef SETBOARD_HH
#define SETBOARD_HH
#include "stops/bar.hh"
#include "stops/atm.hh"
#include "core/logic.hh"
#include "gameengine_old.h"
#include "city.hh"
#include "gameengine.hh"
#include <random>


// Vehicledata
const short int VEHICLE_COUNT = 5;
const short int BUSS_FARE = 5;

const int BAR_COUNT =   10;
const int TIME_SPENT_IN_BAR =   15000; //ms

const int ATM_COUNT =   10;
const int ATM_MAX_WITHDRAW = 100;
const int ATM_CASH_AT_BEGINNING = 200; //ehkä per pelaaja. Kokonaismäärä

// Karttadata
const int DISTANCE_TO_TARGET =  350; //Target = maali
const int DISTANCE_TRESHOLD =   10;  // kuinka lähellä lähtöetäisyyksien tulee olla
const int STEP_LENGTH =         1; //kuinka pitkä on askel

const int MAP_WIDTH =   400;    //actoreiden piirtoalueen koko
const int MAP_HEIGHT =  400;

//Vasen ja yläreuna pois, jotta stopit on keskusta-alueella eikä koskessa.
const int MAP_NORTH_EAST_CUT = 100;


void initScreen(std::shared_ptr<Interface::ICity> city);
Interface::Location getRandomLocation ();
void startingPointsSetup();
void createAtmsBars();
GameEngine createPlayers(std::vector<std::pair<std::string, std::string> > &playerSpecs);
void setBoard(std::vector<std::pair<std::string,
              std::string>> playerSpecs);
void createTaxisScooters();
std::string getSubClass (std::shared_ptr<Interface::IActor> iActor );
std::list <std::shared_ptr<Player>> getPlayers();
/*void addActorItems ();
void addStaticItems();*/
int xFromEast(int eastcoord);
int yFromNorth(int northcoord);
int EastFromX(int x);
int NorthFromY(int y);
void clearPassengers();




#endif // SETBOARD_HH
