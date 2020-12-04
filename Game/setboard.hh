#ifndef SETBOARD_HH
#define SETBOARD_HH
#include "stops/bar.hh"
#include "stops/atm.hh"
#include "core/logic.hh"
#include "actors/player.hh"
#include "gameengine.h"
#include "city.hh"
#include <random>

/*
const QString TAXI_ICON_FILE = ":/graphics/taxi_icon.png";
const QImage TAXI_ICON (TAXI_ICON_FILE);
const std::shared_ptr<QImage> TAXI_ICON_PTR = std::make_shared<QImage> (TAXI_ICON);
*/
const QString SCOOTER_ICON_FILE = ":/graphics/scooter_icon2.png";
const QImage SCOOTER_ICON(SCOOTER_ICON_FILE);
const std::shared_ptr<QImage> SCOOTER_ICON_PTR = std::make_shared<QImage> (SCOOTER_ICON);

const QString BUS_STOP_ICON_FILE = ":/graphics/nysse_icon.png";
const QImage BUS_STOP_ICON(BUS_STOP_ICON_FILE);
const std::shared_ptr<QImage> BUS_STOP_ICON_PTR = std::make_shared<QImage> (BUS_STOP_ICON);


const QString WALK_ICON_FILE = ":/graphics/taxi_icon.png";
const QImage WALK_ICON(WALK_ICON_FILE);
const std::shared_ptr<QImage> WALK_ICON_PTR = std::make_shared<QImage> (WALK_ICON);

const QString BAR_ICON_FILE = ":graphics/bar_icon.png";
const QImage BAR_ICON(BAR_ICON_FILE);
const std::shared_ptr<QImage> BAR_ICON_PTR = std::make_shared<QImage> (BAR_ICON);

const QString ATM_ICON_FILE = ":graphics/atm_icon.png";
const QImage ATM_ICON(ATM_ICON_FILE);
const std::shared_ptr<QImage> ATM_ICON_PTR = std::make_shared<QImage> (ATM_ICON);


const int BAR_COUNT =   10;
const int TIME_SPENT_IN_BAR =   15000; //ms

const int ATM_COUNT =   10;
const int ATM_MAX_WITHDRAW = 100;
const int ATM_CASH_AT_BEGINNING = 200; //ehkä per pelaaja. Kokonaismäärä

const int DISTANCE_TO_TARGET =  350; //Target = maali
const int DISTANCE_TRESHOLD =   10;
const int STEPS =       100; //kuinka moneen osaan matka jaetaan

const int MAP_WIDTH =   400;    //actoreiden piirtoalueen koko
const int MAP_HEIGHT =  400;

//Vasen ja yläreuna pois, jotta stopit on keskusta-alueella eikä koskessa.
const int MAP_NORTH_EAST_CUT = 100;


void initScreen(std::shared_ptr<Interface::ICity> city);
Interface::Location getRandomLocation ();
void startingPointsSetup();
void createAtmsBars();
void createPlayers(std::vector<std::pair<std::string,
                   std::string>> playerSpecs);
void createTaxisScooters();

std::list <std::shared_ptr<Player>> getPlayers();
void addActorItems ();
void addStaticItems();
void updateActorsLocations();
int xFromEast(int eastcoord);
int yFromNorth(int northcoord);
int EastFromX(int x);
int NorthFromY(int y);
void clearPassengers();




#endif // SETBOARD_HH
