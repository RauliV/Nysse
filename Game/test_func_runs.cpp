#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "actors/stop.hh"
#include "city.hh"
#include <QTime>
#include <QDebug>
#include <memory>
#include <QStyleOptionGraphicsItem>

void addActors(std::shared_ptr<City> city)
{
    //Alustetaan toimijoita

    auto nysse_shared_ptr = std::make_shared<CourseSide::Nysse> (5);
    //city->addActor(nysse_shared_ptr );
    Interface::Location paikka;
    paikka.setXY(100,100);
    Interface::Location paikka2;
    paikka2.setXY(200,200);

    QString stop_name = "Keskustori";
    auto stop_shared_ptr = std::make_shared<CourseSide::Stop> (paikka,stop_name,1);
    //auto s_shared_ptr =  ;
    auto matkustaja_shared_ptr = std::make_shared<CourseSide::Passenger> (stop_shared_ptr);
    //city->addActor(matkustaja_shared_ptr);
    //city->addActor(stop_shared_ptr.get());

    qDebug() << "Matkustaja on kulkuneuvossa? " << matkustaja_shared_ptr->isInVehicle();
    matkustaja_shared_ptr.get()->enterNysse(nysse_shared_ptr);


    qDebug() << "Kip...kip..kipittää sisään";
    qDebug() << "Nyt matkustaja on kulkuneuvossa? " << matkustaja_shared_ptr->isInVehicle();


    //Luetaan toimijasta
    auto kulkuneuvo = matkustaja_shared_ptr.get()->getVehicle();
    auto kulkuneuvo_str = kulkuneuvo.get()->getName();
    auto pysakki = matkustaja_shared_ptr.get()->getStop();

    QString q_kulkuneuvon_nimi = QString::fromStdString(kulkuneuvo_str);
    Interface::Location matkustajan_paikka = matkustaja_shared_ptr.get()->giveLocation();
    //QString maaranpaa = pysakki->getName();

    //std::string maaranpaa_str = pysakki.get()->getName();


    qDebug() << "Kulkuneuvossa" << qPrintable(q_kulkuneuvon_nimi);
    //qDebug() << "määränpää on " << qPrintable(maaranpaa);
    qDebug() << "Paikassa X: " << matkustajan_paikka.giveX()
             << " Y: " << matkustajan_paikka.giveY();
    qDebug() << "saapuu pysäkille";
    matkustaja_shared_ptr.get()->enterStop(pysakki);
    qDebug() << "Paikassa X: " << matkustajan_paikka.giveX()
             << " Y: " << matkustajan_paikka.giveY();


    //auto matkustajaluettelo = nysse_shared_ptr->getPassengers();

    //city->removeActor(nysse_shared_ptr);

    QTime uusi_aika;
    uusi_aika.setHMS(0,0,0,0);
    nysse_shared_ptr->move(paikka);
    auto stop = nysse_shared_ptr->getStop();
    nysse_shared_ptr->calcStartingPos(uusi_aika);
    paikka = nysse_shared_ptr->giveLocation();
    std::string nimi = nysse_shared_ptr->getName();

    //nysse_shared_ptr->getTimeRoute(QTime::currentTime(), );


    int x = 0;


    while (x < 100)
    {
        city->get_window()->addActor(x,x,0);
        x += 1;
        city->get_window()->update();
    }

    while (x>1)
    {
        city->get_window()->addActor(x,x,x);
        x -= 1;
    }




}

void init_screen(std::shared_ptr<City> city)
{
    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);
    city->setBackground(tausta_iso, tausta_pieni);

    city->get_window()->show();
}

