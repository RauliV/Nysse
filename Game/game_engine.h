#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "mainwindow.h"
#include "core/logic.hh"
#include "test_func_runs.h"
#include "city.hh"


/*tietorakenne
 * Actor {location, is_destroyed; vechile{ nimi,
 *                                  passenger
 *       vector passengers{sharedptr objects}
 *       vector stops{shareptr objects}
 *            player
 *
 *vector actors, stops, atms
 *
 *  Nysset, pelaajat, stops {obj}
 *

*/

//pelikello
//stops ja actors -vektorit?

const std::shared_ptr<std::list<std::shared_ptr<Interface::IActor>>> cityActorsPtr;
const std::shared_ptr<std::list<std::shared_ptr<Interface::IStop>>> cityStopsPtr;

const std::shared_ptr<CourseSide::Logic> gameObjectPtr;

const std::shared_ptr<QTime> gameClock = std::make_shared<QTime> ();


void make_game(std::shared_ptr<Interface::ICity> city);

#endif // GAME_ENGINE_H
