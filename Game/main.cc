#include "creategame.hh"
#include "city.hh"
//#include "interfaces/icity.hh"
#include "graphics/simplemainwindow.hh"
#include <QApplication>
#include <QDebug>
#include <memory>





int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    std::shared_ptr<Interface::ICity> pointer;

    CourseSide::SimpleMainWindow window;
   //CourseSide::SimpleMainWindow* window = new CourseSide::SimpleMainWindow[1];
    window.show();

    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);



    //pointer = Interface::createGame(); //   TÄSSÄ ROPLEEMI.

    // Miksi createGame ei ole käytettävissä täällä? Ajonaikainen linkitysvirhe?
    // Sama tiedostossa city.cc 94

    //Jumittavat, koska pointteri viittaa jonnekin(tm). Kts. edellä.
    //pointer->setBackground(tausta_iso, tausta_pieni);
    //pointer->setClock(QTime::currentTime());
    //pointer->startGame(); //slot

    return a.exec();


}




