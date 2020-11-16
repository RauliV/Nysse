#include "creategame.hh"
#include "city.hh"
#include <QTime>
#include <QDebug>
#include <memory>


std::shared_ptr<Interface::ICity> createGame()
{
    /*QString file_iso = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QString file_pieni = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage tausta_iso (file_iso);
    QImage tausta_pieni (file_pieni);*/
    City tampere;
    /*tampere.setBackground(tausta_pieni, tausta_iso);
    tampere.setClock(QTime::currentTime());

    //extern ?? Osoite globaaliksi/näkymään Cityn metodeissa?*/
    std::shared_ptr<Interface::ICity> kaupunki_osoite;
    *kaupunki_osoite = tampere;
    return kaupunki_osoite;
}
