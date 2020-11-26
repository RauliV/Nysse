#include "game_engine.h"






//Kassa (xx)

//onko liikkunut (QTime x QTime x1 loc !)
//päivitä
//saapuu kohteeseen ->


void make_game(std::shared_ptr<Interface::ICity> city){

//std::shared_ptr<CourseSide::Logic> game = std::make_shared<CourseSide::Logic> ();
std::shared_ptr<CourseSide::Logic> gameObjectPtr {std::make_shared<CourseSide::Logic> ()};

//&gameObjectPtr(game);
gameObjectPtr->takeCity(city);

 //City *d = dynamic_cast<Derived*>(b);
//City *city_object = dynamic_cast<std::shared_ptr<Interface::ICity*>> (city.get());
addActors(city);

//std::shared_ptr <City> new_d = dynamic_cast<std::shared_ptr <City>>
 //                              (std::shared_ptr<Interface::ICity>);



//Game->finalizeGameStart();
/*player -> playerlocation
city -> target location*/


};
