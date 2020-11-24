#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "core/logic.hh"


/*tietorakenne
 * Actor {location, is_destroyed; vechile{ nimi,
 *                                  passenger
 *       vector passengers{sharedptr objects}
 *       vector stops{shareptr objects}
 *            player
 *
 *  Nysset, pelaajat, stops {obj}
 *

*/

// Tässäkin kiukuttelee joku

void make_game(std::shared_ptr<Interface::ICity> city);
/*
{

    std::shared_ptr<CourseSide::Logic> Game = std::make_shared<CourseSide::Logic> ();
    Game->takeCity(city);
};*/
#endif // GAME_ENGINE_H
