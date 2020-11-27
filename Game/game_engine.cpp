#include "game_engine.h"






//Kassa (xx)

//onko liikkunut (QTime x QTime x1 loc !)
//päivitä
//saapuu kohteeseen ->


void make_game(std::shared_ptr<Interface::ICity> city){


std::shared_ptr<City> kaupunki = std::dynamic_pointer_cast<City>(city);



std::shared_ptr<Interface::IActor> nyse = std::make_shared<CourseSide::Nysse> (5);
kaupunki->addActor(nyse);
qDebug() << "Onko" <<  kaupunki->findActor(nyse);
kaupunki->removeActor(nyse);
qDebug() << "Onko" <<  kaupunki->findActor(nyse);

kaupunki->addActor(nyse);



kaupunki->getGame()->finalizeGameStart();


kaupunki->get_window()->show();









//Yksittäisiä kokeiluja


//std::shared_ptr<CourseSide::Logic> game = std::make_shared<CourseSide::Logic> ();
//

//city->gameObjectPtr->takeCity(city);

 //std::shared_ptr<CourseSide::Logic> gameObjectPtr = std::make_shared<CourseSide::Logic>();

//&gameObjectPtr(game);
//gameObjectPtr->takeCity(city);

 //City *d = dynamic_cast<Derived*>(b);
//City *city_object = dynamic_cast<std::shared_ptr<Interface::ICity*>> (city.get());
//addActors(city);

//std::shared_ptr <City> new_d = dynamic_cast<std::shared_ptr <City>>
 //                              (std::shared_ptr<Interface::ICity>);



//Game->finalizeGameStart();
/*player -> playerlocation
city -> target location*/


};
