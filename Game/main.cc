#include "creategame.hh"
#include "city.hh"
//#include "interfaces/icity.hh"
#include "graphics/simplemainwindow.hh"
#include <QApplication>
#include <QDebug>
#include <memory>




std::shared_ptr<Interface::ICity> pointer;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);



    std::shared_ptr<Interface::ICity> pointer;
    //qDebug() << "Tuleeko tähän";


    CourseSide::SimpleMainWindow window;
    window.show();

    //pointer = Interface::createGame(); //slot?   TÄSSÄ ROPLEEMI.
    // Miksi createGame ei ole käytettävissä täällä? Ajon aikainen linkitysvirhe?



    //Ei toimi, koska pointteri viittaa jonnekin(tm). Kts. edellä.
    //pointer->startGame();

    // pelimoottori

    // Game Over

    // statistics



    //for tests

    //pointer->setClock(QTime::currentTime());  //Eivät toimi, koska createGame
    //pointer->setBackground(QImage xxxx);




// Miten ikkunaolio näkyviin missä tarvitaan / globaaliksi?
// Esim. City::setBackground city.cc 45


    return a.exec();

}

namespace name {

//std::shared_ptr<CourseSide::SimpleMainWindow> ikkuna_osoite = new (CourseSide::SimpleMainWindow);
CourseSide::SimpleMainWindow *ikkuna_osoite =  new CourseSide::SimpleMainWindow;


};
