#include "creategame.hh"
#include "city.hh"
#include <QTime>
#include <QDebug>
#include <memory>

namespace Interface {



void init_screen(std::shared_ptr<City> city)
{
    QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);
    city->setBackground(tausta_iso, tausta_pieni);

    city->get_window()->show();
}



std::shared_ptr<ICity> createGame()
// Tätä ei ajeta vielä, koska errorerror

{   std::shared_ptr<City> pointer = std::make_shared<City>();
    Interface::init_screen(pointer);
    pointer -> setClock(QTime::currentTime());

    return pointer;
}
}
